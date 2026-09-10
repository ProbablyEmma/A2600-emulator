/*
* AUTHOR: Emma BOULESTEIX
* DATE: Aug 2026
* PROJECT: A2600 CPU emulator
* FILE: Contains the definitions for each instruction though not the CPU macros (eg CPU::LDA)
*/



#include <stdint.h>
#include <optional>
#include <stdexcept>

#include <Processor/CPUMisc.h>
#include <Processor/CPURuntimeTypes.h>
#include <Memory/MemoryRAM.h>
#include <Processor/RegisterFile.h>
#include <Processor/InstructionTypes.h>
#include <Processor/InstructionDecoder.h>
#include <Processor/DecoderHelpers.h>
#include <Misc/BCDTypeDef.h>
#include <Misc/BinaryHelpers.h>

using namespace cpu::execution;
using namespace helpers::decoder;
using namespace helpers::binary;
using namespace helpers::decimal;



#define ZEROPAGE_OFFSET 0x0000 //zeropage addresses are from 0x0000-0x00FF


namespace cpu::decoder{
    // Base Class: Decoder and related functions
    class InstructionDecoder {
    // References to processor register file, opcode mapper and CPU type here
    cpu::decoder::OpCodeTableMap& OpCMap;
    cpu::registers::RegisterFile& RF;
    cpu::ChipType CpuTypeFamily;
    memory::ram::MemoryRAM& RAM;


public:
    // constructor where references to ressources are passed 
        InstructionDecoder(cpu::registers::RegisterFile& CPURF, cpu::decoder::OpCodeTableMap& CPUOpCMap, memory::ram::MemoryRAM& systemRAM, cpu::ChipType CPUType = cpu::ChipType::NMOS6502) : RF(CPURF), OpCMap(CPUOpCMap), RAM(systemRAM), CpuTypeFamily(CPUType) {};
        //From the emulator's perspective, these executors run atomically, so a 6 cycle instruction runs all at once THEN stalls for 
        cpu::execution::ResolvedInfoInstruction instructionMetadata; //GOAL: the executors below just do flag ops and basic math and state changes, with timing done by the overall system timer. 


        // Setting this as PROTECTED because this will be inherinted by Processor class. These are individual instruction handlers (eg LDA, LDX...)
            
        // =================================== //
        // ------ Arithmetic operations ------ //
        // =================================== //

