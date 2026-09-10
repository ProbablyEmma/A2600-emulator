#include <Processor/CPURuntimeTypes.h>

namespace cpu::execution{

    void ResolvedInfoInstruction::resetRunningPrimed() { runningCyclesTally = 0; }; // for timer, reset tally of running cycles
    bool ResolvedInfoInstruction::incrementAndCheckTallyStale() { //increments tally, and then returns true if we've hit the number of cycle deeded
        runningCyclesTally++;
        return (runningCyclesTally >= resolvedCycleCount);
    };
    

};