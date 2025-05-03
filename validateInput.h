#ifndef INPUTVALIDATION_H
#define INPUTVALIDATION_H

typedef enum Command {
    CMD_LD,             // Load deck
    CMD_LD_FILENAME,    // ^ with input
    CMD_SW,             // Show
    CMD_SI,             // Shuffle Split
    CMD_SI_SPLIT,       // ^ with input
    CMD_SR,             // Shuffle Random
    CMD_SD,             // Save Deck
    CMD_QQ,             // Quit program
    CMD_Q,              // Go to Initilization
    CMD_P,              // Go to PlayPhase
    CMD_MOVE,
    CMD_INVALID,
    CMD_BREAKS_RULES
  } Command;

Command validateInput(char * input);
extern char * toCommandName[];

#endif //INPUTVALIDATION_H
