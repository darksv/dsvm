//
// Created by darksv on 10.07.2016.
//

#pragma once

#include <iomanip>
#include <string>
#include "Fetcher.hpp"

template<typename T>
std::string formatHex(T value)
{
    std::stringstream ss;
    ss << std::uppercase << std::hex << std::setw(sizeof(T) * 2) << std::setfill('0') << static_cast<uint32_t>(value) << "h";

    return ss.str();
}

std::string formatDataType(DataType dataType);
std::string formatOpcode(Opcode opcode);
std::string formatOperand(const Operand& operand);

Operand makeOperand(uint8_t byte);

template <typename T>
constexpr T operandAs(const Operand& operand)
{
    return *reinterpret_cast<const T*>(&operand.value);
}