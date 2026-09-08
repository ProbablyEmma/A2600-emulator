//CPURuntimeTypes.h

//Holds def for data types meant for in-cpu-loop processing
#pragma once
#include <Processor/InstructionTypes.h>

namespace cpu::execution{
    struct OperandData {
        std::optional<cpu::instructions::AddressingMode> resolvedAddressingMode;
        std::optional<uint8_t> operandA;
        std::optional<uint8_t> operandB;
        std::optional<bool> insructionPageCrossed;
        std::optional<bool> operandPageCrossed;
        std::optional<uint16_t> operandByteAddress; //address (16) of byte
        std::optional<uint16_t> operandWordAddress; //address (16) of two bytes
        std::optional<bool> useInstructionMode; // Do we use a 'weird' behavior, eg Read-mofidy-write?
    };

    struct ResolvedInfoInstruction { //metadata helper system: when running, the executor can add a bunch of data here relating to the cycle count for this instruction
        cpu::instructions::Instruction instruc; //all data about the instruction's routines
        uint8_t resolvedCycleCount; //how many cycles does this specific instruciton take?
        uint8_t runningCyclesTally = 0; //not used by this class, but can be pinged by timer to keep track of how long this instruction has been running
        uint8_t resolvedByteCount; //how many bytes is the instruction, INCLUDING opcode?
        std::optional<uint8_t> znSource; // byte to derive N/Z from
        std::optional<bool> carry;
        std::optional<bool> overflow;
        std::optional<bool> zero;
        std::optional<bool> negative;
    public:
        void resetRunningPrimed(); // for timer, reset tally of running cycles
        bool incrementAndCheckTallyStale();
    };

    struct FlagResult { // short system for tracking flags
        //FIXME: this should be incoporated into ResolvedInfoInstruction if possible
        std::optional<uint8_t> znSource;  //which byte should be used for deriving the Z and N flags?
        std::optional<bool> carry;
        std::optional<bool> overflow;
        std::optional<bool> zero;
        std::optional<bool> negative;
    };

    enum ResultDestination { //represent the destination of the result here, for programmatic reasons
        A,
        X,
        Y,
        PC,
        SR,
        SP,
        Mem
    };
}