cmake_minimum_required(VERSION 3.30)
project(YukonBackend C)

set(CMAKE_C_STANDARD 11)

add_executable(YukonBackend
        main.c
        generateCards.c
        generateCards.h
        fillBoard.c
        fillBoard.h
        moveCard.c
        moveCard.h
        saveCards.c
        saveCards.h
)