        void ADC(cpu::instructions::Instruction instr) {
                instructionMetadata.resolvedByteCount = instr.byteCount;
                cpu::instructions::AddressingMode instructionMode = instr.addressMode;
                cpu::execution::OperandData data = helpers::decoder::fetchOperands(instr, RF.PC.readPC(), RAM, RF, CpuTypeFamily);
                uint8_t result, newFlags, cycleCost;
                cpu::execution::FlagResult resFlags;
                //bool isCarry, isOverflow, isZero, isNegative;
                bool isDecimal = RF.SR.readFlag(cpu::registers::StatusFlag::D);
                if (data.operandA.has_value() && (!isDecimal)) {
                    result = RF.A.read() + data.operandA.value() + RF.SR.readFlag(cpu::registers::StatusFlag::C);
                    resFlags.carry = helpers::decoder::checkIfOperationCarry(RF.A.read(), data.operandA.value(), RF.SR.readFlag(cpu::registers::StatusFlag::C));
                    resFlags.overflow = helpers::decoder::checkIfOperationOverflow(RF.A.read(), data.operandA.value(), RF.SR.readFlag(cpu::registers::StatusFlag::C));
                    resFlags.zero = helpers::decoder::checkIfDataZero(result);
                    resFlags.negative = helpers::decoder::checkIfDataNegative(result);
                }
                else if (data.operandA.has_value() && (isDecimal))
                {
                    uint8_t binarySum = RF.A.read() + data.operandA.value() + RF.SR.readFlag(cpu::registers::StatusFlag::C);
                    helpers::decimal::BCD8 Acc = helpers::decimal::BCD8(RF.A.read());
                    helpers::decimal::BCD8 Op = helpers::decimal::BCD8(data.operandA.value());
                    helpers::decimal::BCD8 Carry = helpers::decimal::BCD8(static_cast<uint8_t>(RF.SR.readFlag(cpu::registers::StatusFlag::C)));
                    Acc = Acc.operator+(Op);
                    Acc = Acc.operator+(Carry);
                    result = Acc.toBinary();
                    resFlags.carry = (Acc.toBinary() > 99);
                    resFlags.overflow = helpers::decoder::checkIfOperationOverflow(RF.A.read(), data.operandA.value(), RF.SR.readFlag(cpu::registers::StatusFlag::C));
                    if (CpuTypeFamily == cpu::ChipType::NMOS6502) {
                        resFlags.zero = helpers::decoder::checkIfDataZero(binarySum);
                        resFlags.negative = helpers::decoder::checkIfDataNegative(binarySum);
                    }
                    else if (CpuTypeFamily == cpu::ChipType::CMOS6502)
                    {
                        resFlags.zero = helpers::decoder::checkIfDataZero(result);
                        resFlags.negative = helpers::decoder::checkIfDataNegative(result);
                        cycleCost = instr.cycleCount + 1;
                    }

                }

                else { throw std::runtime_error("ERROR: (ADC Decode) invalid payload for operands"); }
                if (data.operandPageCrossed.has_value()) {
                    cycleCost = instr.cycleCount + static_cast<uint8_t>(data.operandPageCrossed.value());
                }
                else { cycleCost = instr.cycleCount; }
                instructionMetadata = makeInstructionMetaData(instr, cycleCost, result, resFlags);
                RF.SR.commitFlags(instr, instructionMetadata);
                helpers::decoder::commitData(result, data, cpu::execution::ResultDestination::A, RAM, RF);

            };

        void SBC(cpu::instructions::Instruction instr) {
                instructionMetadata.resolvedByteCount = instr.byteCount;
                cpu::instructions::AddressingMode instructionMode = instr.addressMode;
                cpu::execution::OperandData data = helpers::decoder::fetchOperands(instr, RF.PC.readPC(), RAM, RF, CpuTypeFamily);
                uint8_t result, newFlags, cycleCost;
                //package flags up here when done
                cpu::execution::FlagResult resFlags;
                //bool isCarry, isOverflow, isZero, isNegative;
                bool isDecimal = RF.SR.readFlag(cpu::registers::StatusFlag::D);
                if (data.operandA.has_value() && (!isDecimal)) {
                    uint8_t invertedOperand = ~data.operandA.value();
                    result = RF.A.read() + invertedOperand + RF.SR.readFlag(cpu::registers::StatusFlag::C);
                    resFlags.carry = helpers::decoder::checkIfOperationCarry(RF.A.read(), invertedOperand, RF.SR.readFlag(cpu::registers::StatusFlag::C));
                    resFlags.overflow = helpers::decoder::checkIfOperationOverflow(RF.A.read(), invertedOperand, RF.SR.readFlag(cpu::registers::StatusFlag::C));
                    resFlags.zero = helpers::decoder::checkIfDataZero(result);
                    resFlags.negative = helpers::decoder::checkIfDataNegative(result);
                }
                else if (data.operandA.has_value() && (isDecimal))
                {
                    uint8_t invertedOperand = ~data.operandA.value();
                    uint8_t binarySum = RF.A.read() + invertedOperand + RF.SR.readFlag(cpu::registers::StatusFlag::C);
                    helpers::decimal::BCD8 Acc = helpers::decimal::BCD8(RF.A.read());
                    helpers::decimal::BCD8 Op = helpers::decimal::BCD8(data.operandA.value());
                    helpers::decimal::BCD8 Carry = helpers::decimal::BCD8(static_cast<uint8_t>(RF.SR.readFlag(cpu::registers::StatusFlag::C)));
                    Acc = Acc.operator-(Op);
                    Acc = Acc.operator-(helpers::decimal::BCD8(static_cast<uint8_t>(1 - RF.SR.readFlag(cpu::registers::StatusFlag::C))));
                    result = Acc.toBinary();
                    resFlags.carry = helpers::decoder::checkIfOperationCarry(RF.A.read(), invertedOperand, RF.SR.readFlag(cpu::registers::StatusFlag::C));
                    resFlags.overflow = helpers::decoder::checkIfOperationOverflow(RF.A.read(), invertedOperand, RF.SR.readFlag(cpu::registers::StatusFlag::C));
                    if (CpuTypeFamily == cpu::ChipType::NMOS6502) {
                        resFlags.zero = helpers::decoder::checkIfDataZero(binarySum);
                        resFlags.negative = helpers::decoder::checkIfDataNegative(binarySum);
                    }
                    else if (CpuTypeFamily == cpu::ChipType::CMOS6502)
                    {
                        resFlags.zero = helpers::decoder::checkIfDataZero(result);
                        resFlags.negative = helpers::decoder::checkIfDataNegative(result);
                    }

                }

                else { throw std::runtime_error("ERROR: (SBC Decode) invalid payload for operands"); }
                cycleCost = instr.cycleCount;
                if (data.operandPageCrossed.has_value()) {
                    cycleCost += static_cast<uint8_t>(data.operandPageCrossed.value());
                }
                if (isDecimal && CpuTypeFamily == cpu::ChipType::CMOS6502) {
                    cycleCost += 1;
                }

                instructionMetadata = makeInstructionMetaData(instr, cycleCost, result, resFlags);
                RF.SR.commitFlags(instr, instructionMetadata);
                helpers::decoder::commitData(result, data, cpu::execution::ResultDestination::A, RAM, RF);
            };

