#include "Interpreter.hpp"

int main(int argc, char** argv)
{
    if (argc > 1)
    {
        Interpreter interpreter{argv[1]};
        interpreter.readMeta();

        while (interpreter.hasNextInstruction())
        {
            interpreter.nextInstruction();
        }
    }

    return 0;
}

