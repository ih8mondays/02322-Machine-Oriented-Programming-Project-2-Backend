#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include "generateCards.h"

typedef enum GamePhase {
    STARTUP_PHASE,
    PLAY_PHASE
  } GamePhase;

void playGame();
void setBoardMessage(char * newMessage);

extern char boardMessage[100];
extern Card * columnHeader[];
extern Card * foundationHeader[];
extern Card * deckHeader;

#endif //GAMECONTROLLER_H
