//
// Created by darksv on 10.07.2016.
//

#include <iostream>
#include "Fetcher.hpp"
#include "opcodes.hpp"
#include "utils.hpp"
#include "Instruction.hpp"

Fetcher::Fetcher(const std::string& inputFile) :
    input_{inputFile}
{

}

Fetcher::~Fetcher()
{

}

void Fetcher::readMeta()
{
    meta_ = read<Metadata>();

    std::cout << "; Version = " << meta_.version << std::endl
              << "; Stack size = " << meta_.stackSize << std::endl
              << "; Entry point = " << formatHex(meta_.entryPoint) << std::endl;
}

bool Fetcher::hasNextInstruction() const
{
    return !input_.eof();
}

bool Fetcher::fetch(Instruction& instruction)
{
    if (!hasNextInstruction())
        return false;

    instruction.opcode = getOpcode();
    for (std::size_t i = 0; i < OPCODES[instruction.opcode].numOperands; ++i)
        instruction.operands[i] = getOperand();

    //std::cerr << "; unknown instruction: " << formatHex(static_cast<uint8_t>(instruction.opcode)) << std::endl;

    return true;
}

Opcode Fetcher::getOpcode()
{
    return read<Opcode>();
}

Operand Fetcher::getOperand()
{
    Operand operand = makeOperand(read<uint8_t>());

    /* Read register number */
    if (operand.fromRegister)
    {
        operand.value = read<uint8_t>();
        return operand;
    }

    switch (operand.type)
    {
        case DataType::i8:
        case DataType::u8:
            operand.value = read<uint8_t>();
            break;
        case DataType::i16:
        case DataType::u16:
            operand.value = read<uint16_t>();
            break;
        case DataType::i32:
        case DataType::u32:
        case DataType::f32:
            operand.value = read<uint32_t>();
            break;
        case DataType::i64:
        case DataType::u64:
        case DataType::f64:
            operand.value = read<uint64_t>();
            break;
    }

    return operand;
}

Operand Fetcher::getRegister()
{
    auto operand = getOperand();

    if (!operand.fromRegister)
        std::cerr << "Register expected, got constant." << std::endl;

    return operand;
}

Operand Fetcher::getConstant()
{
    auto operand = getOperand();

    if (operand.fromRegister)
        std::cerr << "Contstant expected, got register." << std::endl;

    return operand;
}