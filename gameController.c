#include "gameController.h"
#include "main.h"
#include "validateInput.h"
#include "loadCards.h"
#include "moveCard.h"
#include "printBoard.h"
#include "saveCards.h"
#include "shuffleDeck.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void startUpPhaseCommands(Command command);
void playPhaseCommands(Command command);

// Game variables
char input[50];
Command command = NO_CMD_YET;
char boardMessage[100];
static GamePhase gamePhase;
Card * deckHeader = NULL;

// Initialize empty board
Card * columnHeader[] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL};
Card * foundationHeader[] = {NULL,NULL,NULL,NULL};

void playGame() {

    print_empty_board();

    while (command != CMD_QQ) {

        // Print current board


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
        //      make sure to print correctly

    }

}

void startUpPhaseCommands(Command command) {
    switch (command) {
        case CMD_LD:
        case CMD_LD_FILENAME: loadCards(input); break; // TODO fix parameters
        case CMD_SW: // TODO fix parameters
        case CMD_SI: // TODO fix parameters
        case CMD_SI_SPLIT: // TODO fix parameters
        case CMD_SR: randomShuffle(deckHeader); break;
        case CMD_SD: //saveCards(); // TODO fix parameters
        case CMD_P: gamePhase = PLAY_PHASE; break;
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