        // =================================== //
        // -------- Logical operations ------- //
        // =================================== //
           
        void AND(cpu::instructions::Instruction instr) {
                // AND Memory with Accumulator, affects N and Z //
                // Get encoded base instruction metadata
                instructionMetadata.resolvedByteCount = instr.byteCount;
                cpu::instructions::AddressingMode instructionMode = instr.addressMode;
                // fetch data using base metadata
                cpu::execution::OperandData data = helpers::decoder::fetchOperands(instr, RF.PC.readPC(), RAM, RF, CpuTypeFamily);
                //package flags up here when done
                cpu::execution::FlagResult resFlags;
                // init temp variables for result
                uint8_t result, newFlags, cycleCost;

                if (data.operandA.has_value()) { //should always be valid, technically
                    result = static_cast<uint8_t>(RF.A.read() & data.operandA.value());
                    resFlags.zero = helpers::decoder::checkIfDataZero(result);
                    resFlags.negative = helpers::decoder::checkIfDataNegative(result);
                }
                else { throw std::runtime_error("ERROR: (AND Decode) invalid payload for operands"); }
                cycleCost = instr.cycleCount;
                if (data.operandPageCrossed.has_value()) {
                    cycleCost += static_cast<uint8_t>(data.operandPageCrossed.value());
                }
                instructionMetadata = makeInstructionMetaData(instr, cycleCost, result, resFlags);
                RF.SR.commitFlags(instr, instructionMetadata);
                helpers::decoder::commitData(result, data, cpu::execution::ResultDestination::A, RAM, RF);
            };

        // =================================== //
        // ----- Shift/rotate operations ----- //
        // =================================== //

