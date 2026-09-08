#include <cstdint>
#include <stdexcept>
#include <Misc/BCDTypeDef.h>


namespace helpers::decimal {
    class BCD8 // 8 bit (dual nibble) BCD type (0-99)
    {
    public:
        BCD8() : value_(0x00) {} // constructor, all BCD values defined as default to 00

        // Make binary value
        BCD8(uint8_t binary)
            : value_(encode(binary))
        {
        }

        // Construct from raw BCD
        static BCD8 fromBCD(uint8_t bcd)
        {
            if (!isValidBCD(bcd))
                throw std::invalid_argument("Invalid BCD");

            BCD8 v;
            v.value_ = bcd;
            return v;
        }

        // convert BCd to binary
        uint8_t toBinary() const
        {
            return decode(value_);
        }

        // return raw BCD as binary uint (for bit manip?)
        uint8_t raw() const
        {
            return value_;
        }

        // addition (modulo 100, wraps around)
        BCD8 operator+(BCD8 rhs) const
        {
            return fromRaw(addBCD(value_, rhs.value_));
        }

        BCD8& operator+=(BCD8 rhs)
        {
            value_ = addBCD(value_, rhs.value_);
            return *this;
        }

        // Subtraction (modulo 100)
        BCD8 operator-(BCD8 rhs) const
        {
            return fromRaw(subBCD(value_, rhs.value_));
        }

        BCD8& operator-=(BCD8 rhs)
        {
            value_ = subBCD(value_, rhs.value_);
            return *this;
        }

        bool operator==(BCD8 rhs) const { return value_ == rhs.value_; }
        bool operator!=(BCD8 rhs) const { return value_ != rhs.value_; }

    private:
        uint8_t value_;

        static bool isValidBCD(uint8_t b)
        {
            return ((b & 0x0F) < 10) && (((b >> 4) & 0x0F) < 10);
        }

        static uint8_t encode(uint8_t binary) //turn uint to BCD type
        {
            if (binary > 99) //  BCD 8 can only do 0-99
                throw std::out_of_range("BCD8 supports only 0-99");

            return ((binary / 10) << 4) | (binary % 10);
        }

        static uint8_t decode(uint8_t bcd)
        {
            return ((bcd >> 4) * 10) + (bcd & 0x0F);
        }

        static BCD8 fromRaw(uint8_t raw) //turns binary unit to BCD
        {
            BCD8 b;
            b.value_ = raw;
            return b;
        }

        // BCD addition (00-99), wraps modulo 100
        static uint8_t addBCD(uint8_t a, uint8_t b)
        {
            uint8_t lo = (a & 0x0F) + (b & 0x0F);
            uint8_t carry = 0;

            if (lo > 9)
            {
                lo += 6;
                carry = 1;
            }

            uint8_t hi = (a >> 4) + (b >> 4) + carry;

            if (hi > 9)
                hi += 6;

            return ((hi << 4) | (lo & 0x0F));
        }

        // BCD subtraction (00-99), wraps modulo 100
        static uint8_t subBCD(uint8_t a, uint8_t b)
        {
            int lo = (a & 0x0F) - (b & 0x0F);
            int borrow = 0;

            if (lo < 0)
            {
                lo -= 6;
                borrow = 1;
            }

            int hi = (a >> 4) - (b >> 4) - borrow;

            if (hi < 0)
                hi -= 6;

            return (uint8_t)(((hi & 0x0F) << 4) | (lo & 0x0F));
        }
    };
};