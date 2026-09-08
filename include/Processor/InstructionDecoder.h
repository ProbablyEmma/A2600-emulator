//InstructionTypes.h
#pragma once
#include <array>
#include <optional>
#include <Processor/CPURuntimeTypes.h>


//std::array<Instruction, 256> makeOpCodeTable(); 
//using OpCodeTableMap = std::array<Instruction, 256>;

namespace cpu::decoder {
    std::array<cpu::instructions::Instruction, 256> makeOpCodeTable();
    using OpCodeTableMap = std::array<cpu::instructions::Instruction, 256>;

    class InstructionDecoder {
    private:
        ResolvedInfoInstruction makeInstructionMetaData(
            cpu::instructions::Instruction instr, uint8_t resolvedCycleCount, uint8_t resultByte,
            cpu::execution::FlagResult flags = {}
        );
    };
};



