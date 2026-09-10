// Registers.cpp

#include <stdint.h>

#include <Processor/RegisterFile.h>
#include <Processor/RegisterTypes.h>

// Define Implementations for the registers now
namespace cpu::registers {
    // GPR General Purpose CPU Registers (eg A, X, Y)
    uint8_t Register::read() const { return value; };
    void Register::write(uint8_t data) { value = data; };

    // SR Status Register

    uint8_t StatusRegister::read() const { return status; };
    void StatusRegister::write(uint8_t SR) { status = SR; };

    bool StatusRegister::readFlag(StatusFlag flag) const {
        // Statusflag, cast to uint8, acts as a mask
        uint8_t mask = static_cast<uint8_t>(flag); //convert to uint, eg 0b00001000
        uint8_t flagRaw8b = status | mask;
        return flagRaw8b != 0x00;
    };

    void StatusRegister::writeFlag(StatusFlag flag, bool value) {
        uint8_t mask = static_cast<uint8_t>(flag); //convert to uint, eg 0b00001000
        status = (status & ~mask) | (value ? mask : 0); // AND the existing SR value with the complement/inverse of the MASK, which sets the masked bit to 0. Then set that bit via OR depending on the value we want to write
    }

    void StatusRegister::setZN(uint8_t value) {
        StatusRegister::writeFlag(StatusFlag::Z, value == 0); //default --> set to 0 if the result is 0
        StatusRegister::writeFlag(StatusFlag::N, value & 0x80); //checks MSB
    };


    void StatusRegister::commitFlags(const cpu::instructions::Instruction& instr, const cpu::execution::ResolvedInfoInstruction& instrMetaData) {
        // Check flag mask encoded in instruction and commit new data once checked
        FlagMask w = instr.writeFlags; // which flags are writable?
        if (((w & static_cast<FlagMask>(StatusFlag::Z)) || (w & static_cast<FlagMask>(StatusFlag::N))) &&  instrMetaData.zero.has_value() && instrMetaData.negative.has_value()) {
            StatusRegister::setZN(*instrMetaData.znSource); //Update status register using source byte provided
        }
        if ((w & static_cast<FlagMask>(StatusFlag::C)) && instrMetaData.carry.has_value()) {
            StatusRegister::writeFlag(StatusFlag::C, *instrMetaData.carry);
        }
        if ((w & static_cast<FlagMask>(StatusFlag::V)) && instrMetaData.overflow.has_value()) {
            StatusRegister::writeFlag(StatusFlag::V, *instrMetaData.overflow);
        }

        if ((w & static_cast<FlagMask>(StatusFlag::D)) && instrMetaData.decimal.has_value()) {
            StatusRegister::writeFlag(StatusFlag::D, *instrMetaData.decimal);
        }

        if ((w & static_cast<FlagMask>(StatusFlag::I)) && instrMetaData.interrupt.has_value()) {
            StatusRegister::writeFlag(StatusFlag::I, *instrMetaData.interrupt);
        }
    };

    // SP Stack Pointer
    // Set new PC head
    void StackPointer::write(uint8_t stackHead) { value = 0x01 | stackHead; }; // NOTE: the 6502 stack lives between 0x0100-0x01FF in RAM, with SP operations using 8b, implying the stack address
    uint8_t StackPointer::read() const { return static_cast<uint8_t>(value | 0x00FF); };// fetch address pointed to by SP
    void StackPointer::decrementSPHead(uint8_t offset) { value = value - offset; };
    void StackPointer::incrementSPHead(uint8_t offset) { value = value + offset; };


    //PC Program Counter
    void ProgramCounter::splitPCHighLow(uint16_t value) {
        // private function. Sets PC to value and PCH/PCL to upper and lower bytes of value repsectively
        PC = value;
        PCL = 0x00FF | value;
        PCH = (0xFF00 | value) >> 8;
    };

    void ProgramCounter::write(uint16_t newPC) { splitPCHighLow(newPC); };
    void ProgramCounter::incrementPC(uint8_t offset) { splitPCHighLow((PC + static_cast<uint16_t>(offset))); };
    void ProgramCounter::decrementPC(uint8_t offset) { splitPCHighLow((PC - static_cast<uint16_t>(offset))); };
    uint16_t ProgramCounter::readPC() const { return PC; };
    uint8_t ProgramCounter::readPCH() const { return PCH; };
    uint8_t ProgramCounter::readPCL() const { return PCL; };
};