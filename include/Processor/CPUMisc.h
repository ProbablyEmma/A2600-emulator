// CPUMisc.h
// file contains various types describing design philosophy/quirks of the CPU
#pragma once
#include <stdint.h>

namespace cpu {
    enum ChipType {
        NMOS6502,
        CMOS6502,
    };
};

namespace cpu {
    enum CPUEndianness {
        BIG,
        LITTLE,
    };
};

namespace memory {
    enum byteSignificance {
        HIGH,
        LOW,
    };


};
//class CPU;