// MemoryRAM.h
#pragma once
#include <stdint.h>
#include <array>
#include <vector>

//custom type defs
#include <Processor/CPUMisc.h>



namespace memory::ram {
    class MemoryRAM {
    public:
        MemoryRAM(uint16_t memorySizeInBytes); //constructor
        uint8_t getPageIDFromAddress(uint16_t address) const;
        std::vector<uint8_t> fetchBytes(uint16_t address, uint8_t byteCount, cpu::CPUEndianness endianConvention = cpu::CPUEndianness::LITTLE);
        uint8_t readByte(uint16_t address) const;
        uint16_t readWord16b(uint16_t address);
        void writeByte(uint16_t address, uint8_t dataByte);
        void writeWord16b(uint16_t address, uint16_t dataWord);

    };
}