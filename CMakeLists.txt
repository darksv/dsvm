cmake_minimum_required(VERSION 3.5)
project(DSVM)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(SOURCE_FILES opcodes.hpp Interpreter.cpp Interpreter.hpp utils.cpp utils.hpp)

set(INTERPRETER_SOURCE_FILES main.cpp ${SOURCE_FILES})
add_executable(interpreter ${INTERPRETER_SOURCE_FILES})