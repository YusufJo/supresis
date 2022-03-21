cmake_minimum_required(VERSION 3.17)
project(supresis)

set(CMAKE_CXX_STANDARD 17)

add_executable(supresis main.cpp Chunk.cpp Chunk.h Entry.cpp Entry.h)