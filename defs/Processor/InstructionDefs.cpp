/*
* AUTHOR: Emma BOULESTEIX
* DATE: Aug 2026
* PROJECT: A2600 CPU emulator
* FILE: Contains the definitions for each instruction though not the CPU macros (eg CPU::LDA)
*/

#include <array>
#include <stdint.h>
#include <stdlib.h>

#include <Processor/InstructionTypes.h>
#include <Processor/CPURuntimeTypes.h>
#include <Processor/DecoderHelpers.h>


namespace cpu::decoder{
    std::array<cpu::instructions::Instruction, 256> makeOpCodeTable(){
    std::array<cpu::instructions::Instruction, 256> map{};

    //FIXME: All cpu instruction pointers are currently blanked out due to them not being defined. Fix later.
    // ADC (Add Memory to Accumulator with Carry)//
    // A + M + C -> A, C
    // N Z C I D V
    // + + + - - +
        map[0x69] = {
            // Immediate mode
            .opcode = 0x69,
            .mnemonic = cpu::instructions::InstructionMnemonic::ADC,
            .addressMode = cpu::instructions::AddressingMode::Immediate,
            .byteCount = 2,
            .cycleCount = 2,
            .readFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::V),
            //.execute = &CPU::ADC,
        };
        map[0x65] = {
            // Zeropage mode
            .opcode = 0x65,
            .mnemonic = cpu::instructions::InstructionMnemonic::ADC,
            .addressMode = cpu::instructions::AddressingMode::ZeroPage,
            .byteCount = 2,
            .cycleCount = 3,
            .readFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::V),
            //.execute = &CPU::ADC,
        };
        map[0x75] = {
            // Zeropage mode, X
            .opcode = 0x75,
            .mnemonic = cpu::instructions::InstructionMnemonic::ADC,
            .addressMode = cpu::instructions::AddressingMode::ZeroPageXIndexed,
            .byteCount = 2,
            .cycleCount = 4,
            .readFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::V),
            //.execute = &CPU::ADC,
        };
        map[0x6D] = {
            // Absolute Mode
            .opcode = 0x6D,
            .mnemonic = cpu::instructions::InstructionMnemonic::ADC,
            .addressMode = cpu::instructions::AddressingMode::Absolute,
            .byteCount = 3,
            .cycleCount = 4,
            .readFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::V),
            //.execute = &CPU::ADC,
        };
        map[0x7D] = {
            // Absolute Mode, X
            .opcode = 0x7D,
            .mnemonic = cpu::instructions::InstructionMnemonic::ADC,
            .addressMode = cpu::instructions::AddressingMode::AbsoluteXIndexed,
            .byteCount = 3,
            .cycleCount = 4,
            .additionalCyclesIfPageCrossed = 1,
            .readFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::V),
            //.execute = &CPU::ADC,
        };
        map[0x79] = {
            // Absolute Mode, Y
            .opcode = 0x79,
            .mnemonic = cpu::instructions::InstructionMnemonic::ADC,
            .addressMode = cpu::instructions::AddressingMode::AbsoluteYIndexed,
            .byteCount = 3,
            .cycleCount = 4,
            .additionalCyclesIfPageCrossed = 1,
            .readFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::V),
            //.execute = &CPU::ADC,
        };
        map[0x61] = {
            // Indirect Mode, X
            .opcode = 0x61,
            .mnemonic = cpu::instructions::InstructionMnemonic::ADC,
            .addressMode = cpu::instructions::AddressingMode::IndirectXIndexed,
            .byteCount = 2,
            .cycleCount = 6,
            .readFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::V),
            //.execute = &CPU::ADC,
        };
        map[0x71] = {
            // Indirect Mode, Y
            .opcode = 0x71,
            .mnemonic = cpu::instructions::InstructionMnemonic::ADC,
            .addressMode = cpu::instructions::AddressingMode::IndirectYIndexed,
            .byteCount = 2,
            .cycleCount = 5,
            .additionalCyclesIfPageCrossed = 1,
            .readFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::V),
            //.execute = &CPU::ADC,
        };
    // AND (AND Memory with Accumulator)//
    // A AND M -> A
    // N Z C I D V
    // + + - - - -

        map[0x29] = {
            // Immediate
            .opcode = 0x29,
            .mnemonic = cpu::instructions::InstructionMnemonic::AND,
            .addressMode = cpu::instructions::AddressingMode::Immediate,
            .byteCount = 2,
            .cycleCount = 2,
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            //.execute = &CPU::AND,
        };
        map[0x25] = {
            // ZeroPage
            .opcode = 0x25,
            .mnemonic = cpu::instructions::InstructionMnemonic::AND,
            .addressMode = cpu::instructions::AddressingMode::ZeroPage,
            .byteCount = 2,
            .cycleCount = 3,
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            //.execute = &CPU::AND,
        };
        map[0x35] = {
            // ZeroPage, X
            .opcode = 0x35,
            .mnemonic = cpu::instructions::InstructionMnemonic::AND,
            .addressMode = cpu::instructions::AddressingMode::ZeroPageXIndexed,
            .byteCount = 2,
            .cycleCount = 4,
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            //.execute = &CPU::AND,
        };
        map[0x2D] = {
            // Absolute
            .opcode = 0x2D,
            .mnemonic = cpu::instructions::InstructionMnemonic::AND,
            .addressMode = cpu::instructions::AddressingMode::Absolute,
            .byteCount = 3,
            .cycleCount = 4,
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            //.execute = &CPU::AND,
        };
        map[0x3D] = {
            // Absolute X
            .opcode = 0x3D,
            .mnemonic = cpu::instructions::InstructionMnemonic::AND,
            .addressMode = cpu::instructions::AddressingMode::AbsoluteXIndexed,
            .byteCount = 3,
            .cycleCount = 4,
            .additionalCyclesIfPageCrossed = 1,
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            //.execute = &CPU::AND,
        };
        map[0x39] = {
            // Absolute Y
            .opcode = 0x39,
            .mnemonic = cpu::instructions::InstructionMnemonic::AND,
            .addressMode = cpu::instructions::AddressingMode::AbsoluteYIndexed,
            .byteCount = 3,
            .cycleCount = 4,
            .additionalCyclesIfPageCrossed = 1,
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            //.execute = &CPU::AND,
        };
        map[0x21] = {
            // Indirect X
            .opcode = 0x21,
            .mnemonic = cpu::instructions::InstructionMnemonic::AND,
            .addressMode = cpu::instructions::AddressingMode::IndirectXIndexed,
            .byteCount = 2,
            .cycleCount = 6,
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            //.execute = &CPU::AND,
        };
        map[0x31] = {
            // Indirect Y
            .opcode = 0x31,
            .mnemonic = cpu::instructions::InstructionMnemonic::AND,
            .addressMode = cpu::instructions::AddressingMode::IndirectYIndexed,
            .byteCount = 2,
            .cycleCount = 5,
            .additionalCyclesIfPageCrossed = 1,
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            //.execute = &CPU::AND,
        };
    // BCC (Branch on Carry Clear)//
    // BRANCH on C = 0
    // N Z C I D V
    // - - - - - -
        map[0x90] = {
            // Relative
            .opcode = 0x90,
            .mnemonic = cpu::instructions::InstructionMnemonic::BCC,
            .addressMode = cpu::instructions::AddressingMode::Relative,
            .byteCount = 2,
            .cycleCount = 2, //NOTE: DOC says that branch is 2 cycles + 1 if branching to same page and + 2 if branching to different page
            .additionalCyclesIfPageNotCrossed = 1,
            .additionalCyclesIfPageCrossed = 2,
            .readFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            .writeFlags = 0,
            //.execute = &CPU::BCC,
        };
    // BCS (Branch on Carry Set)//
    // BRANCH on C = 1
    // N Z C I D V
    // - - - - - -
        map[0xB0] = {
            // Relative
            .opcode = 0xB0,
            .mnemonic = cpu::instructions::InstructionMnemonic::BCS,
            .addressMode = cpu::instructions::AddressingMode::Relative,
            .byteCount = 2,
            .cycleCount = 2, //NOTE: DOC says that branch is 2 cycles + 1 if branching to same page and + 2 if branching to different page
            .additionalCyclesIfPageNotCrossed = 1,
            .additionalCyclesIfPageCrossed = 2,
            .readFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            .writeFlags = 0,
            //.execute = &CPU::BCS,
        };
    // BEQ (Branch on Result Zero)//
    // BRANCH on Z = 1
    // N Z C I D V
    // - - - - - -
        map[0xF0] = {
            // Relative
            .opcode = 0xF0,
            .mnemonic = cpu::instructions::InstructionMnemonic::BEQ,
            .addressMode = cpu::instructions::AddressingMode::Relative,
            .byteCount = 2,
            .cycleCount = 2, //NOTE: DOC says that branch is 2 cycles + 1 if branching to same page and + 2 if branching to different page
            .additionalCyclesIfPageNotCrossed = 1,
            .additionalCyclesIfPageCrossed = 2,
            .readFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            .writeFlags = 0,
            //.execute = &CPU::BEQ,
        };
    // BIT (Test Bits in Memory with Accumulator)//
    // see documentation
    // N  Z C I D V
    // M7 + - - - M6
        map[0x24] = {
            // Zeropage
            .opcode = 0x24,
            .mnemonic = cpu::instructions::InstructionMnemonic::BIT,
            .addressMode = cpu::instructions::AddressingMode::ZeroPage,
            .byteCount = 2,
            .cycleCount = 3, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::V),
            //.execute = &CPU::BIT,
        };
        map[0x2C] = {
            // absolute
            .opcode = 0x2C,
            .mnemonic = cpu::instructions::InstructionMnemonic::BIT,
            .addressMode = cpu::instructions::AddressingMode::Absolute,
            .byteCount = 3,
            .cycleCount = 4, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::V),
            //.execute = &CPU::BIT,
        };
    // BMI (Branch on Result Minus)//
    // BRANCH on N = 1
    // N Z C I D V
    // - - - - - -
        map[0x30] = {
            // Relative
            .opcode = 0x30,
            .mnemonic = cpu::instructions::InstructionMnemonic::BMI,
            .addressMode = cpu::instructions::AddressingMode::Relative,
            .byteCount = 2,
            .cycleCount = 2, //NOTE: DOC says that branch is 2 cycles + 1 if branching to same page and + 2 if branching to different page
            .additionalCyclesIfPageNotCrossed = 1,
            .additionalCyclesIfPageCrossed = 2,
            .readFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N),
            .writeFlags = 0,
            //.execute = &CPU::BMI,
        };
    // BNE (Branch Not Equal)//
    // BRANCH on Z = 0
    // N Z C I D V
    // - - - - - -
        map[0xD0] = {
            // Relative
            .opcode = 0xD0,
            .mnemonic = cpu::instructions::InstructionMnemonic::BNE,
            .addressMode = cpu::instructions::AddressingMode::Relative,
            .byteCount = 2,
            .cycleCount = 2, //NOTE: DOC says that branch is 2 cycles + 1 if branching to same page and + 2 if branching to different page
            .additionalCyclesIfPageNotCrossed = 1,
            .additionalCyclesIfPageCrossed = 2,
            .readFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            .writeFlags = 0,
            //.execute = &CPU::BNE,
        };
    // BPL (Branch on Result Plus)//
    // BRANCH on N = 0
    // N Z C I D V
    // - - - - - -
        map[0x10] = {
            // Relative
            .opcode = 0x10,
            .mnemonic = cpu::instructions::InstructionMnemonic::BPL,
            .addressMode = cpu::instructions::AddressingMode::Relative,
            .byteCount = 2,
            .cycleCount = 2, //NOTE: DOC says that branch is 2 cycles + 1 if branching to same page and + 2 if branching to different page
            .additionalCyclesIfPageNotCrossed = 1,
            .additionalCyclesIfPageCrossed = 2,
            .readFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N),
            .writeFlags = 0,
            //.execute = &CPU::BPL,
        };
    // BRK (Force Break)//
    // See documentation
    // N Z C I D V
    // - - - 1 - -
    // Push PC, Push SR
        map[0x00] = {
            // Implied
            .opcode = 0x00,
            .mnemonic = cpu::instructions::InstructionMnemonic::BRK,
            .addressMode = cpu::instructions::AddressingMode::Implied,
            .byteCount = 1,
            .cycleCount = 7,
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::I),
            //.execute = &CPU::BRK,
        };
    // BVC (Branch on Overflow Clear)//
    // BRANCH on V = 0
    // N Z C I D V
    // - - - - - -
        map[0x50] = {
            // Relative
            .opcode = 0x50,
            .mnemonic = cpu::instructions::InstructionMnemonic::BVC,
            .addressMode = cpu::instructions::AddressingMode::Relative,
            .byteCount = 2,
            .cycleCount = 2, //NOTE: DOC says that branch is 2 cycles + 1 if branching to same page and + 2 if branching to different page
            .additionalCyclesIfPageNotCrossed = 1,
            .additionalCyclesIfPageCrossed = 2,
            .readFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::V),
            .writeFlags = 0,
            //.execute = &CPU::BVC,
        };
    // BVS (Branch on Overflow Set)//
    // BRANCH on V = 1
    // N Z C I D V
    // - - - - - -
        map[0x70] = {
            // Relative
            .opcode = 0x70,
            .mnemonic = cpu::instructions::InstructionMnemonic::BVS,
            .addressMode = cpu::instructions::AddressingMode::Relative,
            .byteCount = 2,
            .cycleCount = 2, //NOTE: DOC says that branch is 2 cycles + 1 if branching to same page and + 2 if branching to different page
            .additionalCyclesIfPageNotCrossed = 1,
            .additionalCyclesIfPageCrossed = 2,
            .readFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::V),
            .writeFlags = 0,
            //.execute = &CPU::BVS,
        };
    // CLC (Clear Carry FLag)//
    // 0 -> C
    // N Z C I D V
    // - - 0 - - -
        map[0x18] = {
            // Implied
            .opcode = 0x18,
            .mnemonic = cpu::instructions::InstructionMnemonic::CLC,
            .addressMode = cpu::instructions::AddressingMode::Implied,
            .byteCount = 1,
            .cycleCount = 2, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            //.execute = &CPU::CLC,
        };
    // CLD (Clear Decimal Mode)//
    // 0 -> D
    // N Z C I D V
    // - - - - 0 -
        map[0xD8] = {
            // Implied
            .opcode = 0xD8,
            .mnemonic = cpu::instructions::InstructionMnemonic::CLD,
            .addressMode = cpu::instructions::AddressingMode::Implied,
            .byteCount = 1,
            .cycleCount = 2, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::D),
            //.execute = &CPU::CLD,
        };
    // CLI (Clear Interrupt Disable Bit)//
    // 0 -> I
    // N Z C I D V
    // - - - 0 - -
        map[0x58] = {
            // Implied
            .opcode = 0x58,
            .mnemonic = cpu::instructions::InstructionMnemonic::CLI,
            .addressMode = cpu::instructions::AddressingMode::Implied,
            .byteCount = 1,
            .cycleCount = 2, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::I),
            //.execute = &CPU::CLI,
        };
    // CLV (Clear Overflow flag)//
    // 0 -> V
    // N Z C I D V
    // - - - 0 - -
        map[0xB8] = {
            // Implied
            .opcode = 0xB8,
            .mnemonic = cpu::instructions::InstructionMnemonic::CLV,
            .addressMode = cpu::instructions::AddressingMode::Implied,
            .byteCount = 1,
            .cycleCount = 2, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::V),
            //.execute = &CPU::CLV,
        };
    // CMP (Compare Memory with Accumulator)//
    // A - M
    // N Z C I D V
    // + + + - - -
        map[0xC9] = {
            // Immediate
            .opcode = 0xC9,
            .mnemonic = cpu::instructions::InstructionMnemonic::CMP,
            .addressMode = cpu::instructions::AddressingMode::Immediate,
            .byteCount = 2,
            .cycleCount = 2, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            //.execute = &CPU::CMP,
        };
        map[0xC5] = {
            // Zeropage
            .opcode = 0xC5,
            .mnemonic = cpu::instructions::InstructionMnemonic::CMP,
            .addressMode = cpu::instructions::AddressingMode::ZeroPage,
            .byteCount = 2,
            .cycleCount = 3, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            //.execute = &CPU::CMP,
        };
        map[0xD5] = {
            // Zeropage X
            .opcode = 0xD5,
            .mnemonic = cpu::instructions::InstructionMnemonic::CMP,
            .addressMode = cpu::instructions::AddressingMode::ZeroPageXIndexed,
            .byteCount = 2,
            .cycleCount = 4, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            //.execute = &CPU::CMP,
        };
        map[0xCD] = {
            // Absolute
            .opcode = 0xCD,
            .mnemonic = cpu::instructions::InstructionMnemonic::CMP,
            .addressMode = cpu::instructions::AddressingMode::Absolute,
            .byteCount = 3,
            .cycleCount = 4, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            //.execute = &CPU::CMP,
        };
        map[0xDD] = {
            // Absolute X
            .opcode = 0xDD,
            .mnemonic = cpu::instructions::InstructionMnemonic::CMP,
            .addressMode = cpu::instructions::AddressingMode::AbsoluteXIndexed,
            .byteCount = 3,
            .cycleCount = 4, 
            .additionalCyclesIfPageCrossed = 1,
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            //.execute = &CPU::CMP,
        };
        map[0xD9] = {
            // Absolute Y
            .opcode = 0xD9,
            .mnemonic = cpu::instructions::InstructionMnemonic::CMP,
            .addressMode = cpu::instructions::AddressingMode::AbsoluteYIndexed,
            .byteCount = 3,
            .cycleCount = 4, 
            .additionalCyclesIfPageCrossed = 1,
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            //.execute = &CPU::CMP,
        };
        map[0xC1] = {
            // Indirect X
            .opcode = 0xC1,
            .mnemonic = cpu::instructions::InstructionMnemonic::CMP,
            .addressMode = cpu::instructions::AddressingMode::IndirectXIndexed,
            .byteCount = 2,
            .cycleCount = 6, 
            .additionalCyclesIfPageCrossed = 0,
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            //.execute = &CPU::CMP,
        };
        map[0xD1] = {
            // Indirect Y
            .opcode = 0xD1,
            .mnemonic = cpu::instructions::InstructionMnemonic::CMP,
            .addressMode = cpu::instructions::AddressingMode::IndirectYIndexed,
            .byteCount = 2,
            .cycleCount = 5, 
            .additionalCyclesIfPageCrossed = 1,
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            //.execute = &CPU::CMP,
        };
    // CPX (Compare Memory with X)//
    // X - M
    // N Z C I D V
    // + + + - - -
        map[0xE0] = {
            // Immediate
            .opcode = 0xE0,
            .mnemonic = cpu::instructions::InstructionMnemonic::CPX,
            .addressMode = cpu::instructions::AddressingMode::Immediate,
            .byteCount = 2,
            .cycleCount = 2, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            //.execute = &CPU::CPX,
        };
        map[0xE4] = {
            // Zeropage
            .opcode = 0xE4,
            .mnemonic = cpu::instructions::InstructionMnemonic::CPX,
            .addressMode = cpu::instructions::AddressingMode::ZeroPage,
            .byteCount = 2,
            .cycleCount = 3, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            //.execute = &CPU::CPX,
        };
        map[0xEC] = {
            // Absolute
            .opcode = 0xEC,
            .mnemonic = cpu::instructions::InstructionMnemonic::CPX,
            .addressMode = cpu::instructions::AddressingMode::Absolute,
            .byteCount = 3,
            .cycleCount = 4, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            //.execute = &CPU::CPX,
        };
    // DEC (Decrement by one)//
    // M - 1 -> M
    // N Z C I D V
    // + + - - - -
        map[0xC6] = {
            // Zeropage
            .opcode = 0xC6,
            .mnemonic = cpu::instructions::InstructionMnemonic::DEC,
            .addressMode = cpu::instructions::AddressingMode::ZeroPage,
            .byteCount = 2,
            .cycleCount = 5, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            //.execute = &CPU::DEC,
        };
        map[0xD6] = {
            // Zeropage X
            .opcode = 0xD6,
            .mnemonic = cpu::instructions::InstructionMnemonic::DEC,
            .addressMode = cpu::instructions::AddressingMode::ZeroPageXIndexed,
            .byteCount = 2,
            .cycleCount = 6, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            //.execute = &CPU::DEC,
        };
        map[0xCE] = {
            // Absolute
            .opcode = 0xCE,
            .mnemonic = cpu::instructions::InstructionMnemonic::DEC,
            .addressMode = cpu::instructions::AddressingMode::Absolute,
            .byteCount = 3,
            .cycleCount = 6, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            //.execute = &CPU::DEC,
        };
        map[0xDE] = {
            // Absolute X
            .opcode = 0xDE,
            .mnemonic = cpu::instructions::InstructionMnemonic::DEC,
            .addressMode = cpu::instructions::AddressingMode::AbsoluteXIndexed,
            .byteCount = 3,
            .cycleCount = 7, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            //.execute = &CPU::DEC,
        };
    // DEX (Decrement X by one)//
    // X - 1 -> X
    // N Z C I D V
    // + + - - - -
        map[0xCA] = {
            // Implied
            .opcode = 0xCA,
            .mnemonic = cpu::instructions::InstructionMnemonic::DEX,
            .addressMode = cpu::instructions::AddressingMode::Implied,
            .byteCount = 1,
            .cycleCount = 2, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            //.execute = &CPU::DEX,
        };
    // DEY (Decrement Y by one)//
    // Y - 1 -> Y
    // N Z C I D V
    // + + - - - -
        map[0x88] = {
            // Implied
            .opcode = 0x88,
            .mnemonic = cpu::instructions::InstructionMnemonic::DEY,
            .addressMode = cpu::instructions::AddressingMode::Implied,
            .byteCount = 1,
            .cycleCount = 2, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            //.execute = &CPU::DEY,
        };
    // EOR (Exclusive OR with Accumulator)//
    // A XOR M -> A
    // N Z C I D V
    // + + - - - -
        map[0x49] = {
            // Immediate
            .opcode = 0x49,
            .mnemonic = cpu::instructions::InstructionMnemonic::EOR,
            .addressMode = cpu::instructions::AddressingMode::Immediate,
            .instructionModalities = cpu::instructions::InstructionModalities::ReadModifyWrite,
            
            .byteCount = 2,
            .cycleCount = 2, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            //.execute = &CPU::EOR,
        };
        map[0x45] = {
            // ZP
            .opcode = 0x45,
            .mnemonic = cpu::instructions::InstructionMnemonic::EOR,
            .addressMode = cpu::instructions::AddressingMode::ZeroPage,
            .instructionModalities = cpu::instructions::InstructionModalities::ReadModifyWrite,

            .byteCount = 2,
            .cycleCount = 3, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            //.execute = &CPU::EOR,
        };
        map[0x55] = {
            // ZP X
            .opcode = 0x55,
            .mnemonic = cpu::instructions::InstructionMnemonic::EOR,
            .addressMode = cpu::instructions::AddressingMode::ZeroPageXIndexed,
            .instructionModalities = cpu::instructions::InstructionModalities::ReadModifyWrite,
            .byteCount = 2,
            .cycleCount = 4, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            //.execute = &CPU::EOR,
        };
        map[0x4D] = {
            // ABS
            .opcode = 0x4D,
            .mnemonic = cpu::instructions::InstructionMnemonic::EOR,
            .addressMode = cpu::instructions::AddressingMode::Absolute,
            .instructionModalities = cpu::instructions::InstructionModalities::ReadModifyWrite,
            .byteCount = 3,
            .cycleCount = 4, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            //.execute = &CPU::EOR,
        };
        map[0x5D] = {
            // ABS X
            .opcode = 0x5D,
            .mnemonic = cpu::instructions::InstructionMnemonic::EOR,
            .addressMode = cpu::instructions::AddressingMode::AbsoluteXIndexed,
            .instructionModalities = cpu::instructions::InstructionModalities::ReadModifyWrite,
            .byteCount = 3,
            .cycleCount = 4, 
            .additionalCyclesIfPageCrossed = 1,
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            //.execute = &CPU::EOR,
        };
        map[0x59] = {
            // ABS Y
            .opcode = 0x59,
            .mnemonic = cpu::instructions::InstructionMnemonic::EOR,
            .addressMode = cpu::instructions::AddressingMode::AbsoluteYIndexed,
            .instructionModalities = cpu::instructions::InstructionModalities::ReadModifyWrite,
            .byteCount = 3,
            .cycleCount = 4, 
            .additionalCyclesIfPageCrossed = 1,
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            //.execute = &CPU::EOR,
        };
        map[0x41] = {
            // Indirect X
            .opcode = 0x41,
            .mnemonic = cpu::instructions::InstructionMnemonic::EOR,
            .addressMode = cpu::instructions::AddressingMode::IndirectXIndexed,
            .instructionModalities = cpu::instructions::InstructionModalities::ReadModifyWrite,
            .byteCount = 2,
            .cycleCount = 6, 
            .additionalCyclesIfPageCrossed = 0,
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            //.execute = &CPU::EOR,
        };
        map[0x51] = {
            // Indirect Y
            .opcode = 0x51,
            .mnemonic = cpu::instructions::InstructionMnemonic::EOR,
            .addressMode = cpu::instructions::AddressingMode::IndirectYIndexed,
            .instructionModalities = cpu::instructions::InstructionModalities::ReadModifyWrite,
            .byteCount = 2,
            .cycleCount = 5, 
            .additionalCyclesIfPageCrossed = 1,
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            //.execute = &CPU::EOR,
        };
    // INC (INCREMENT Memory by One)//
    // M + 1 -> M
    // N Z C I D V
    // + + - - - -
        map[0xE6] = {
            // Zeropage
            .opcode = 0xE6,
            .mnemonic = cpu::instructions::InstructionMnemonic::INC,
            .addressMode = cpu::instructions::AddressingMode::ZeroPage,
            .instructionModalities = cpu::instructions::InstructionModalities::ReadModifyWrite,
            .byteCount = 2,
            .cycleCount = 5, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            //.execute = &CPU::INC,
        };
        map[0xF6] = {
            // Zeropage X
            .opcode = 0xF6,
            .mnemonic = cpu::instructions::InstructionMnemonic::INC,
            .addressMode = cpu::instructions::AddressingMode::ZeroPageXIndexed,
            .instructionModalities = cpu::instructions::InstructionModalities::ReadModifyWrite,
            .byteCount = 2,
            .cycleCount = 6, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            //.execute = &CPU::INC,
        };
        map[0xEE] = {
            // Absolute
            .opcode = 0xEE,
            .mnemonic = cpu::instructions::InstructionMnemonic::INC,
            .addressMode = cpu::instructions::AddressingMode::Absolute,
            .instructionModalities = cpu::instructions::InstructionModalities::ReadModifyWrite,
            .byteCount = 3,
            .cycleCount = 6, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            //.execute = &CPU::INC,
        };
        map[0xFE] = {
            // Absolute X
            .opcode = 0xFE,
            .mnemonic = cpu::instructions::InstructionMnemonic::INC,
            .addressMode = cpu::instructions::AddressingMode::AbsoluteXIndexed,
            .instructionModalities = cpu::instructions::InstructionModalities::ReadModifyWrite,
            .byteCount = 3,
            .cycleCount = 7, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            //.execute = &CPU::INC,
        };
    // INX (INCREMENT X by One)//
    // X + 1 -> X
    // N Z C I D V
    // + + - - - -
        map[0xE8] = {
            // Implied
            .opcode = 0xE8,
            .mnemonic = cpu::instructions::InstructionMnemonic::INX,
            .addressMode = cpu::instructions::AddressingMode::Implied,
            .byteCount = 1,
            .cycleCount = 2, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            //.execute = &CPU::INX,
        };
    // INY (INCREMENT Y by One)//
    // Y + 1 -> Y
    // N Z C I D V
    // + + - - - -
        map[0xC8] = {
            // Implied
            .opcode = 0xC8,
            .mnemonic = cpu::instructions::InstructionMnemonic::INY,
            .addressMode = cpu::instructions::AddressingMode::Implied,
            .byteCount = 1,
            .cycleCount = 2, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            //.execute = &CPU::INY,
        };

    // JMP (Jump to new location)//
    // Operand first byte -> PCL, operand second byte -> PCH
    // N Z C I D V
    // - - - - - -
        map[0x4C] = {
            // absolute
            .opcode = 0x4C,
            .mnemonic = cpu::instructions::InstructionMnemonic::JMP,
            .addressMode = cpu::instructions::AddressingMode::Absolute,
            .byteCount = 3,
            .cycleCount = 3, 
            .readFlags = 0,
            .writeFlags = 0,
            //.execute = &CPU::INY,
        };

        map[0x6C] = {
            // indirect
            .opcode = 0x6C,
            .mnemonic = cpu::instructions::InstructionMnemonic::JMP,
            .addressMode = cpu::instructions::AddressingMode::Indirect,
            .byteCount = 3,
            .cycleCount = 5, 
            .additionalCyclesIfPageCrossed = 1,
            .readFlags = 0,
            .writeFlags = 0,
            .CPUBehavior = ChipType::NMOS6502, // NMOS chip has the JMP indirect bug 
            //.execute = &CPU::INY,
        };

    // JSR (Jump to subroutine + save return address)//
    // PUSH PC+2
    // Operand first byte -> PCL, operand second byte -> PCH
    // N Z C I D V
    // - - - - - -
        map[0x20] = {
            // absolute
            .opcode = 0x20,
            .mnemonic = cpu::instructions::InstructionMnemonic::JSR,
            .addressMode = cpu::instructions::AddressingMode::Absolute,
            .byteCount = 3,
            .cycleCount = 6, 
            .readFlags = 0,
            .writeFlags = 0,
            //.execute = &CPU::INY,
        };
    // LDA (Load Accumulator with Memory)//
    // M -> A
    // N Z C I D V
    // + + - - - -
        map[0xA9] = {
            // immediate
            .opcode = 0xA9,
            .mnemonic = cpu::instructions::InstructionMnemonic::LDA,
            .addressMode = cpu::instructions::AddressingMode::Immediate,
            .byteCount = 2,
            .cycleCount = 2, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            //.execute = &CPU::INY,
        };
        map[0xA5] = {
            // zeropage
            .opcode = 0xA5,
            .mnemonic = cpu::instructions::InstructionMnemonic::LDA,
            .addressMode = cpu::instructions::AddressingMode::ZeroPage,
            .byteCount = 2,
            .cycleCount = 3, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            //.execute = &CPU::INY,
        };
        map[0xB5] = {
            // ZP X
            .opcode = 0xB5,
            .mnemonic = cpu::instructions::InstructionMnemonic::LDA,
            .addressMode = cpu::instructions::AddressingMode::ZeroPageXIndexed,
            .byteCount = 2,
            .cycleCount = 4, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            //.execute = &CPU::INY,
        };

        map[0xAD] = {
            // ABS
            .opcode = 0xAD,
            .mnemonic = cpu::instructions::InstructionMnemonic::LDA,
            .addressMode = cpu::instructions::AddressingMode::Absolute,
            .byteCount = 3,
            .cycleCount = 4, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            //.execute = &CPU::INY,
        };

        map[0xBD] = {
            // ABS X
            .opcode = 0xBD,
            .mnemonic = cpu::instructions::InstructionMnemonic::LDA,
            .addressMode = cpu::instructions::AddressingMode::AbsoluteXIndexed,
            .byteCount = 3,
            .cycleCount = 4,
            .additionalCyclesIfPageCrossed = 1, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            //.execute = &CPU::INY,
        };

        map[0xB9] = {
            // ABS Y
            .opcode = 0xB9,
            .mnemonic = cpu::instructions::InstructionMnemonic::LDA,
            .addressMode = cpu::instructions::AddressingMode::AbsoluteYIndexed,
            .byteCount = 3,
            .cycleCount = 4,
            .additionalCyclesIfPageCrossed = 1, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            //.execute = &CPU::INY,
        };

        map[0xA1] = {
            // ABS X
            .opcode = 0xA1,
            .mnemonic = cpu::instructions::InstructionMnemonic::LDA,
            .addressMode = cpu::instructions::AddressingMode::IndirectXIndexed,
            .byteCount = 2,
            .cycleCount = 6,
            .additionalCyclesIfPageCrossed = 0, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            //.execute = &CPU::INY,
        };

        map[0xB1] = {
            // ABS Y
            .opcode = 0xB1,
            .mnemonic = cpu::instructions::InstructionMnemonic::LDA,
            .addressMode = cpu::instructions::AddressingMode::IndirectYIndexed,
            .byteCount = 2,
            .cycleCount = 5,
            .additionalCyclesIfPageCrossed = 1, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            //.execute = &CPU::INY,
        };

    // LDX (Load Accumulator with Memory)//
    // M -> X
    // N Z C I D V
    // + + - - - -
        map[0xA2] = {
            // immediate
            .opcode = 0xA2,
            .mnemonic = cpu::instructions::InstructionMnemonic::LDX,
            .addressMode = cpu::instructions::AddressingMode::Immediate,
            .byteCount = 2,
            .cycleCount = 2, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            //.execute = &CPU::INY,
        };
        map[0xA6] = {
            // zeropage
            .opcode = 0xA6,
            .mnemonic = cpu::instructions::InstructionMnemonic::LDX,
            .addressMode = cpu::instructions::AddressingMode::ZeroPage,
            .byteCount = 2,
            .cycleCount = 3, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            //.execute = &CPU::INY,
        };
        map[0xB6] = {
            // ZP Y
            .opcode = 0xB6,
            .mnemonic = cpu::instructions::InstructionMnemonic::LDX,
            .addressMode = cpu::instructions::AddressingMode::ZeroPageYIndexed,
            .byteCount = 2,
            .cycleCount = 4, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            //.execute = &CPU::INY,
        };

        map[0xAE] = {
            // ABS
            .opcode = 0xAE,
            .mnemonic = cpu::instructions::InstructionMnemonic::LDX,
            .addressMode = cpu::instructions::AddressingMode::Absolute,
            .byteCount = 3,
            .cycleCount = 4, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            //.execute = &CPU::INY,
        };

        map[0xBE] = {
            // ABS Y
            .opcode = 0xBE,
            .mnemonic = cpu::instructions::InstructionMnemonic::LDX,
            .addressMode = cpu::instructions::AddressingMode::AbsoluteYIndexed,
            .byteCount = 3,
            .cycleCount = 4,
            .additionalCyclesIfPageCrossed = 1, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            //.execute = &CPU::INY,
        };
    // LDY (Load Y with Memory)//
    // M -> Y
    // N Z C I D V
    // + + - - - -
        map[0xA0] = {
            // immediate
            .opcode = 0xA0,
            .mnemonic = cpu::instructions::InstructionMnemonic::LDY,
            .addressMode = cpu::instructions::AddressingMode::Immediate,
            .byteCount = 2,
            .cycleCount = 2, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            //.execute = &CPU::INY,
        };
        map[0xA4] = {
            // zeropage
            .opcode = 0xA4,
            .mnemonic = cpu::instructions::InstructionMnemonic::LDY,
            .addressMode = cpu::instructions::AddressingMode::ZeroPage,
            .byteCount = 2,
            .cycleCount = 3, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            //.execute = &CPU::INY,
        };
        map[0xB4] = {
            // ZP X
            .opcode = 0xB4,
            .mnemonic = cpu::instructions::InstructionMnemonic::LDY,
            .addressMode = cpu::instructions::AddressingMode::ZeroPageXIndexed,
            .byteCount = 2,
            .cycleCount = 4, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            //.execute = &CPU::INY,
        };

        map[0xAC] = {
            // ABS
            .opcode = 0xAC,
            .mnemonic = cpu::instructions::InstructionMnemonic::LDY,
            .addressMode = cpu::instructions::AddressingMode::Absolute,
            .byteCount = 3,
            .cycleCount = 4, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            //.execute = &CPU::INY,
        };

        map[0xBC] = {
            // ABS X
            .opcode = 0xBC,
            .mnemonic = cpu::instructions::InstructionMnemonic::LDY,
            .addressMode = cpu::instructions::AddressingMode::AbsoluteXIndexed,
            .byteCount = 3,
            .cycleCount = 4,
            .additionalCyclesIfPageCrossed = 1, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            //.execute = &CPU::INY,
        };
    // LSR (Shift One bit Right, memory or accumulator)//
    // 0 -> [76543210] -> C
    // N Z C I D V
    // 0 + + - - -
        map[0x4A] = {
            // Accumulator
            .opcode = 0x4A,
            .mnemonic = cpu::instructions::InstructionMnemonic::LSR,
            .addressMode = cpu::instructions::AddressingMode::Accumulator,
            .byteCount = 1,
            .cycleCount = 2, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            //.execute = &CPU::INY,
        };
        map[0x46] = {
            // zeropage
            .opcode = 0x46,
            .mnemonic = cpu::instructions::InstructionMnemonic::LSR,
            .addressMode = cpu::instructions::AddressingMode::ZeroPage,
            .byteCount = 2,
            .cycleCount = 5, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            //.execute = &CPU::INY,
        };
        map[0x56] = {
            // ZP X
            .opcode = 0x56,
            .mnemonic = cpu::instructions::InstructionMnemonic::LSR,
            .addressMode = cpu::instructions::AddressingMode::ZeroPageXIndexed,
            .byteCount = 2,
            .cycleCount = 6, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            //.execute = &CPU::INY,
        };

        map[0x4E] = {
            // ABS
            .opcode = 0x4E,
            .mnemonic = cpu::instructions::InstructionMnemonic::LSR,
            .addressMode = cpu::instructions::AddressingMode::Absolute,
            .byteCount = 3,
            .cycleCount = 6, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            //.execute = &CPU::INY,
        };

        map[0x5E] = {
            // ABS X
            .opcode = 0x5E,
            .mnemonic = cpu::instructions::InstructionMnemonic::LSR,
            .addressMode = cpu::instructions::AddressingMode::AbsoluteXIndexed,
            .byteCount = 3,
            .cycleCount = 7,
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            //.execute = &CPU::INY,
        }; 
    // NOP (No Operation)//   
    // N Z C I D V
    // - - - - - -
        map[0xEA] = {
            // Accumulator
            .opcode = 0xEA,
            .mnemonic = cpu::instructions::InstructionMnemonic::NOP,
            .addressMode = cpu::instructions::AddressingMode::Implied,
            .byteCount = 1,
            .cycleCount = 2, 
            .readFlags = 0,
            .writeFlags = 0,
            //.execute = &CPU::INY,
        }; 
    // OR ( OR with Accumulator)//
    // A OR M -> A
    // N Z C I D V
    // + + - - - -
        map[0x09] = {
            // Immediate
            .opcode = 0x09,
            .mnemonic = cpu::instructions::InstructionMnemonic::ORA,
            .addressMode = cpu::instructions::AddressingMode::Immediate,
            .byteCount = 2,
            .cycleCount = 2, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            //.execute = &CPU::EOR,
        };
        map[0x05] = {
            // ZP
            .opcode = 0x05,
            .mnemonic = cpu::instructions::InstructionMnemonic::ORA,
            .addressMode = cpu::instructions::AddressingMode::ZeroPage,
            .byteCount = 2,
            .cycleCount = 3, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            //.execute = &CPU::EOR,
        };
        map[0x15] = {
            // ZP X
            .opcode = 0x15,
            .mnemonic = cpu::instructions::InstructionMnemonic::ORA,
            .addressMode = cpu::instructions::AddressingMode::ZeroPageXIndexed,
            .byteCount = 2,
            .cycleCount = 4, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            //.execute = &CPU::EOR,
        };
        map[0x0D] = {
            // ABS
            .opcode = 0x0D,
            .mnemonic = cpu::instructions::InstructionMnemonic::ORA,
            .addressMode = cpu::instructions::AddressingMode::Absolute,
            .byteCount = 3,
            .cycleCount = 4, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            //.execute = &CPU::EOR,
        };
        map[0x1D] = {
            // ABS X
            .opcode = 0x1D,
            .mnemonic = cpu::instructions::InstructionMnemonic::ORA,
            .addressMode = cpu::instructions::AddressingMode::AbsoluteXIndexed,
            .byteCount = 3,
            .cycleCount = 4, 
            .additionalCyclesIfPageCrossed = 1,
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            //.execute = &CPU::EOR,
        };
        map[0x19] = {
            // ABS Y
            .opcode = 0x19,
            .mnemonic = cpu::instructions::InstructionMnemonic::ORA,
            .addressMode = cpu::instructions::AddressingMode::AbsoluteYIndexed,
            .byteCount = 3,
            .cycleCount = 4, 
            .additionalCyclesIfPageCrossed = 1,
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            //.execute = &CPU::EOR,
        };
        map[0x01] = {
            // Indirect X
            .opcode = 0x01,
            .mnemonic = cpu::instructions::InstructionMnemonic::ORA,
            .addressMode = cpu::instructions::AddressingMode::IndirectXIndexed,
            .byteCount = 2,
            .cycleCount = 6, 
            .additionalCyclesIfPageCrossed = 0,
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            //.execute = &CPU::EOR,
        };
        map[0x11] = {
            // Indirect Y
            .opcode = 0x11,
            .mnemonic = cpu::instructions::InstructionMnemonic::ORA,
            .addressMode = cpu::instructions::AddressingMode::IndirectYIndexed,
            .byteCount = 2,
            .cycleCount = 5, 
            .additionalCyclesIfPageCrossed = 1,
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            //.execute = &CPU::EOR,
        }; 
        
    // PHA (Push Accumulator on Stack)//
    // Push A
    // N Z C I D V
    // - - - - - -
        map[0x48] = {
            // Implied
            .opcode = 0x48,
            .mnemonic = cpu::instructions::InstructionMnemonic::PHA,
            .addressMode = cpu::instructions::AddressingMode::Implied,
            .byteCount = 1,
            .cycleCount = 3, 
            .readFlags = 0,
            .writeFlags = 0,
            //.execute = &CPU::EOR,
        };
    // PHP (Push Process Status on Stack)//
    // Push SR
    // N Z C I D V
    // - - - - - -
        map[0x08] = {
            // Implied
            .opcode = 0x08,
            .mnemonic = cpu::instructions::InstructionMnemonic::PHP,
            .addressMode = cpu::instructions::AddressingMode::Implied,
            .byteCount = 1,
            .cycleCount = 3, 
            .readFlags = 0xFF,
            .writeFlags = 0,
            //.execute = &CPU::EOR,
        };
    // PLA (Push Accumulator on Stack)//
    // Push A
    // N Z C I D V
    // + + - - - -
        map[0x68] = {
            // Implied
            .opcode = 0x68,
            .mnemonic = cpu::instructions::InstructionMnemonic::PLA,
            .addressMode = cpu::instructions::AddressingMode::Implied,
            .byteCount = 1,
            .cycleCount = 4, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            //.execute = &CPU::EOR,
        };
    // PLP (Pull Process Status on Stack)//
    // Pull SR
    
        map[0x28] = {
            // Implied
            .opcode = 0x28,
            .mnemonic = cpu::instructions::InstructionMnemonic::PLP,
            .addressMode = cpu::instructions::AddressingMode::Implied,
            .byteCount = 1,
            .cycleCount = 4, 
            .readFlags = 0,
            .writeFlags = 0xFF,
            //.execute = &CPU::EOR,
        };

    // ROR (Rotate one right)//
    // C -> [76543210] -> C
    // N Z C I D V
    // + + + - - -
        map[0x6A] = {
            // Accumulator
            .opcode = 0x6A,
            .mnemonic = cpu::instructions::InstructionMnemonic::ROR,
            .addressMode = cpu::instructions::AddressingMode::Accumulator,
            .byteCount = 1,
            .cycleCount = 2, 
            .readFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            //.execute = &CPU::EOR,
        };
        map[0x66] = {
            // ZP
            .opcode = 0x66,
            .mnemonic = cpu::instructions::InstructionMnemonic::ROR,
            .addressMode = cpu::instructions::AddressingMode::ZeroPage,
            .byteCount = 2,
            .cycleCount = 5, 
            .readFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            //.execute = &CPU::EOR,
        };
        map[0x76] = {
            // ZP X
            .opcode = 0x76,
            .mnemonic = cpu::instructions::InstructionMnemonic::ROR,
            .addressMode = cpu::instructions::AddressingMode::ZeroPageXIndexed,
            .byteCount = 2,
            .cycleCount = 6, 
            .readFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            //.execute = &CPU::EOR,
        };
        map[0x6E] = {
            // ABS
            .opcode = 0x6E,
            .mnemonic = cpu::instructions::InstructionMnemonic::ROR,
            .addressMode = cpu::instructions::AddressingMode::Absolute,
            .byteCount = 3,
            .cycleCount = 6, 
            .readFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            //.execute = &CPU::EOR,
        };
        map[0x7E] = {
            // ABS X
            .opcode = 0x7E,
            .mnemonic = cpu::instructions::InstructionMnemonic::ROR,
            .addressMode = cpu::instructions::AddressingMode::AbsoluteXIndexed,
            .byteCount = 3,
            .cycleCount = 7, 
            .readFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            //.execute = &CPU::EOR,
        };
    // ROL (Rotate one left)//
    // C <- [76543210] <- C
    // N Z C I D V
    // + + + - - -
        map[0x2A] = {
            // Accumulator
            .opcode = 0x2A,
            .mnemonic = cpu::instructions::InstructionMnemonic::ROL,
            .addressMode = cpu::instructions::AddressingMode::Accumulator,
            .instructionModalities = cpu::instructions::InstructionModalities::ReadModifyWrite,
            .byteCount = 1,
            .cycleCount = 2, 
            .readFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            //.execute = &CPU::EOR,
        };
        map[0x26] = {
            // ZP
            .opcode = 0x26,
            .mnemonic = cpu::instructions::InstructionMnemonic::ROL,
            .addressMode = cpu::instructions::AddressingMode::ZeroPage,
            .instructionModalities = cpu::instructions::InstructionModalities::ReadModifyWrite,
            .byteCount = 2,
            .cycleCount = 5, 
            .readFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            //.execute = &CPU::EOR,
        };
        map[0x36] = {
            // ZP X
            .opcode = 0x36,
            .mnemonic = cpu::instructions::InstructionMnemonic::ROL,
            .addressMode = cpu::instructions::AddressingMode::ZeroPageXIndexed,
            .instructionModalities = cpu::instructions::InstructionModalities::ReadModifyWrite,
            .byteCount = 2,
            .cycleCount = 6, 
            .readFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            //.execute = &CPU::EOR,
        };
        map[0x2E] = {
            // ABS
            .opcode = 0x2E,
            .mnemonic = cpu::instructions::InstructionMnemonic::ROL,
            .addressMode = cpu::instructions::AddressingMode::Absolute,
            .instructionModalities = cpu::instructions::InstructionModalities::ReadModifyWrite,
            .byteCount = 3,
            .cycleCount = 6, 
            .readFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            //.execute = &CPU::EOR,
        };
        map[0x3E] = {
            // ABS X
            .opcode = 0x3E,
            .mnemonic = cpu::instructions::InstructionMnemonic::ROL,
            .addressMode = cpu::instructions::AddressingMode::AbsoluteXIndexed,
            .instructionModalities = cpu::instructions::InstructionModalities::ReadModifyWrite,
            .byteCount = 3,
            .cycleCount = 7, 
            .readFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            //.execute = &CPU::EOR,
        };

    // RTI (Return from Interrupt)//
    //The status register is pulled with the break flag
    //and bit 5 ignored. Then PC is pulled from the stack.
        map[0x40] = {
            // Implied
            .opcode = 0x40,
            .mnemonic = cpu::instructions::InstructionMnemonic::RTI,
            .addressMode = cpu::instructions::AddressingMode::Implied,
            .byteCount = 1,
            .cycleCount = 6, 
            .readFlags = 0,
            .writeFlags = 0xFF,
            //.execute = &CPU::EOR,
        };
    // RTS (Return from Suboutine)//
    // pull PC, PC+1 -> PC
        map[0x60] = {
            // Implied
            .opcode = 0x60,
            .mnemonic = cpu::instructions::InstructionMnemonic::RTS,
            .addressMode = cpu::instructions::AddressingMode::Implied,
            .byteCount = 1,
            .cycleCount = 6, 
            .readFlags = 0,
            .writeFlags = 0,
            //.execute = &CPU::EOR,
        };   
    
    // SBC (Subtract Memory from Accumulator with Borrow)//
    // A - M - C̅ -> A
    // N Z C I D V
    // + + + - - +
        map[0xE9] = {
            // Immediate
            .opcode = 0xE9,
            .mnemonic = cpu::instructions::InstructionMnemonic::SBC,
            .addressMode = cpu::instructions::AddressingMode::Immediate,
            .byteCount = 2,
            .cycleCount = 2, 
            .readFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::V),
            //.execute = &CPU::EOR,
        };
        map[0xE5] = {
            // ZP
            .opcode = 0xE5,
            .mnemonic = cpu::instructions::InstructionMnemonic::SBC,
            .addressMode = cpu::instructions::AddressingMode::ZeroPage,
            .byteCount = 2,
            .cycleCount = 3, 
            .readFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::V),
            //.execute = &CPU::EOR,
        };
        map[0xF5] = {
            // ZP X
            .opcode = 0xF5,
            .mnemonic = cpu::instructions::InstructionMnemonic::SBC,
            .addressMode = cpu::instructions::AddressingMode::ZeroPageXIndexed,
            .byteCount = 2,
            .cycleCount = 4, 
            .readFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::V),
            //.execute = &CPU::EOR,
        };
        map[0xED] = {
            // ABS
            .opcode = 0xED,
            .mnemonic = cpu::instructions::InstructionMnemonic::SBC,
            .addressMode = cpu::instructions::AddressingMode::Absolute,
            .byteCount = 3,
            .cycleCount = 4, 
            .readFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::V),
            //.execute = &CPU::EOR,
        };
        map[0xFD] = {
            // ABS X
            .opcode = 0xFD,
            .mnemonic = cpu::instructions::InstructionMnemonic::SBC,
            .addressMode = cpu::instructions::AddressingMode::AbsoluteXIndexed,
            .byteCount = 3,
            .cycleCount = 4, 
            .additionalCyclesIfPageCrossed = 1,
            .readFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::V),
            //.execute = &CPU::EOR,
        };
        map[0xF9] = {
            // ABS Y
            .opcode = 0xF9,
            .mnemonic = cpu::instructions::InstructionMnemonic::SBC,
            .addressMode = cpu::instructions::AddressingMode::AbsoluteYIndexed,
            .byteCount = 3,
            .cycleCount = 4, 
            .additionalCyclesIfPageCrossed = 1,
            .readFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::V),
            //.execute = &CPU::EOR,
        };
        map[0xE1] = {
            // Indirect X
            .opcode = 0xE1,
            .mnemonic = cpu::instructions::InstructionMnemonic::SBC,
            .addressMode = cpu::instructions::AddressingMode::IndirectXIndexed,
            .byteCount = 2,
            .cycleCount = 6, 
            .additionalCyclesIfPageCrossed = 0,
            .readFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::V),
            //.execute = &CPU::EOR,
        };
        map[0xF1] = {
            // Indirect Y
            .opcode = 0xF1,
            .mnemonic = cpu::instructions::InstructionMnemonic::SBC,
            .addressMode = cpu::instructions::AddressingMode::IndirectYIndexed,
            .byteCount = 2,
            .cycleCount = 5, 
            .additionalCyclesIfPageCrossed = 1,
            .readFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::V),
            //.execute = &CPU::EOR,
        }; 
    // SEC (SET carry flag)//
    // 1 -> C
    // N Z C I D V
    // - - 1 - - -
        map[0x38] = {
            // Implied
            .opcode = 0x38,
            .mnemonic = cpu::instructions::InstructionMnemonic::SEC,
            .addressMode = cpu::instructions::AddressingMode::Implied,
            .byteCount = 1,
            .cycleCount = 2, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            //.execute = &CPU::EOR,
        }; 
    // SED (SET Decimal flag)//
    // 1 -> D
    // N Z C I D V
    // - - - - 1 -
        map[0xF8] = {
            // Implied
            .opcode = 0xF8,
            .mnemonic = cpu::instructions::InstructionMnemonic::SED,
            .addressMode = cpu::instructions::AddressingMode::Implied,
            .byteCount = 1,
            .cycleCount = 2, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::D),
            //.execute = &CPU::EOR,
        }; 
    // SEI (SET Interrupt disable flag)//
    // 1 -> I
    // N Z C I D V
    // - - - 1 - -
        map[0x78] = {
            // Implied
            .opcode = 0x78,
            .mnemonic = cpu::instructions::InstructionMnemonic::SEI,
            .addressMode = cpu::instructions::AddressingMode::Implied,
            .byteCount = 1,
            .cycleCount = 2, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::I),
            //.execute = &CPU::EOR,
        }; 
    // STA ( Store Accumulator in Memory)//
    // A -> M
    // N Z C I D V
    // - - - - - -

        map[0x85] = {
            // ZP
            .opcode = 0x85,
            .mnemonic = cpu::instructions::InstructionMnemonic::STA,
            .addressMode = cpu::instructions::AddressingMode::ZeroPage,
            .byteCount = 2,
            .cycleCount = 3, 
            .readFlags = 0,
            .writeFlags = 0,
            //.execute = &CPU::EOR,
        };
        map[0x95] = {
            // ZP X
            .opcode = 0x95,
            .mnemonic = cpu::instructions::InstructionMnemonic::STA,
            .addressMode = cpu::instructions::AddressingMode::ZeroPageXIndexed,
            .byteCount = 2,
            .cycleCount = 4, 
            .readFlags = 0,
            .writeFlags = 0,
            //.execute = &CPU::EOR,
        };
        map[0x8D] = {
            // ABS
            .opcode = 0x8D,
            .mnemonic = cpu::instructions::InstructionMnemonic::STA,
            .addressMode = cpu::instructions::AddressingMode::Absolute,
            .byteCount = 3,
            .cycleCount = 4, 
            .readFlags = 0,
            .writeFlags = 0,
            //.execute = &CPU::EOR,
        };
        map[0x9D] = {
            // ABS X
            .opcode = 0x9D,
            .mnemonic = cpu::instructions::InstructionMnemonic::STA,
            .addressMode = cpu::instructions::AddressingMode::AbsoluteXIndexed,
            .byteCount = 3,
            .cycleCount = 5, 
            .additionalCyclesIfPageCrossed = 0,
            .readFlags = 0,
            .writeFlags = 0,
            //.execute = &CPU::EOR,
        };
        map[0x99] = {
            // ABS Y
            .opcode = 0x99,
            .mnemonic = cpu::instructions::InstructionMnemonic::STA,
            .addressMode = cpu::instructions::AddressingMode::AbsoluteYIndexed,
            .byteCount = 3,
            .cycleCount = 5, 
            .additionalCyclesIfPageCrossed = 0,
            .readFlags = 0,
            .writeFlags = 0,
            //.execute = &CPU::EOR,
        };
        map[0x81] = {
            // Indirect X
            .opcode = 0x81,
            .mnemonic = cpu::instructions::InstructionMnemonic::STA,
            .addressMode = cpu::instructions::AddressingMode::IndirectXIndexed,
            .byteCount = 2,
            .cycleCount = 6, 
            .additionalCyclesIfPageCrossed = 0,
            .readFlags = 0,
            .writeFlags = 0,
            //.execute = &CPU::EOR,
        };
        map[0x91] = {
            // Indirect Y
            .opcode = 0x91,
            .mnemonic = cpu::instructions::InstructionMnemonic::STA,
            .addressMode = cpu::instructions::AddressingMode::IndirectYIndexed,
            .byteCount = 2,
            .cycleCount = 6, 
            .additionalCyclesIfPageCrossed = 0,
            .readFlags = 0,
            .writeFlags = 0,
            //.execute = &CPU::EOR,
        }; 
    
    // STX (Store Index X in Memory)//
    // X -> M
    // N Z C I D V
    // - - - - - -

        map[0x86] = {
            // ZP
            .opcode = 0x86,
            .mnemonic = cpu::instructions::InstructionMnemonic::STX,
            .addressMode = cpu::instructions::AddressingMode::ZeroPage,
            .byteCount = 2,
            .cycleCount = 3, 
            .readFlags = 0,
            .writeFlags = 0,
            //.execute = &CPU::EOR,
        };
        map[0x96] = {
            // ZP Y
            .opcode = 0x96,
            .mnemonic = cpu::instructions::InstructionMnemonic::STX,
            .addressMode = cpu::instructions::AddressingMode::ZeroPageYIndexed,
            .byteCount = 2,
            .cycleCount = 4, 
            .readFlags = 0,
            .writeFlags = 0,
            //.execute = &CPU::EOR,
        };
        map[0x8E] = {
            // ABS
            .opcode = 0x8E,
            .mnemonic = cpu::instructions::InstructionMnemonic::STX,
            .addressMode = cpu::instructions::AddressingMode::Absolute,
            .byteCount = 3,
            .cycleCount = 4, 
            .readFlags = 0,
            .writeFlags = 0,
            //.execute = &CPU::EOR,
        };
    // STY (Store Index Y in Memory)//
    // Y -> M
    // N Z C I D V
    // - - - - - -

        map[0x84] = {
            // ZP
            .opcode = 0x84,
            .mnemonic = cpu::instructions::InstructionMnemonic::STY,
            .addressMode = cpu::instructions::AddressingMode::ZeroPage,
            .byteCount = 2,
            .cycleCount = 3, 
            .readFlags = 0,
            .writeFlags = 0,
            //.execute = &CPU::EOR,
        };
        map[0x94] = {
            // ZP X
            .opcode = 0x94,
            .mnemonic = cpu::instructions::InstructionMnemonic::STY,
            .addressMode = cpu::instructions::AddressingMode::ZeroPageXIndexed,
            .byteCount = 2,
            .cycleCount = 4, 
            .readFlags = 0,
            .writeFlags = 0,
            //.execute = &CPU::EOR,
        };
        map[0x8C] = {
            // ABS
            .opcode = 0x8C,
            .mnemonic = cpu::instructions::InstructionMnemonic::STY,
            .addressMode = cpu::instructions::AddressingMode::Absolute,
            .byteCount = 3,
            .cycleCount = 4, 
            .readFlags = 0,
            .writeFlags = 0,
            //.execute = &CPU::EOR,
        };
    // TAX (  Transfer Accumulator to Index X)//
    // A -> X
    // N Z C I D V
    // + + - - - -
        map[0xAA] = {
            // Implied
            .opcode = 0xAA,
            .mnemonic = cpu::instructions::InstructionMnemonic::TAX,
            .addressMode = cpu::instructions::AddressingMode::Implied,
            .byteCount = 1,
            .cycleCount = 2, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            //.execute = &CPU::EOR,
        }; 
    // TAY (Transfer Accumulator to Index Y)//
    // A -> Y
    // N Z C I D V
    // + + - - - -
        map[0xA8] = {
            // Implied
            .opcode = 0xA8,
            .mnemonic = cpu::instructions::InstructionMnemonic::TAY,
            .addressMode = cpu::instructions::AddressingMode::Implied,
            .byteCount = 1,
            .cycleCount = 2, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            //.execute = &CPU::EOR,
        }; 
    // TXS (Transfer Index X to Stack Register)//
    // SP -> X
    // N Z C I D V
    // - - - - - -
        map[0x9A] = {
            // Implied
            .opcode = 0x9A,
            .mnemonic = cpu::instructions::InstructionMnemonic::TXS,
            .addressMode = cpu::instructions::AddressingMode::Implied,
            .byteCount = 1,
            .cycleCount = 2, 
            .readFlags = 0,
            .writeFlags = 0,
            //.execute = &CPU::EOR,
        }; 
    // TYA (Transfer Index Y to Stack Register)//
    // SP -> X
    // N Z C I D V
    // + + - - - -
        map[0x98] = {
            // Implied
            .opcode = 0x98,
            .mnemonic = cpu::instructions::InstructionMnemonic::TYA,
            .addressMode = cpu::instructions::AddressingMode::Implied,
            .byteCount = 1,
            .cycleCount = 2, 
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            //.execute = &CPU::EOR,
        }; 
    // ASL (Arithmetic Shift Left)//
    // C <- [76543210] <- 0
    // N Z C I D V
    // + + + - - -
        map[0x0A] = {
            // Accumulator
            .opcode = 0x0A,
            .mnemonic = cpu::instructions::InstructionMnemonic::ASL,
            .addressMode = cpu::instructions::AddressingMode::Accumulator,
            .instructionModalities = cpu::instructions::InstructionModalities::ReadModifyWrite,
            .addrModalityMask = static_cast<cpu::instructions::AdressingModeModalityMask>(~static_cast<cpu::instructions::AdressingModeModalityMask>(cpu::instructions::AdressingModeModality::Imm)),
            .byteCount = 1,
            .cycleCount = 2,
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            //.execute = &CPU::ASL,
        };
        map[0x06] = {
            // Zeropage
            .opcode = 0x06,
            .mnemonic = cpu::instructions::InstructionMnemonic::ASL,
            .addressMode = cpu::instructions::AddressingMode::ZeroPage,
            .instructionModalities = cpu::instructions::InstructionModalities::ReadModifyWrite,
            .addrModalityMask = static_cast<cpu::instructions::AdressingModeModalityMask>(~static_cast<cpu::instructions::AdressingModeModalityMask>(cpu::instructions::AdressingModeModality::Imm)),

            .byteCount = 2,
            .cycleCount = 5,
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            //.execute = &CPU::ASL,
        };
        map[0x16] = {
            // Zeropage, X
            .opcode = 0x16,
            .mnemonic = cpu::instructions::InstructionMnemonic::ASL,
            .addressMode = cpu::instructions::AddressingMode::ZeroPageXIndexed,
            .instructionModalities = cpu::instructions::InstructionModalities::ReadModifyWrite,
            .addrModalityMask = static_cast<cpu::instructions::AdressingModeModalityMask>(~static_cast<cpu::instructions::AdressingModeModalityMask>(cpu::instructions::AdressingModeModality::Imm)),
            .byteCount = 2,
            .cycleCount = 6,
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            //.execute = &CPU::ASL,
        };
        map[0x0E] = {
            // Absolute
            .opcode = 0x0E,
            .mnemonic = cpu::instructions::InstructionMnemonic::ASL,
            .addressMode = cpu::instructions::AddressingMode::Absolute,
            .instructionModalities = cpu::instructions::InstructionModalities::ReadModifyWrite,
            .addrModalityMask = static_cast<cpu::instructions::AdressingModeModalityMask>(~static_cast<cpu::instructions::AdressingModeModalityMask>(cpu::instructions::AdressingModeModality::Imm)),
            .byteCount = 3,
            .cycleCount = 6,
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            //.execute = &CPU::ASL,
        };
        map[0x1E] = {
            // Absolute, X
            .opcode = 0x1E,
            .mnemonic = cpu::instructions::InstructionMnemonic::ASL,
            .addressMode = cpu::instructions::AddressingMode::AbsoluteXIndexed,
            .instructionModalities = cpu::instructions::InstructionModalities::ReadModifyWrite,
            .addrModalityMask = static_cast<cpu::instructions::AdressingModeModalityMask>(~static_cast<cpu::instructions::AdressingModeModalityMask>(cpu::instructions::AdressingModeModality::Imm)),
            .byteCount = 3,
            .cycleCount = 7,
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            //.execute = &CPU::ASL,
        };
    // CPY (Compare Memory with Y)//
    // Y - M
    // N Z C I D V
    // + + + - - -
        map[0xC0] = {
            // Immediate
            .opcode = 0xC0,
            .mnemonic = cpu::instructions::InstructionMnemonic::CPY,
            .addressMode = cpu::instructions::AddressingMode::Immediate,
            .byteCount = 2,
            .cycleCount = 2,
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            //.execute = &CPU::CPY,
        };
        map[0xC4] = {
            // Zeropage
            .opcode = 0xC4,
            .mnemonic = cpu::instructions::InstructionMnemonic::CPY,
            .addressMode = cpu::instructions::AddressingMode::ZeroPage,
            .byteCount = 2,
            .cycleCount = 3,
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            //.execute = &CPU::CPY,
        };
        map[0xCC] = {
            // Absolute
            .opcode = 0xCC,
            .mnemonic = cpu::instructions::InstructionMnemonic::CPY,
            .addressMode = cpu::instructions::AddressingMode::Absolute,
            .byteCount = 3,
            .cycleCount = 4,
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::C),
            //.execute = &CPU::CPY,
        };
    // TXA (Transfer Index X to Accumulator)//
    // X -> A
    // N Z C I D V
    // + + - - - -
        map[0x8A] = {
            // Implied
            .opcode = 0x8A,
            .mnemonic = cpu::instructions::InstructionMnemonic::TXA,
            .addressMode = cpu::instructions::AddressingMode::Implied,
            .byteCount = 1,
            .cycleCount = 2,
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            //.execute = &CPU::TXA,
        };
    // TSX (Transfer Stack Pointer to Index X)//
    // SP -> X
    // N Z C I D V
    // + + - - - -
        map[0xBA] = {
            // Implied
            .opcode = 0xBA,
            .mnemonic = cpu::instructions::InstructionMnemonic::TSX,
            .addressMode = cpu::instructions::AddressingMode::Implied,
            .byteCount = 1,
            .cycleCount = 2,
            .readFlags = 0,
            .writeFlags = static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::N) | static_cast<cpu::registers::FlagMask>(cpu::registers::StatusFlag::Z),
            //.execute = &CPU::TSX,
        };
        return map;
};
};