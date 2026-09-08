#include <Processor/CPURuntimeTypes.h>

namespace cpu::execution{

    struct ResolvedInfoInstruction { //metadata helper system: when running, the executor can add a bunch of data here relating to the cycle count for this instruction
        cpu::instructions::Instruction instruc; //all data about the instruction's routines
        bool isPrimedData = false; //is data stale? may be commented out later
        uint8_t resolvedCycleCount; //how many cycles does this specific instruciton take?
        uint8_t runningCyclesTally = 0; //not used by this class, but can be pinged by timer to keep track of how long this instruction has been running
        uint8_t resolvedByteCount; //how many bytes is the instruction, INCLUDING opcode?
        std::optional<uint8_t> znSource; // byte to derive N/Z from
        std::optional<bool> carry;
        std::optional<bool> overflow;
        std::optional<bool> zero;
        std::optional<bool> negative;
    public:
        void resetRunningPrimed() { runningCyclesTally = 0; }; // for timer, reset tally of running cycles
        bool incrementAndCheckTallyStale() { //increments tally, and then returns true if we've hit the number of cycle deeded
            runningCyclesTally++;
            return (runningCyclesTally >= resolvedCycleCount);
        };
    };

};