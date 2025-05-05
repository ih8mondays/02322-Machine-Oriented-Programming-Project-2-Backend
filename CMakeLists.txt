cmake_minimum_required(VERSION 3.30)
project(YukonBackend C)

set(CMAKE_C_STANDARD 11)

add_executable(YukonBackend
        main.c
        src/model/generateCards.c
        src/model/generateCards.h
        src/model/fillBoard.c
        src/model/fillBoard.h
        src/model/moveCard.c
        src/model/moveCard.h
        src/model/saveCards.c
        src/model/saveCards.h
        src/model/loadCards.c
        src/model/loadCards.h
        src/model/validateInput.c
        src/model/validateInput.h
        src/model/shuffleDeck.c
        src/model/shuffleDeck.h
        src/view/printBoard.c
        src/view/printBoard.h
        src/controller/gameController.c
        src/controller/gameController.h
)
