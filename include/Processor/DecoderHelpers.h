// DecoderHelpers.h
#pragma once
#include <cstdint>
#include <vector>
#include <optional>
#include <stdint.h>

#include <Processor/CPUMisc.h>
#include <Processor/RegisterFile.h>
#include <Processor/InstructionTypes.h>
#include <Processor/CPURuntimeTypes.h>
#include <Processor/RegisterFile.h>
#include <Processor/RegisterTypes.h>
#include <Memory/MemoryRAM.h>




namespace helpers::decoder{
    bool checkPageCrossOffset(uint16_t baseAddress, uint8_t addressOffset);
    uint8_t computeTotalRuntimePageCross(uint16_t baseAddress, uint8_t addressOffset, uint8_t baseCycleCost, uint8_t pageCrossExtraCycles);
    bool checkIfDataZero(uint8_t data);
    bool checkIfDataNegative(uint8_t data);
    bool checkIfOperationCarry(uint8_t operandA, uint8_t operandB, bool carryBit = 0);
    bool checkIfOperationOverflow(uint8_t operandA, uint8_t operandB, bool carryBit = 0);
    cpu::execution::OperandData fetchOperands(const cpu::instructions::Instruction& instr, uint16_t baseAddress, memory::ram::MemoryRAM& ram, cpu::registers::RegisterFile& RF, cpu::ChipType processorFamily = cpu::ChipType::NMOS6502);
    void commitData(uint8_t result, cpu::execution::OperandData resultMeta, cpu::execution::ResultDestination resDestination, memory::ram::MemoryRAM& ram, cpu::registers::RegisterFile& RF);
    void commitData(uint16_t result, cpu::execution::OperandData resultMeta, cpu::execution::ResultDestination resDestination, memory::ram::MemoryRAM& ram, cpu::registers::RegisterFile& RF);
};