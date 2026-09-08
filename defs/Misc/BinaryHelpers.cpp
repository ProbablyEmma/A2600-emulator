
#include <Processor/CPUMisc.h>
#include <Memory/MemoryRAM.h>
#include <Misc/BinaryHelpers.h>

namespace helpers::binary {
    class BinaryHelpers {
    public:
        uint8_t fetchByteFromWord16b(uint16_t word, memory::byteSignificance byte) {
            if (byte == memory::byteSignificance::HIGH) { return (static_cast<uint8_t>((word | 0xFF00) >> 8)); } // Get MSB
            else if (byte == memory::byteSignificance::LOW) { return (static_cast<uint8_t>(word | 0x00FF)); } // Get LSB
            else { return (static_cast<uint8_t>(word | 0x00FF)); } // Defaults to LSB
        };
        uint16_t concatenateWordFromTwoBytes(uint8_t highByte, uint8_t lowByte) { return (static_cast<uint16_t>(highByte) << 8) | (static_cast<uint16_t>(lowByte)); }; // If High is 0xHH and Low is 0xLL, we can do 0xHHLL = 0xHH00 | 0x00LL
    };
}