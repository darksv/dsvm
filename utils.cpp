//
// Created by darksv on 10.07.2016.
//

#include <cstdint>
#include <string>
#include "utils.hpp"

std::string formatOperand(const Operand& operand)
{
    std::stringstream ss;

    if (operand.fromRegister)
    {
        switch (operand.kind)
        {
            case OperandKind::i8:
                ss << "r" << operand.value << ":" << (operand.pointer ? "*" : "") << "i8";
                break;
            case OperandKind::i16:
                ss << "r" << operand.value << ":" << (operand.pointer ? "*" : "") << "i16";
                break;
            case OperandKind::i32:
                ss << "r" << operand.value << ":" << (operand.pointer ? "*" : "") << "i32";
                break;
            case OperandKind::i64:
                ss << "r" << operand.value << ":" << (operand.pointer ? "*" : "") << "i64";
                break;
            case OperandKind::u8:
                ss << "r" << operand.value << ":" << (operand.pointer ? "*" : "") << "u8";
                break;
            case OperandKind::u16:
                ss << "r" << operand.value << ":" << (operand.pointer ? "*" : "") << "u16";
                break;
            case OperandKind::u32:
                ss << "r" << operand.value << ":" << (operand.pointer ? "*" : "") << "u32";
                break;
            case OperandKind::u64:
                ss << "r" << operand.value << ":" << (operand.pointer ? "*" : "") << "u64";
                break;
            case OperandKind::f32:
                ss << "r" << operand.value << ":" << (operand.pointer ? "*" : "") << "f32";
                break;
            case OperandKind::f64:
                ss << "r"<< operand.value << ":" << (operand.pointer ? "*" : "") << "f64";
                break;
            default:
                ss << "?:?";
        }
    }
    else
    {
        switch (operand.kind)
        {
            case OperandKind::i8:
                ss << (operand.fromRegister ? "r" : "") << *reinterpret_cast<const int8_t*>(&operand.value) << ":" << (operand.pointer ? "*" : "") << "i8";
                break;
            case OperandKind::i16:
                ss << (operand.fromRegister ? "r" : "") << *reinterpret_cast<const int16_t*>(&operand.value) << ":" << (operand.pointer ? "*" : "") << "i16";
                break;
            case OperandKind::i32:
                ss << (operand.fromRegister ? "r" : "") << *reinterpret_cast<const int32_t*>(&operand.value) << ":" << (operand.pointer ? "*" : "") << "i32";
                break;
            case OperandKind::i64:
                ss << (operand.fromRegister ? "r" : "") << *reinterpret_cast<const int64_t*>(&operand.value) << ":" << (operand.pointer ? "*" : "") << "i64";
                break;
            case OperandKind::u8:
                ss << (operand.fromRegister ? "r" : "") << *reinterpret_cast<const uint8_t*>(&operand.value) << ":" << (operand.pointer ? "*" : "") << "u8";
                break;
            case OperandKind::u16:
                ss << (operand.fromRegister ? "r" : "") << *reinterpret_cast<const uint16_t*>(&operand.value) << ":" << (operand.pointer ? "*" : "") << "u16";
                break;
            case OperandKind::u32:
                ss << (operand.fromRegister ? "r" : "") << *reinterpret_cast<const uint32_t*>(&operand.value) << ":" << (operand.pointer ? "*" : "") << "u32";
                break;
            case OperandKind::u64:
                ss << (operand.fromRegister ? "r" : "") << *reinterpret_cast<const uint64_t*>(&operand.value) << ":" << (operand.pointer ? "*" : "") << "u64";
                break;
            case OperandKind::f32:
                ss << (operand.fromRegister ? "r" : "") << *reinterpret_cast<const float*>(&operand.value) << ":" << (operand.pointer ? "*" : "") << "f32";
                break;
            case OperandKind::f64:
                ss << (operand.fromRegister ? "r" : "") << *reinterpret_cast<const double*>(&operand.value) << ":" << (operand.pointer ? "*" : "") << "f64";
                break;
            default:
                ss << "?:?";

        }
    }

    return ss.str();
}