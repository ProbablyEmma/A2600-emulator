// BinaryHelpers.h
// various helper functions used for faster binary handling

#pragma once
#include <stdint.h>
#include <Processor/CPUMisc.h>


namespace helpers::binary {
    uint8_t fetchByteFromWord16b(uint16_t word, memory::byteSignificance byte);
    uint16_t concatenateWordFromTwoBytes(uint8_t highByte, uint8_t lowByte);
  
};