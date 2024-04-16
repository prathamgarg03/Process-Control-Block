cmake_minimum_required(VERSION 3.27)
project(Process_Control_Block C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Process_Control_Block
        data_structure.h
        helper.c
        helper.h
        list.h
        main.c
        operations.c
        operations.h)