        void ASL(cpu::instructions::Instruction instr) {
                // Arithmetic shift one bit left, affects N, Z, C
                // NOTE this is a R-m-W type instruction for all non accumulator modes
                // 
                // Get packed instruction data
                instructionMetadata.resolvedByteCount = instr.byteCount;
                cpu::instructions::AddressingMode instructionMode = instr.addressMode;
                //
                // fetch data using base metadata
                cpu::execution::OperandData data = helpers::decoder::fetchOperands(instr, RF.PC.readPC(), RAM, RF, CpuTypeFamily);
                //
                //init and package here, init
                cpu::execution::FlagResult resFlags;
                uint16_t resultIntermediate;
                uint8_t result, cycleCost;
                //
                //Now run main computations on data
                if (data.operandA.has_value()) {
                    //MSB of data is carry
                    resFlags.carry = static_cast<bool>(data.operandA.value() & 0x80); // if MSB is not 1 already, this operartion will return 0
                    resultIntermediate = static_cast<uint16_t>(data.operandA.value());
                    resultIntermediate = resultIntermediate << 1; //shift left by one place
                    resultIntermediate = (resultIntermediate & 0x00FF); // remove anything not in 8b
                    result = static_cast<uint8_t>(resultIntermediate);
                    resFlags.zero = helpers::decoder::checkIfDataZero(result);
                    resFlags.negative = helpers::decoder::checkIfDataNegative(result);
                }
                else { throw std::runtime_error("ERROR: (ASL Decode) invalid payload for operands"); }
                // NOTE: this is a read-modify-write instruction, meaning that the destination might either be A (Accumulator) or the address of the original operand
                // CHECK 1: did we assign these values for the operation mode? (sanity check)
                if (instr.instructionModalities == cpu::instructions::InstructionModalities::ReadModifyWrite && data.useInstructionMode.has_value()) {
                    if (data.useInstructionMode == true) { // CHECK 2 : are we using the specified RMW mode here?
                        // YES: we write to RAM
                        if (data.operandByteAddress.has_value()) { helpers::decoder::commitData(result, data, cpu::execution::ResultDestination::Mem, RAM, RF); }; //commit to memory
                    }
                    if (data.useInstructionMode == false) { // CHECK 2 : are we using the specified RMW mode here?
                        // NO: we write to RF
                        helpers::decoder::commitData(result, data, cpu::execution::ResultDestination::A, RAM, RF); //commit to RF.A
                    }
                }
                else { helpers::decoder::commitData(result, data, cpu::execution::ResultDestination::A, RAM, RF); }; //commit to RF.A
                cycleCost = instr.cycleCount;
                if (data.operandPageCrossed.has_value()) { cycleCost += static_cast<uint8_t>(data.operandPageCrossed.value()); }
                instructionMetadata = makeInstructionMetaData(instr, cycleCost, result, resFlags);
                RF.SR.commitFlags(instr, instructionMetadata);
            };
        
        // =================================== //
        // -------- Branch operations -------- //
        // =================================== //            
        
        void BCC(cpu::instructions::Instruction instr) {
                // Branch on Carry clear, affects no flags
                // 
                // Get packed instruction data
                instructionMetadata.resolvedByteCount = instr.byteCount;
                cpu::instructions::AddressingMode instructionMode = instr.addressMode;
                //
                // fetch data using base metadata
                cpu::execution::OperandData data = helpers::decoder::fetchOperands(instr, RF.PC.readPC(), RAM, RF, CpuTypeFamily);
                //
                // Init data
                bool isBranching, pageCrossedWhileBranching;
                uint8_t cycleCost;
                uint16_t resolvedAddress = RF.PC.readPC(); // by default just use the base PC
                // 
                //Now run main computations on data
                isBranching = !(RF.SR.readFlag(cpu::registers::StatusFlag::C)); // Branch if C == 0
                //FIXME: CHECK if the page crossing behavior is wrt first byte PC or not
                if (isBranching) {
                    if (!((data.operandA.has_value()) && (data.operandB.has_value()))) {throw std::runtime_error("ERROR: (BCC Decode) invalid payload for operands");}
                    resolvedAddress = helpers::binary::concatenateWordFromTwoBytes(data.operandB.value(), data.operandA.value());
                }
                helpers::decoder::commitData(resolvedAddress, data, cpu::execution::ResultDestination::PC, RAM, RF);
                // cycle cost calculation
                cycleCost = instr.cycleCount + static_cast<uint8_t>(isBranching);
                if (data.operandPageCrossed.has_value()) { cycleCost += static_cast<uint8_t>(data.operandPageCrossed.value()); }
            };
                   
