#include <iostream>
#include "Fetcher.hpp"
#include "utils.hpp"

int main(int argc, char** argv)
{
    if (argc > 1)
    {
        Fetcher fetcher{argv[1]};
        fetcher.readMeta();

        Instruction inst;
        while (fetcher.fetch(inst))
        {
            switch (OPCODES[inst.opcode].numOperands)
            {
                case 1:
                    std::cout << formatOpcode(inst.opcode) << " "
                              << formatOperand(inst.operands[0]) << "\n";
                    break;
                case 2:
                    std::cout << formatOpcode(inst.opcode) << " "
                              << formatOperand(inst.operands[0]) << ", "
                              << formatOperand(inst.operands[1]) << "\n";
                    break;
                case 3:
                    std::cout << formatOpcode(inst.opcode) << " "
                              << formatOperand(inst.operands[0]) << ", "
                              << formatOperand(inst.operands[1]) << ", "
                              << formatOperand(inst.operands[2]) << "\n";
                    break;
                default:
                    std::cout << formatOpcode(inst.opcode) << "\n";
                    break;
            }
        }
    }

    return 0;
}

