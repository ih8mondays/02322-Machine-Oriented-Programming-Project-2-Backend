#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include "../model/generateCards.h"

typedef enum GamePhase {
    STARTUP_PHASE,
    PLAY_PHASE
  } GamePhase;

typedef enum PrintState {
    PRINT_STARTUP_EMPTY,
    PRINT_STARTUP_HIDDEN,
    PRINT_STARTUP_SHOWN,
    PRINT_PLAY
  } PrintState;

void playGame();
void setBoardMessage(char * newMessage);

extern char boardMessage[100];
extern Card * columnHeader[];
extern Card * foundationHeader[];
extern Card * deckHeader;

#endif //GAMECONTROLLER_H