        void BCS(cpu::instructions::Instruction instr) {
                // Branch on Carry Set, affects no flags
                // 
                // Get packed instruction data
                instructionMetadata.resolvedByteCount = instr.byteCount;
                cpu::instructions::AddressingMode instructionMode = instr.addressMode;
                //
                // fetch data using base metadata
                cpu::execution::OperandData data = helpers::decoder::fetchOperands(instr, RF.PC.readPC(), RAM, RF, CpuTypeFamily);
                //
                // Init data
                bool isBranching, pageCrossedWhileBranching;
                uint8_t cycleCost;
                uint16_t resolvedAddress = RF.PC.readPC(); // by default just use the base PC
                // 
                //Now run main computations on data
                isBranching = RF.SR.readFlag(cpu::registers::StatusFlag::C); // Branch if C == 1
                //FIXME: CHECK if the page crossing behavior is wrt first byte PC or not
                if (isBranching) {
                    if (!((data.operandA.has_value()) && (data.operandB.has_value()))) { throw std::runtime_error("ERROR: (BCS Decode) invalid payload for operands"); }
                    resolvedAddress = helpers::binary::concatenateWordFromTwoBytes(data.operandB.value(), data.operandA.value());
                }
                helpers::decoder::commitData(resolvedAddress, data, cpu::execution::ResultDestination::PC, RAM, RF);
                // cycle cost calculation
                cycleCost = instr.cycleCount + static_cast<uint8_t>(isBranching);
                if (data.operandPageCrossed.has_value()) { cycleCost += static_cast<uint8_t>(data.operandPageCrossed.value()); }
            };
                    
        void BEQ(cpu::instructions::Instruction instr) {
                // Branch on Result Zero, affects no flags
                // 
                // Get packed instruction data
                instructionMetadata.resolvedByteCount = instr.byteCount;
                cpu::instructions::AddressingMode instructionMode = instr.addressMode;
                //
                // fetch data using base metadata
                cpu::execution::OperandData data = helpers::decoder::fetchOperands(instr, RF.PC.readPC(), RAM, RF, CpuTypeFamily);
                //
                // Init data
                bool isBranching, pageCrossedWhileBranching;
                uint8_t cycleCost;
                uint16_t resolvedAddress = RF.PC.readPC(); // by default just use the base PC
                // 
                //Now run main computations on data
                isBranching = (RF.SR.readFlag(cpu::registers::StatusFlag::Z)); // Branch if Z=1
                //FIXME: CHECK if the page crossing behavior is wrt first byte PC or not
                if (isBranching) {
                    if (!((data.operandA.has_value()) && (data.operandB.has_value()))) { throw std::runtime_error("ERROR: (BEQ Decode) invalid payload for operands"); }
                    resolvedAddress = helpers::binary::concatenateWordFromTwoBytes(data.operandB.value(), data.operandA.value());
                }
                helpers::decoder::commitData(resolvedAddress, data, cpu::execution::ResultDestination::PC, RAM, RF);
                // cycle cost calculation
                cycleCost = instr.cycleCount + static_cast<uint8_t>(isBranching);
                if (data.operandPageCrossed.has_value()) { cycleCost += static_cast<uint8_t>(data.operandPageCrossed.value()); }
            };
                    
