#ifndef INPUTVALIDATION_H
#define INPUTVALIDATION_H

typedef enum Command {
    NO_CMD_YET,
    CMD_LD,             // Load deck
    CMD_LD_FILENAME,    // ^ with input
    CMD_SW,             // Show
    CMD_SI,             // Shuffle Split
    CMD_SI_SPLIT,       // ^ with input
    CMD_SR,             // Shuffle Random
    CMD_SD,             // Save Deck
    CMD_SD_FILENAME,    // ^ with input
    CMD_QQ,             // Quit program
    CMD_Q,              // Go to STARTUP_PHASE
    CMD_P,              // Go to PLAY_PHASE
    CMD_MOVE,
    CMD_INVALID
  } Command;

Command validateInput(char * input);
int isRank(char input);
int isSuit(char input);
extern char * toCommandName[];

#endif //INPUTVALIDATION_H
