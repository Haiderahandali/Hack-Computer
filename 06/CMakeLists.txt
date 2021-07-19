cmake_minimum_required(VERSION 3.17)
project(ASSEMBLER)

add_executable(Parser
        parse.c
        hack.c
        hashtable.c
        )