        void BMI(cpu::instructions::Instruction instr) {
                // Branch on Result Minus, affects no flags
                // 
                // Get packed instruction data
                instructionMetadata.resolvedByteCount = instr.byteCount;
                cpu::instructions::AddressingMode instructionMode = instr.addressMode;
                //
                // fetch data using base metadata
                cpu::execution::OperandData data = helpers::decoder::fetchOperands(instr, RF.PC.readPC(), RAM, RF, CpuTypeFamily);
                //
                // Init data
                bool isBranching, pageCrossedWhileBranching;
                uint8_t cycleCost;
                uint16_t resolvedAddress = RF.PC.readPC(); // by default just use the base PC
                // 
                //Now run main computations on data
                isBranching = (RF.SR.readFlag(cpu::registers::StatusFlag::N)); // Branch if N=1
                //FIXME: CHECK if the page crossing behavior is wrt first byte PC or not
                if (isBranching) {
                    if (!((data.operandA.has_value()) && (data.operandB.has_value()))) { throw std::runtime_error("ERROR: (BMI Decode) invalid payload for operands"); }
                    resolvedAddress = helpers::binary::concatenateWordFromTwoBytes(data.operandB.value(), data.operandA.value());
                }
                helpers::decoder::commitData(resolvedAddress, data, cpu::execution::ResultDestination::PC, RAM, RF);
                // cycle cost calculation
                cycleCost = instr.cycleCount + static_cast<uint8_t>(isBranching);
                if (data.operandPageCrossed.has_value()) { cycleCost += static_cast<uint8_t>(data.operandPageCrossed.value()); }
            };
                    
        void BNE(cpu::instructions::Instruction instr) {
                // Branch on Result not Zero, affects no flags
                // 
                // Get packed instruction data
                instructionMetadata.resolvedByteCount = instr.byteCount;
                cpu::instructions::AddressingMode instructionMode = instr.addressMode;
                //
                // fetch data using base metadata
                cpu::execution::OperandData data = helpers::decoder::fetchOperands(instr, RF.PC.readPC(), RAM, RF, CpuTypeFamily);
                //
                // Init data
                bool isBranching, pageCrossedWhileBranching;
                uint8_t cycleCost;
                uint16_t resolvedAddress = RF.PC.readPC(); // by default just use the base PC
                // 
                //Now run main computations on data
                isBranching = !(RF.SR.readFlag(cpu::registers::StatusFlag::Z)); // Branch if Z=0
                //FIXME: CHECK if the page crossing behavior is wrt first byte PC or not
                if (isBranching) {
                    if (!((data.operandA.has_value()) && (data.operandB.has_value()))) { throw std::runtime_error("ERROR: (BNR Decode) invalid payload for operands"); }
                    resolvedAddress = helpers::binary::concatenateWordFromTwoBytes(data.operandB.value(), data.operandA.value());
                }
                helpers::decoder::commitData(resolvedAddress, data, cpu::execution::ResultDestination::PC, RAM, RF);
                // cycle cost calculation
                cycleCost = instr.cycleCount + static_cast<uint8_t>(isBranching);
                if (data.operandPageCrossed.has_value()) { cycleCost += static_cast<uint8_t>(data.operandPageCrossed.value()); }
            };
                    
        void BPL(cpu::instructions::Instruction instr) {
                // Branch on Result Plus, affects no flags
                // 
                // Get packed instruction data
                instructionMetadata.resolvedByteCount = instr.byteCount;
                cpu::instructions::AddressingMode instructionMode = instr.addressMode;
                //
                // fetch data using base metadata
                cpu::execution::OperandData data = helpers::decoder::fetchOperands(instr, RF.PC.readPC(), RAM, RF, CpuTypeFamily);
                //
                // Init data
                bool isBranching, pageCrossedWhileBranching;
                uint8_t cycleCost;
                uint16_t resolvedAddress = RF.PC.readPC(); // by default just use the base PC
                // 
                //Now run main computations on data
                isBranching = !(RF.SR.readFlag(cpu::registers::StatusFlag::N)); // Branch if N = 0
                //FIXME: CHECK if the page crossing behavior is wrt first byte PC or not
                if (isBranching) {
                    if (!((data.operandA.has_value()) && (data.operandB.has_value()))) { throw std::runtime_error("ERROR: (BNR Decode) invalid payload for operands"); }
                    resolvedAddress = helpers::binary::concatenateWordFromTwoBytes(data.operandB.value(), data.operandA.value());
                }
                helpers::decoder::commitData(resolvedAddress, data, cpu::execution::ResultDestination::PC, RAM, RF);
                // cycle cost calculation
                cycleCost = instr.cycleCount + static_cast<uint8_t>(isBranching);
                if (data.operandPageCrossed.has_value()) { cycleCost += static_cast<uint8_t>(data.operandPageCrossed.value()); }
            };
                    
