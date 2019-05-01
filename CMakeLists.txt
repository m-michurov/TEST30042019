cmake_minimum_required(VERSION 3.12)
project(TEST30042019 C)

set(CMAKE_C_STANDARD 11)

add_executable(TEST30042019 main.c stringlist.c stringlist.h grammarlist.c grammarlist.h grammar.c grammar.h)