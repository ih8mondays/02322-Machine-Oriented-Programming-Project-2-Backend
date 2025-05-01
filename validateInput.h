#ifndef INPUTVALIDATION_H
#define INPUTVALIDATION_H

typedef enum Command {
    LD,             // Load deck
    LD_FILENAME,
    SW,             // Show
    SI,             // Shuffle Split
    SI_SPLIT,
    SR,             // Shuffle Random
    SD,             // Save Deck
    QQ,             // Quit program
    Q,              // Go to Initilization
    P,              // Go to PlayPhase
    MOVE,
    INVALID,
    BREAKS_RULES
  } Command;

Command validateInput(char * input);
extern char * toCommandName[];

#endif //INPUTVALIDATION_H