        void BVC(cpu::instructions::Instruction instr) {
                // Branch on overflow clear, affects no flags
                // 
                // Get packed instruction data
                instructionMetadata.resolvedByteCount = instr.byteCount;
                cpu::instructions::AddressingMode instructionMode = instr.addressMode;
                //
                // fetch data using base metadata
                cpu::execution::OperandData data = helpers::decoder::fetchOperands(instr, RF.PC.readPC(), RAM, RF, CpuTypeFamily);
                //
                // Init data
                bool isBranching, pageCrossedWhileBranching;
                uint8_t cycleCost;
                uint16_t resolvedAddress = RF.PC.readPC(); // by default just use the base PC
                // 
                //Now run main computations on data
                isBranching = !(RF.SR.readFlag(cpu::registers::StatusFlag::V)); // Branch if V = 0
                //FIXME: CHECK if the page crossing behavior is wrt first byte PC or not
                if (isBranching) {
                    if (!((data.operandA.has_value()) && (data.operandB.has_value()))) { throw std::runtime_error("ERROR: (BNR Decode) invalid payload for operands"); }
                    resolvedAddress = helpers::binary::concatenateWordFromTwoBytes(data.operandB.value(), data.operandA.value());
                }
                helpers::decoder::commitData(resolvedAddress, data, cpu::execution::ResultDestination::PC, RAM, RF);
                // cycle cost calculation
                cycleCost = instr.cycleCount + static_cast<uint8_t>(isBranching);
                if (data.operandPageCrossed.has_value()) { cycleCost += static_cast<uint8_t>(data.operandPageCrossed.value()); }
            };
                    
        void BVS(cpu::instructions::Instruction instr) {
                // Branch on overflow set, affects no flags
                // 
                // Get packed instruction data
                instructionMetadata.resolvedByteCount = instr.byteCount;
                cpu::instructions::AddressingMode instructionMode = instr.addressMode;
                //
                // fetch data using base metadata
                cpu::execution::OperandData data = helpers::decoder::fetchOperands(instr, RF.PC.readPC(), RAM, RF, CpuTypeFamily);
                //
                // Init data
                bool isBranching, pageCrossedWhileBranching;
                uint8_t cycleCost;
                uint16_t resolvedAddress = RF.PC.readPC(); // by default just use the base PC
                // 
                //Now run main computations on data
                isBranching = (RF.SR.readFlag(cpu::registers::StatusFlag::V)); // Branch if V = 1
                //FIXME: CHECK if the page crossing behavior is wrt first byte PC or not
                if (isBranching) {
                    if (!((data.operandA.has_value()) && (data.operandB.has_value()))) { throw std::runtime_error("ERROR: (BNR Decode) invalid payload for operands"); }
                    resolvedAddress = helpers::binary::concatenateWordFromTwoBytes(data.operandB.value(), data.operandA.value());
                }
                helpers::decoder::commitData(resolvedAddress, data, cpu::execution::ResultDestination::PC, RAM, RF);
                // cycle cost calculation
                cycleCost = instr.cycleCount + static_cast<uint8_t>(isBranching);
                if (data.operandPageCrossed.has_value()) { cycleCost += static_cast<uint8_t>(data.operandPageCrossed.value()); }
            };

        // =================================== //
        // --------- Flag carry/set ---------- //
        // =================================== //  
        
        void CLC(cpu::instructions::Instruction instr) {
            // Clear carry flag, sets C=0
            // 
            // Get packed instruction data
            instructionMetadata.resolvedByteCount = instr.byteCount;
            cpu::instructions::AddressingMode instructionMode = instr.addressMode;
            // init
            uint8_t cycleCost;
            cpu::execution::FlagResult resFlags;
            //
            // fetch data using base metadata
            cpu::execution::OperandData data = helpers::decoder::fetchOperands(instr, RF.PC.readPC(), RAM, RF, CpuTypeFamily);
            resFlags.carry = false;// set carry flag

            // compute cycle cost (fixed for CLC)
            cycleCost = instr.cycleCount; 
            //commit state
            instructionMetadata = makeInstructionMetaData(instr, cycleCost, 0, resFlags);
            RF.SR.commitFlags(instr, instructionMetadata);
        };

