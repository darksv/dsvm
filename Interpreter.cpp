//
// Created by darksv on 10.07.2016.
//

#include <iostream>
#include "Interpreter.hpp"
#include "opcodes.hpp"
#include "utils.hpp"

Interpreter::Interpreter(const std::string& inputFile) :
    input_{inputFile}
{

}

Interpreter::~Interpreter()
{

}

void Interpreter::readMeta()
{
    meta_ = read<Metadata>();

    std::cout << "; Version = " << meta_.version << std::endl
              << "; Stack size = " << meta_.stackSize << std::endl
              << "; Entry point = " << formatHex(meta_.entryPoint) << std::endl;
}

bool Interpreter::hasNextInstruction() const
{
    return !input_.eof();
}

void Interpreter::nextInstruction()
{
    Opcode op = getOpcode();

    switch (op)
    {
        case Opcode::IN:
        {
            auto o1 = getOperand();
            std::cout << "in " << formatOperand(o1) << std::endl;

            break;
        }
        case Opcode::ADD:
        {
            auto o1 = getOperand();
            auto o2 = getOperand();
            auto o3 = getOperand();
            std::cout << "add " << formatOperand(o1) << ", " << formatOperand(o2) << ", " << formatOperand(o3) << std::endl;

            break;
        }
        case Opcode::MOV:
        {
            auto o1 = getOperand();
            auto o2 = getOperand();
            std::cout << "mov " << formatOperand(o1) << ", " << formatOperand(o2) << std::endl;

            break;
        }
        case Opcode::OUT:
        {
            auto o1 = getOperand();
            std::cout << "out " << formatOperand(o1) << std::endl;

            break;
        }
        case Opcode::JMP:
        {
            auto o1 = getOperand();
            std::cout << "jmp " << formatOperand(o1) << std::endl;

            break;
        }
        case Opcode::NOP:
        {
            std::cout << "nop" << std::endl;
            break;
        }
        /* Since we use a single byte for opcodes, some of the values are not used */
        default:
        {
            std::cerr << "; unknown instruction: " << formatHex(static_cast<uint8_t>(op)) << std::endl;
        }
    }
}

Opcode Interpreter::getOpcode()
{
    return read<Opcode>();
}

Operand Interpreter::getOperand()
{
    const auto type = read<uint8_t>();
    const std::uint8_t typeMask = 0x0F;
    const std::uint8_t pointerMask = (1 << 4);

    Operand operand;
    operand.kind = static_cast<OperandKind>(type & typeMask);
    operand.pointer = type & pointerMask;
    operand.fromRegister = (type >> 7);

    /* Read register number */
    if (operand.fromRegister)
    {
        operand.value = read<uint8_t>();
        return operand;
    }

    switch (operand.kind)
    {
        case OperandKind::i8:
        case OperandKind::u8:
            operand.value = read<uint8_t>();
            break;
        case OperandKind::i16:
        case OperandKind::u16:
            operand.value = read<uint16_t>();
            break;
        case OperandKind::i32:
        case OperandKind::u32:
        case OperandKind::f32:
            operand.value = read<uint32_t>();
            break;
        case OperandKind::i64:
        case OperandKind::u64:
        case OperandKind::f64:
            operand.value = read<uint64_t>();
            break;
    }

    return operand;
}