cmake_minimum_required(VERSION 3.5)
project(DSVM)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(SOURCE_FILES opcodes.hpp Fetcher.cpp Fetcher.hpp utils.cpp utils.hpp)

set(DISASM_SOURCE_FILES disasm.cpp ${SOURCE_FILES} Instruction.cpp Instruction.hpp)
add_executable(disasm ${DISASM_SOURCE_FILES})