        void CLD(cpu::instructions::Instruction instr) {
            // Clear decimal mode flag, sets D=0
            // 
            // Get packed instruction data
            instructionMetadata.resolvedByteCount = instr.byteCount;
            cpu::instructions::AddressingMode instructionMode = instr.addressMode;
            // init
            uint8_t cycleCost;
            cpu::execution::FlagResult resFlags;
            //
            // fetch data using base metadata
            cpu::execution::OperandData data = helpers::decoder::fetchOperands(instr, RF.PC.readPC(), RAM, RF, CpuTypeFamily);
            resFlags.decimal = false;// set decimal flag

            // compute cycle cost (fixed for CLD)
            cycleCost = instr.cycleCount;
            //commit state
            instructionMetadata = makeInstructionMetaData(instr, cycleCost, 0, resFlags);
            RF.SR.commitFlags(instr, instructionMetadata);
        };

        void CLI(cpu::instructions::Instruction instr) {
            // Clear interrupt disable bit flag, sets I=0
            // 
            // Get packed instruction data
            instructionMetadata.resolvedByteCount = instr.byteCount;
            cpu::instructions::AddressingMode instructionMode = instr.addressMode;
            // init
            uint8_t cycleCost;
            cpu::execution::FlagResult resFlags;
            //
            // fetch data using base metadata
            cpu::execution::OperandData data = helpers::decoder::fetchOperands(instr, RF.PC.readPC(), RAM, RF, CpuTypeFamily);
            resFlags.interrupt = false;// set decimal flag

            // compute cycle cost (fixed for CLI)
            cycleCost = instr.cycleCount;
            //commit state
            instructionMetadata = makeInstructionMetaData(instr, cycleCost, 0, resFlags);
            RF.SR.commitFlags(instr, instructionMetadata);
        };

        void CLV(cpu::instructions::Instruction instr) {
            // Clear overflow flag, sets V=0
            // 
            // Get packed instruction data
            instructionMetadata.resolvedByteCount = instr.byteCount;
            cpu::instructions::AddressingMode instructionMode = instr.addressMode;
            // init
            uint8_t cycleCost;
            cpu::execution::FlagResult resFlags;
            //
            // fetch data using base metadata
            cpu::execution::OperandData data = helpers::decoder::fetchOperands(instr, RF.PC.readPC(), RAM, RF, CpuTypeFamily);
            resFlags.overflow = false;// set decimal flag

            // compute cycle cost (fixed for CLI)
            cycleCost = instr.cycleCount;
            //commit state
            instructionMetadata = makeInstructionMetaData(instr, cycleCost, 0, resFlags);
            RF.SR.commitFlags(instr, instructionMetadata);
        };
        
        private:
            cpu::execution::ResolvedInfoInstruction makeInstructionMetaData(cpu::instructions::Instruction instr, uint8_t resolvedCycleCount, uint8_t resultByte, cpu::execution::FlagResult flags) {
                cpu::execution::ResolvedInfoInstruction payload;
                payload.instruc = instr;
                // load flags
                if (flags.carry.has_value()) { payload.carry = flags.carry; }
                if (flags.overflow.has_value()) { payload.overflow = flags.overflow; }
                if (flags.zero.has_value()) { payload.zero = flags.zero; }
                if (flags.negative.has_value()) { payload.negative = flags.negative; }
                if (flags.decimal.has_value()) { payload.decimal = flags.decimal; }
                if (flags.interrupt.has_value()) { payload.interrupt = flags.interrupt; }
                payload.znSource = resultByte;
                //payload.isPrimedData = true;
                return payload;
                };

    };

};