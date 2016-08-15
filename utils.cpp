//
// Created by darksv on 10.07.2016.
//

#include <cstdint>
#include <string>
#include "utils.hpp"

std::string formatDataType(DataType dataType)
{
    switch (dataType)
    {
        case DataType::i8:
            return "i8";
        case DataType::i16:
            return "i16";
        case DataType::i32:
            return "i32";
        case DataType::i64:
            return "i64";
        case DataType::u8:
            return "u8";
        case DataType::u16:
            return "u16";
        case DataType::u32:
            return "u32";
        case DataType::u64:
            return "u64";
        case DataType::f32:
            return "f32";
        case DataType::f64:
            return "f64";
    }

    /* If data type is invalid */
    return "?";
}

std::string formatOpcode(Opcode opcode)
{
    return OPCODES[opcode].mnemonics;
}

std::string formatOperand(const Operand& operand)
{
    std::stringstream ss;

    if (operand.fromRegister)
    {
        ss << "r" << operand.value << ":" << (operand.pointer ? "*" : "") << formatDataType(operand.type);
    }
    else
    {
        switch (operand.type)
        {
            case DataType::i8:
                ss << operandAs<int8_t>(operand);
                break;
            case DataType::i16:
                ss << operandAs<int16_t>(operand);
                break;
            case DataType::i32:
                ss << operandAs<int32_t>(operand);
                break;
            case DataType::i64:
                ss << operandAs<int64_t>(operand);
                break;
            case DataType::u8:
                ss << operandAs<uint8_t>(operand);
                break;
            case DataType::u16:
                ss << operandAs<uint16_t>(operand);
                break;
            case DataType::u32:
                ss << operandAs<uint32_t>(operand);
                break;
            case DataType::u64:
                ss << operandAs<uint64_t>(operand);
                break;
            case DataType::f32:
                ss << operandAs<float>(operand);
                break;
            case DataType::f64:
                ss << operandAs<double>(operand);
                break;
            default:
                ss << "?";

        }
        ss << ":" << (operand.pointer ? "*" : "") << formatDataType(operand.type);
    }

    return ss.str();
}

Operand makeOperand(uint8_t byte)
{
    const std::uint8_t typeMask = 0x0F;
    const std::uint8_t pointerMask = (1 << 4);

    return {
            .type = static_cast<DataType>(byte & typeMask),
            .value = 0,
            .fromRegister = (byte >> 7),
            .pointer = byte & pointerMask
    };
}