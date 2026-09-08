
/*
* AUTHOR: Emma BOULESTEIX
* DATE: Aug 2026
* PROJECT: A2600 CPU emulator
* FILE: Handles memory addressing 
*/
#include <stdint.h>
#include <array>
#include <vector>
#include <format>
#include <stdexcept>

#include <Processor/CPUMisc.h>
#include <Memory/MemoryRAM.h>
#include <Misc/BinaryHelpers.h>


namespace memory::ram {
    class MemoryRAM {
        std::vector<uint8_t> ramBuffer;
        uint32_t memorySizeBytes;
    public:
        MemoryRAM(uint32_t memorySizeInBytes) {
            std::vector<uint8_t> ramBuffer(sizeof(uint8_t) * memorySizeInBytes);
            memorySizeBytes = memorySizeInBytes;
        }; //declare buffer for RAM

        uint8_t getPageIDFromAddress(uint16_t address) {
            uint8_t pageID = helpers::binary::fetchByteFromWord16b(address, memory::byteSignificance::HIGH);
            return pageID;
        }; //MS byte of address is page ID};

        std::vector<uint8_t>  fetchBytes(uint16_t address, uint8_t byteCount, cpu::CPUEndianness endianConvention = cpu::CPUEndianness::LITTLE) const { //fetch the N bytes from the provided memory address, ascending, returning them in order based on convention
            // NOTE/FIXME: endianness does nothing here, which is because 6502 is LE, but maybe extend this later
            std::vector<uint8_t> buffer(byteCount); // store entries here
            for (int i = 0; i < byteCount; i++) {
                buffer[byteCount - i] = ramBuffer[address + i]; //iterate through RAM buffer and place in buffer here. This inversion means that opcode is placed first (index 0) with addresses and such appearing in order
            };
            return buffer;
        };

        uint8_t readByte(uint16_t address) const {
            return static_cast<uint8_t>(fetchBytes(address, 1)[0]);
        };
        uint16_t readWord16b(uint16_t address) {
            std::vector<uint8_t> word = fetchBytes(address, 2);
            uint8_t highByte = word[0]; // BE convention: MSB/High is lower in memory address terms
            uint8_t lowByte = word[1]; // BE convention: LOW byte at higher address
            return helpers::binary::concatenateWordFromTwoBytes(highByte, lowByte);
        };

        void writeByte(uint16_t address, uint8_t dataByte) {
            ramBuffer[address] = dataByte;
        };

        void writeWord16b(uint16_t address, uint16_t dataWord) {
            uint8_t highByte = helpers::binary::fetchByteFromWord16b(dataWord, memory::byteSignificance::HIGH);
            uint8_t lowByte = helpers::binary::fetchByteFromWord16b(dataWord, memory::byteSignificance::LOW);
            //now write
            ramBuffer[address + 1] = highByte; // LE convention: MSB in higher address
            ramBuffer[address] = lowByte;
        };

    };
};