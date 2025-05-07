#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL3/SDL.h>
#include "gameController.h"
#include "../../main.h"
#include "../model/validateInput.h"
#include "../model/loadCards.h"
#include "../model/moveCard.h"
#include "../view/printBoard.h"
#include "../model/saveCards.h"
#include "../model/shuffleDeck.h"
#include "../model/fillBoard.h"
#include "../view/GUI.h"


void startUpPhaseCommands(Command command);
void playPhaseCommands(Command command);

// Game variables
char input[50];
char boardMessage[100];
int dontOverwriteMessage = 0; // flag - error message already set
Command command = NO_CMD_YET;
PrintState printState = PRINT_EMPTY;
static GamePhase gamePhase = STARTUP_PHASE;

// Initialize empty board and deck
Card * deckHeader = NULL;
Card * columnHeader[7] = {NULL};
Card * foundationHeader[4] = {NULL};
int visual;
void playGame() {
    visual=0;
    if (visual==1) {
        createGUI();
        draw_empty_board();
    }

    while (command != CMD_QQ) {
        visual=0;
        // Print current board
        switch (printState) {
            case PRINT_EMPTY:
                if (visual!=1) {
                    print_empty_board();
                }
                else {
                    draw_empty_board();
                }
                break;
            case PRINT_HIDDEN:
                if (visual!=1) {
                    print_filled_board();
                }
                else {
                    draw_filled_board();
                }
                break;
            case PRINT_SHOWN:
                reveal_all_cards(deckHeader);
                if (visual!=1) {
                    print_filled_board();
                }
                else {
                    draw_filled_board();
                }
                break;
            case PRINT_PLAY:
                if (visual!=1) {
                    print_current_board();
                } break;
            default: printf("Error in printState.");
        }

        setBoardMessage("OK");

        // receive input
        memset(input, '\0', sizeof(input));
        fgets(input,sizeof(input), stdin);

        // reset flag
        dontOverwriteMessage = 0;

        // validate input
        command = validateInput(input);

        // execute command
        if (gamePhase == STARTUP_PHASE) {
            startUpPhaseCommands(command);
        } else if (gamePhase == PLAY_PHASE) {
            playPhaseCommands(command);
        }
    }
}

void startUpPhaseCommands(Command command) {
    switch (command) {
        case CMD_LD:
        case CMD_LD_FILENAME:
            loadCards(input);
            if (deckHeader != NULL) {
                printState = PRINT_HIDDEN;
            }
            break;
        case CMD_SW:
            if (printState == PRINT_HIDDEN && deckHeader != NULL) {
                printState = PRINT_SHOWN;
            } else if (printState == PRINT_SHOWN) {
                setBoardMessage("The board is already visible.");
            } else {
                setBoardMessage("You must load a deck first.");
            }
            break;
        case CMD_SI:
        case CMD_SI_SPLIT: splitShuffle(command,input); break;
        case CMD_SR: randomShuffle(deckHeader); break;
        case CMD_SD:
        case CMD_SD_FILENAME: saveCards(command, input); break;
        case CMD_P:
            fillBoard();
            if (deckHeader == NULL) { break;}
            gamePhase = PLAY_PHASE;
            printState = PRINT_PLAY;
            break;
        case CMD_QQ: break;     //exit(0);
        case CMD_Q:
        case CMD_MOVE: setBoardMessage("Command not available in the STARTUP phase."); break;
        case CMD_INVALID: dontOverwriteMessage? : setBoardMessage("Invalid input"); break;
        default: !yukonDebugMode? : setBoardMessage("Input validation failed"); break;
    }
}

void playPhaseCommands(Command command) {
    switch (command) {
        case CMD_LD:
        case CMD_LD_FILENAME:
        case CMD_SW:
        case CMD_SI:
        case CMD_SI_SPLIT:
        case CMD_SR:
        case CMD_SD:
        case CMD_P:
        case CMD_QQ: setBoardMessage("Command not available in the PLAY phase."); break;
        case CMD_Q:
            gamePhase = STARTUP_PHASE;
            printState = PRINT_SHOWN;
            break;
        case CMD_MOVE: moveCard(input); break;
        case CMD_INVALID: dontOverwriteMessage? : setBoardMessage("Invalid input"); break;
        default: !yukonDebugMode? : setBoardMessage("Inputvalidation failed"); break;
    }
}

void setBoardMessage(char * newMessage) {
    !yukonDebugMode? : memset(boardMessage, '\0', sizeof(boardMessage));
    !yukonDebugMode? : snprintf(boardMessage,sizeof(boardMessage),newMessage);
}

void setBoardErrorMessage(int line, char * fileName) {
    !yukonDebugMode? : memset(boardMessage, '\0', sizeof(boardMessage));
    !yukonDebugMode? : snprintf(boardMessage,sizeof(boardMessage),"Error at line %d in %s",line,fileName);
    dontOverwriteMessage = 1;
}



