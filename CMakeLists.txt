cmake_minimum_required(VERSION 3.28)
project(cli_parse C)

set(CMAKE_C_STANDARD 11)

add_executable(cli_parse main.c
        string/string.h
        string/string.c
        arena/Arena.c
        arena/Arena.h
        log/Log.h
        log/Log.c
        stack/stack.h
        stack/stack.c
        queue/Queue.h
        queue/Queue.c)
