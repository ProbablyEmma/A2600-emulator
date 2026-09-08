// RegisterFile.h

#pragma once
#include <stdint.h>
#include <Processor/RegisterTypes.h>
#include <Processor/CPURuntimeTypes.h>
#include <Processor/InstructionTypes.h>

namespace cpu::registers{
    // LOGICAL PRINCIPLE/ AUTHORS NOTE:  MOST 6502 registers have particular semantics, eg how the PC is split into smaller PCH/PCL fields. 
    // We hide this abstraction behind wrappers and methods so we can make registers behave internally as they would on the 6502 while providing a way to programmatically access higher level abstractions
    struct Register {
    private:
        uint8_t value = 0x00;
    public:
        uint8_t read() const; // get data from register
        void write(uint8_t data); //write data to register
    };

    struct StatusRegister {
        // Raw SR value, should not be read directly
        private:
            uint8_t status = 0x00; //FIXME: check 6502 flag init policy
        public:
            uint8_t read() const; // get raw 8b SR fields
            void write(uint8_t SR); //write raw 8b SR
            bool readFlag(cpu::registers::StatusFlag flag) const; //read particular flag
            void writeFlag(cpu::registers::StatusFlag flag, bool value); //write particular flag
            void setZN(uint8_t value);
            void commitFlags(const cpu::instructions::Instruction& instr, const cpu::execution::ResolvedInfoInstruction& instrMetaData);
        };

        struct StackPointer {
            //NOTE: 6502 uses a decrementing, empty stack convention (pushing decrements the SP and vice versa, and SP always points to next empty byte)
        private:
            // RAW SP value
            uint16_t value = 0x01FF; //check raw value
            // private: increment/decrement SP pointed address. Given 6502 semantics this should theoretically only ever be SP +/- 1
        public:
            void write(uint8_t stackHead); //set stack head adress, useful for init. NOTE that the 6502 assumes 8b addresses are supplied, and does 0x0100 | SP to compute the full 16
            uint8_t read() const;
            void incrementSPHead(uint8_t offset);
            void decrementSPHead(uint8_t offset);
        };

        struct ProgramCounter {
        private:
            uint16_t PC = 0x00;
            uint8_t PCL;
            uint8_t PCH;
            void splitPCHighLow(uint16_t value);
        public:
            void write(uint16_t newPC); // for jump, branch and init
            void incrementPC(uint8_t offset); // PC = PC + 2 type stuff
            void decrementPC(uint8_t offset); // PC = PC - 2 i guess?
            // Reading PC fields here, when accessing register file PC value
            uint16_t readPC() const;
            uint8_t readPCH() const;
            uint8_t readPCL() const;
        };

        class RegisterFile {
        public:
            // GENERAL PURPOSE CPU REGISTERS
                Register A; // Accumulator
                Register X; // Index register X
                Register Y; //Index register Y
                // SPECIAL PURPOSE CPU REGISTERS
                    ProgramCounter PC;
                    StackPointer SP;
                    StatusRegister SR;

                };
};