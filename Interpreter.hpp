//
// Created by darksv on 10.07.2016.
//

#pragma once

#include <fstream>
#include "opcodes.hpp"

struct Metadata
{
    std::uint16_t version;
    std::uint16_t stackSize;
    std::uint32_t entryPoint;
};

enum class DataType
{
    i8 = 0x01, i16, i32, i64,
    u8, u16, u32, u64,
    f32, f64
};

struct Operand
{
    DataType type;
    std::uint64_t value;
    bool fromRegister;
    bool pointer;

    Operand(uint8_t byte)
    {
        const std::uint8_t typeMask = 0x0F;
        const std::uint8_t pointerMask = (1 << 4);

        type = static_cast<DataType>(byte & typeMask);
        pointer = byte & pointerMask;
        fromRegister = (byte >> 7);
    }
};

class Interpreter
{
public:
    Interpreter(const std::string& inputFile);
    ~Interpreter();

    void readMeta();
    bool hasNextInstruction() const;
    void nextInstruction();

protected:
    template<typename T>
    T read()
    {
        T value;
        input_.read(reinterpret_cast<char*>(&value), sizeof(T));

        return value;
    }

    Opcode getOpcode();
    Operand getOperand();
    Operand getRegister();
    Operand getConstant();

private:
    Metadata meta_;
    std::ifstream input_;
    uint32_t registers_[256];
};



