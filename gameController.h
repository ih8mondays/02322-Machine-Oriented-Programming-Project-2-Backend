#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

typedef enum GamePhase {
    STARTUP_PHASE,
    PLAY_PHASE
  } GamePhase;

void playGame();
extern char boardMessage[100];

#endif //GAMECONTROLLER_H
