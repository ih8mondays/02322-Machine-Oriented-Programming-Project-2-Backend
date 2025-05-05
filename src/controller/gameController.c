#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gameController.h"
#include "../../main.h"
#include "../model/validateInput.h"
#include "../model/loadCards.h"
#include "../model/moveCard.h"
#include "../view/printBoard.h"
#include "../model/saveCards.h"
#include "../model/shuffleDeck.h"
#include "../model/fillBoard.h"


void startUpPhaseCommands(Command command);
void playPhaseCommands(Command command);

// Game variables
char input[50] = "Input must not be longer than 50 characters.";
char boardMessage[100];
Command command = NO_CMD_YET;
PrintState printState = PRINT_STARTUP_EMPTY;
static GamePhase gamePhase = STARTUP_PHASE;

// Initialize empty board and deck
Card * deckHeader = NULL;
Card * columnHeader[] = {NULL};
Card * foundationHeader[] = {NULL};

void playGame() {

    while (command != CMD_QQ) {

        // Print current board
        switch (printState) {
            case PRINT_STARTUP_EMPTY: print_empty_board(); break;
            case PRINT_STARTUP_HIDDEN: print_hidden_board(); break;
            case PRINT_STARTUP_SHOWN: print_shown_board(); break;
            case PRINT_PLAY:                               break; //TODO missing print command
            default: printf("Error in printState.");
        }

        // receive input
        memset(input, '\0', sizeof(input));
        fgets(input,sizeof(input), stdin);

        // validate input
        command = validateInput(input);

        // execute command
        if (gamePhase == STARTUP_PHASE) {
            startUpPhaseCommands(command);
        } else if (gamePhase == PLAY_PHASE) {
            playPhaseCommands(command);
        }


        // TODO handle CMD_BREAKS_RULES

    }

}

void startUpPhaseCommands(Command command) {
    switch (command) {
        case CMD_LD:
        case CMD_LD_FILENAME:
            loadCards(input);
            printState = PRINT_STARTUP_HIDDEN;
            break;
        case CMD_SW: printState = PRINT_STARTUP_SHOWN; break;
        case CMD_SI:
        case CMD_SI_SPLIT: splitShuffle(command,input); break;
        case CMD_SR: randomShuffle(deckHeader); break;
        case CMD_SD:
        case CMD_SD_FILENAME: saveCards(command, input); break;
        case CMD_P:
            fillBoard();
            gamePhase = PLAY_PHASE;
            break;
        case CMD_QQ: break;     //exit(0);
        case CMD_Q:
        case CMD_MOVE: setBoardMessage("Command not available in the PLAY phase."); break;
        case CMD_INVALID: setBoardMessage("Invalid input"); break;
        default: !debug? : setBoardMessage("Input validation failed"); break;
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
        case CMD_Q: gamePhase = STARTUP_PHASE; break;
        case CMD_MOVE: moveCard(input); break;
        case CMD_INVALID: setBoardMessage("Invalid input"); break;
        default: !debug? : setBoardMessage("Inputvalidation failed"); break;
    }
}

void setBoardMessage(char * newMessage) {
    memset(boardMessage, '\0', sizeof(boardMessage));
    snprintf(boardMessage,sizeof(boardMessage),newMessage);
}



