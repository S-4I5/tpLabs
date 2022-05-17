cmake_minimum_required(VERSION 3.17)
project(TP)

set(CMAKE_CXX_STANDARD 20)

add_executable(TP GRR/main.cpp GRR/Graph.h GRR/SmartMatrix.h GRR/command_struct.h)