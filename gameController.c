#include "gameController.h"
#include "main.h"
#include "validateInput.h"
#include "loadCards.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void startUpPhaseCommand(Command command);
void playPhaseCommand(Command command);

char input[50];
Command lastCommand;
char boardMessage[100];
static GamePhase gamePhase;


void playGame() {



    while (1) {

        // Print current board


        // receive input
        memset(input, '\0', sizeof(input));
        fgets(input,sizeof(input), stdin);


        // validate input
        Command inputCommand = validateInput(input);

        // execute command
        if (gamePhase == STARTUP_PHASE) {
            startUpPhaseCommand(inputCommand);
        } else if (gamePhase == PLAY_PHASE) {
            playPhaseCommand(inputCommand);
        }



        // handle CMD_BREAKS_RULES


        // update lastCommand


        // repeat
    }

}

void playPhaseCommand(Command command) {
    switch (command) {
        case CMD_LD:
        case CMD_LD_FILENAME:
        case CMD_SW:
        case CMD_SI:
        case CMD_SI_SPLIT:
        case CMD_SR:
        case CMD_SD:
        case CMD_P:
        case CMD_QQ: snprintf(boardMessage,sizeof(boardMessage),"Command not available in the PLAY phase."); break;
        case CMD_Q:
        case CMD_MOVE:
        case CMD_INVALID:
        case CMD_BREAKS_RULES:
        default: !debug? : printf("\n\nInputvalidation failed\n");
    }
}

void startUpPhaseCommand(Command command) {
    switch (command) {
        case CMD_LD:
        case CMD_LD_FILENAME: loadCards(input); break;
        case CMD_SW: //TODO saveCards(deckHeader, input);   needs work
        case CMD_SI:
        case CMD_SI_SPLIT:
        case CMD_SR:
        case CMD_SD:
        case CMD_P: gamePhase = PLAY_PHASE; break;
        case CMD_QQ: exit(0);
        case CMD_Q:
            //  case CMD_MOVE:
            //  case CMD_INVALID:
            //  case CMD_BREAKS_RULES:
        default: !debug? : printf("\n\nInputvalidation failed\n");
    }
}



