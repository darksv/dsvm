//
// Created by darksv on 10.07.2016.
//

#pragma once

#include <iomanip>
#include <string>
#include "Interpreter.hpp"

template<typename T>
std::string formatHex(T value)
{
    std::stringstream ss;
    ss << std::uppercase << std::hex << std::setw(sizeof(T) * 2) << std::setfill('0') << static_cast<uint32_t>(value) << "h";

    return ss.str();
}

std::string formatOperand(const Operand& operand);