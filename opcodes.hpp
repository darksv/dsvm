//
// Created by darksv on 10.07.2016.
//

#pragma once

#include <map>

enum class Opcode : uint8_t
{
    IN  = 0x00,
    MOV = 0x01,
    ADD = 0x02,
    OUT = 0x03,
    JMP = 0x04,
    NOP = 0xFF
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
};

struct OpcodeInfo
{
    std::uint8_t numOperands;
    std::string mnemonics;
};

static std::map<Opcode, OpcodeInfo> OPCODES = {
    {Opcode::IN,  {1, "in"}},
    {Opcode::MOV, {2, "mov"}},
    {Opcode::ADD, {3, "add"}},
    {Opcode::OUT, {1, "out"}},
    {Opcode::JMP, {1, "jmp"}},
    {Opcode::NOP, {0, "nop"}},
};