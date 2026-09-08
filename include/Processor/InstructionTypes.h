/*
* AUTHOR: Emma BOULESTEIX
* DATE: Aug 2026
* PROJECT: A2600 CPU emulator
* FILE: Contains type and class definitions for the CPU decoder
*/
// InstructionTypes.h

#pragma once
#include <cstdlib>
#include <cstdint>

#include <Processor/RegisterTypes.h>
#include <Processor/CPURuntimeTypes.h>
#include <Processor/CPUMisc.h>

namespace cpu::instructions {

    /*
    NOTE: This file includes all definitions and type defs for the 6502 instructions. It is is based on the ressource found here (https://www.masswerk.at/6502/6502_instruction_set.html).
    The A2600 uses a limited variant of the 6502 called the 6507, which doesn't include BCD instructions and uses a 12bit (4096B) address space: we will thus implement the 6502 instruction set ONLY and remove the BCD instructions
    */

    enum AddressingMode{
        // All the 6502 addressing modes 
        Accumulator,
        Absolute,
        AbsoluteXIndexed,
        AbsoluteYIndexed,
        Immediate,
        Implied,
        Indirect,
        IndirectXIndexed,
        IndirectYIndexed,
        Relative,
        ZeroPage,
        ZeroPageXIndexed,
        ZeroPageYIndexed
    };


    enum InstructionModalities { // USE: some isntructions have specific modalities like Read-Modify-Write that I'd like to account for. 
        //Im not yet 100% familiar with the 6502 ISA so im using an enumto note this in instruction Metadata
        Normal,
        ReadModifyWrite, // NOTE: on NMOS 6502 CPUs, the "write" happens on a seperate cycle
    };

    enum class AdressingModeModality : uint16_t {
        // WHY? Some instructions have specific behavior (eg Read-Modify-Write) in certain addressing Modes, but not others...
        // This allows us to concatenate all 'weird' addressing modes
        Acc = 1 << 0,
        Abs = 1 << 1,
        AbX = 1 << 2,
        AbY = 1 << 3,
        Imm = 1 << 4,
        Imp = 1 << 5,
        Ind = 1 << 6,
        IdX = 1 << 7,
        IdY = 1 << 8,
        Rel = 1 << 9,
        Zpg = 1 << 10,
        ZpX = 1 << 11,
        ZpY = 11 << 12
    };

    using AdressingModeModalityMask = uint16_t;

    enum InstructionMnemonic{ 
        // Common 6502 Assembler mnemonics, for easier debugging
        ADC,    // ADD with Carry
        AND,    // AND with Accumulator
        ASL,    // Arithmetic SHIFT left
        BCC,    // BRANCH on Carry Clear
        BCS,    // BRANCH on Carry Set
        BEQ,    // BRANCH on Equal (zero-zet)
        BIT,    // Bit TEST
        BMI,    // BRANCH on MINUS (negative set)
        BNE,    // BRANCH on Not Equal (Zero clear)
        BPL,    // BRANCH on PLUS (negative clear)
        BRK,    // Break/Interrupt
        BVC,    // BRANCH on Overflow Clear 
        BVS,    // BRANCH on Overflow Set
        CLC,    // CLEAR CARRY
        CLD,    // CLEAR decimal
        CLI,    // CLEAR interrupt disable
        CLV,    // CLEAR Overflow
        CMP,    // COMPARE with Accumulator
        CPX,    // COMPARE with X
        CPY,    // COMPARE with Y
        DEC,    // DECREMENT
        DEX,    // DECREMENT X
        DEY,    // DECREMENT Y
        EOR,    // XOR with Accumulator
        INC,    // INCREMENT
        INX,    // INCREMENT X
        INY,    // INCREMENT Y
        JMP,    // JUMP
        JSR,    // JUMP Subroutine
        LDA,    // LOAD Accumulator
        LDX,    // LOAD X 
        LDY,    // LOAD Y
        LSR,    // Logical SHIFT Right
        NOP,    // No-Operation
        ORA,    // OR with Accumulator
        PHA,    // PUSH Accumulator
        PHP,    // PUSH Processor Status (SR)
        PLA,    // PULL Accumulator
        PLP,    // PULL Processor Status (SR)
        ROL,    // ROTATE Left
        ROR,    // ROTATE Right
        RTI,    // RETURN from Interrupt
        RTS,    // RETURN from Subroutine
        SBC,    // SUBTRACT with Carry
        SEC,    // SET Carry,
        SED,    // SET Decimal
        SEI,    // SET INTERRUPT Disable
        STA,    // STORE Accumulator
        STX,    // STORE Register
        STY,    // STORE Y Register
        TAX,    // TRANSFER Accumulator to X
        TAY,    // TRANSFER Accumulator to Y
        TSX,    // TRANSFER Stack Pointer to X
        TXA,    // TRANSFER X to Accumulator
        TXS,    // TRANSFER X to Stack Pointer
        TYA,    // TRANSFER Y to Accumulator
    };

    struct Instruction{ // Encode all 6502 instruction metadata here 
        // Info about instruction itself
        uint8_t opcode; // pure 6502 binary opcode
        InstructionMnemonic mnemonic; // instruction mnemonic here
        AddressingMode addressMode; // 
        InstructionModalities instructionModalities = InstructionModalities::Normal; //by default, lets assume we dont need to process anything weird
        AdressingModeModalityMask addrModalityMask = 0xFFFF; // NOTE: on function : a 1 denotes the above addressing mode modality is used for the relevant addressing mode.. if 0, assume NORMAL
        uint8_t byteCount; // how many bites does this take
        uint8_t cycleCount; // how many cycles does the instruction take to execute?
        uint8_t additionalCyclesIfPageNotCrossed = 0; // Useful for branching, dictates how many cycles op should take if on same page
        uint8_t additionalCyclesIfPageCrossed = 0; // Particularly important for memory, brach and zero page operations: if computed address is in a different page (eg a different 256B chunk), how many more cycles should execution take?
        // Register level information, write expressions like: static_cast<FlagMask>(StatusFlag::N) | static_cast<FlagMask>(StatusFlag::Z)
        cpu::registers::FlagMask readFlags;
        cpu::registers::FlagMask writeFlags;
        cpu::ChipType CPUBehavior = cpu::hw::ChipType::NMOS6502; //NOTE: the CMOS and NMOS variants of the 6502 perform slightly differently, as does the later variants. 
        //The NMOS variant is notably bugged for JMP indirect instructions, which needs to be accounted for.
        void (CPU::*execute)(const Instruction&); // Structure: this is a pointer to a method in the main CPU class which takes in an instruction
    };

    extern const Instruction opcodeTable[256]; // Declaring an array of instructions for InstructionOps.h... idea is that I can do opcodeTable[Instruction_LDA] or something and get back all relevant info


};
