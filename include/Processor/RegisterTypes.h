// RegisterTypes.h
// Author: Emma BOULESTEIX
// Date: 08/09/26
// About: this contains all types, enums and basic classes used by the register file and RF-affiliate modules

#pragma once
#include <cstdint>

namespace cpu::registers {
    enum class StatusFlag : uint8_t {
        // This enum defines all flags the 6502/6507 SR uses, and the relevant 8bit bitmask 
        C = 1 << 0, // Carry flag, at bit 0 (LSB)
        Z = 1 << 1, // Zero flag
        I = 1 << 2, // Interrupt flAG
        D = 1 << 3, // Decimal flag (technically irrelevant for A2600)
        B = 1 << 4, // Break flag
        V = 1 << 6, // Overflow flag
        N = 1 << 7, // Negative flag, at bit 7 (MSB)
    };
    using FlagMask = uint8_t; // TYPEDEF: FlagMask aliases 8bit uint8 and represents a mask on the 6502 Status register
};

