#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include "../model/generateCards.h"
#include "../model/validateInput.h"

typedef enum GamePhase {
    STARTUP_PHASE,
    PLAY_PHASE
  } GamePhase;

typedef enum PrintState {
    PRINT_EMPTY,
    PRINT_HIDDEN,
    PRINT_SHOWN,
    PRINT_PLAY
  } PrintState;

void playGame();
void setBoardMessage(char * newMessage);
void setBoardErrorMessage(int line, char * fileName);

extern char input[50];
extern char boardMessage[100];
extern int specificError;
extern Command command;
extern Card * columnHeader[];
extern Card * foundationHeader[];
extern Card * deckHeader;

#endif //GAMECONTROLLER_H
