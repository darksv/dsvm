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
                ss << operand.as<int8_t>();
                break;
            case DataType::i16:
                ss << operand.as<int16_t>();
                break;
            case DataType::i32:
                ss << operand.as<int32_t>();
                break;
            case DataType::i64:
                ss << operand.as<int64_t>();
                break;
            case DataType::u8:
                ss << operand.as<uint8_t>();
                break;
            case DataType::u16:
                ss << operand.as<uint16_t>();
                break;
            case DataType::u32:
                ss << operand.as<uint32_t>();
                break;
            case DataType::u64:
                ss << operand.as<uint64_t>();
                break;
            case DataType::f32:
                ss << operand.as<float>();
                break;
            case DataType::f64:
                ss << operand.as<double>();
                break;
            default:
                ss << "?";

        }
        ss << ":" << (operand.pointer ? "*" : "") << formatDataType(operand.type);
    }

    return ss.str();
}