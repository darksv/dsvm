//
// Created by DN on 14.08.2016.
//

#pragma once


#include "opcodes.hpp"

const unsigned MAX_OPERANDS = 3;


struct Instruction
{
    Opcode opcode;
    Operand operands[MAX_OPERANDS];
};


