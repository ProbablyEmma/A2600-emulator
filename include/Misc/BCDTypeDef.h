// BCDTypeDefs.h
// Definitions for the BCD type def used by the CPU

#pragma once
#include <cstdint>

namespace helpers::decimal {
    class BCD8
    {
    public:
        BCD8();
        explicit BCD8(uint8_t binary);

        static BCD8 fromBCD(uint8_t bcd);

        uint8_t toBinary() const;
        uint8_t raw() const;

        operator uint8_t() const;

        BCD8 operator+(BCD8 rhs) const;
        BCD8 operator-(BCD8 rhs) const;
        BCD8& operator+=(BCD8 rhs);
        BCD8& operator-=(BCD8 rhs);

    private:
        uint8_t value_;
        static bool isValidBCD(uint8_t bcd);
        static uint8_t encode(uint8_t binary);
        static uint8_t decode(uint8_t bcd);

        static uint8_t addBCD(uint8_t a, uint8_t b);
        static uint8_t subBCD(uint8_t a, uint8_t b);
    };
}