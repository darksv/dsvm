//
// Created by darksv on 10.07.2016.
//

#pragma once

#include <fstream>
#include "opcodes.hpp"
#include "Instruction.hpp"

struct Metadata
{
    std::uint16_t version;
    std::uint16_t stackSize;
    std::uint32_t entryPoint;
};

class Fetcher
{
public:
    Fetcher(const std::string& inputFile);
    ~Fetcher();

    void readMeta();
    bool hasNextInstruction() const;
    bool fetch(Instruction& instruction);

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



