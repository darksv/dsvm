//
// Created by darksv on 10.07.2016.
//

#pragma once

enum class Opcode : uint8_t
{
    IN  = 0x00,
    MOV = 0x01,
    ADD = 0x02,
    OUT = 0x03,
    JMP = 0x04,
    NOP = 0xFF
};