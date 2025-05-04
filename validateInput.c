#include "main.h"
#include "validateInput.h"

#include <ctype.h>

// Possible valid inputs ... C1-C7 & F1-F4
// C = Column, F = Foundation, R = Rank, S = Suit
//-----------------------------------------------
//   MOVE
//      CX:RS->CX
//      CX:RS->FX          command isn't useful
//      CX->CX
//      CX->FX
//      FX->CX
//   LD                 Load deck
//   LD_FILENAME
//   SW                 Show
//   SI_SPLIT           Shuffle Split
//   SR                 Shuffle Random
//   SD                 Save Deck
//   QQ                 Quit program
//   Q                  Restart
//   P                  Start PlayPhase
//
//-----------------------------------------------
char * toCommandName[] = {"LD","LD_FILENAME","SW","SI","SI_SPLIT",
                          "SR","SD","QQ","Q","P","MOVE","INVALID",
                         "BREAKS_RULES"};
// TODO set chars to UPPERCASE so C and c is accepted

int isRank(char input);
int isSuit(char input);
void toUpperCase(char * input);
Command validateMove(char * input);
Command validateLoadFile(char * input);
Command validateShuffleSplit(char * input);


Command validateInput(char * input) {

    convertLowerCaseInput? toUpperCase(input) : 0 ;

    switch (input[0]) {
        case 'C':
        case 'F': return validateMove(input);
        case 'L': return validateLoadFile(input);
        case 'S':
            switch (input[1]) {
                case 'I': return validateShuffleSplit(input);
                case 'W': if (input[2] == '\0') return CMD_SW;
                          else return CMD_INVALID;
                case 'R': if (input[2] == '\0') return CMD_SR;
                          else return CMD_INVALID;
                case 'D': if (input[2] =='\0') return CMD_SD;
                          else return CMD_INVALID;
                default: return CMD_INVALID;
            }
        case 'Q': if (input[1] == '\0') return CMD_Q;
                  if (input[1] == 'Q' && input[2] == '\0') return CMD_QQ;
                  else return CMD_INVALID;
        case 'P': if (input[1] =='\0') return CMD_P;
                  else return CMD_INVALID;
        default: return CMD_INVALID;
    }
}

Command validateLoadFile(char * input) {

    // first two must be LD
    if (input[0] != 'L' ||
            input[1] != 'D') {
        return CMD_INVALID;
    }

    // return if done
    if (input[2] == '\0') {
        return CMD_LD;
    }

    // must be space
    if (input[2] != ' ') {
        return CMD_INVALID;
    }

    // file names can't contain '/'
    for (int i = 0 ; input[i] != '\0' ; i++) {
        if (input[i] == '/') {
            return CMD_INVALID;
        }
    }

    int i = 0;
    while (input[i] != '\0') {
        i++;
    }

    // must end on .txt
    if (input[i-4] != '.' ||
            input[i-3] != 't' ||
            input[i-2] != 'x' ||
            input[i-1] != 't') {
        return CMD_INVALID;
    }

    return CMD_LD_FILENAME;
}

Command validateShuffleSplit(char * input) {

    // start with SI
    if (input[0] != 'S' ||
            input[1] != 'I') {
        return CMD_INVALID;
    }

    if (input[2] == '\0') {
        return CMD_SI;
    }

    // must be space
    if (input[2] != ' ') {
        return CMD_INVALID;
    }

    // must be a number
    if (!(input[3] >= '0' &&
            input[3] <= '9')) {
        return CMD_INVALID;
    }

    // return if done
    if (input[4] == '\0') {
        return CMD_SI_SPLIT;
    }

    // must be number
    if (!(input[4] >= '0' &&
            input[4] <= '9')) {
        return CMD_INVALID;
    }

    // must be less than 52
    int inputNumber = (input[3] - '0')*10 + (input[4] - '0');
    if (inputNumber >= rankSize * suitSize) {
        return CMD_INVALID;
    }

    // return if done
    if (input[5] == '\0') {
        return CMD_SI_SPLIT;
    }

    return CMD_INVALID;
}

Command validateMove(char * input) {
    // validate CX
    if ( input[0] != 'C' && input[0] != 'F') {
        return CMD_INVALID;
    }
    if (input[0] == 'C' &&
            !(input[1] >= '1' &&
            input[1] <= '7')) {
        return CMD_INVALID;
        } else if (input[0] == 'F' &&
                !(input[1] >= '1' &&
                input[1] <= '4')) {
            return CMD_INVALID;
        }

    int offset = 0;

    // validate :RS
    if (input[2] == ':') {
            offset = 3;
        if(!isRank(input[3]) ||
              !isSuit(input[4])) {
            return CMD_INVALID;
           }
    }

    // validate ->
    if (input[2+offset] != '-' &&
        input[3+offset] != '>') {
        return CMD_INVALID;
        }

    // edgecase can't move F to F
    if (input[0] == 'F' &&
            input[4+offset] == 'F') {
        return CMD_INVALID;
        }
    // validate CX
    if (input[4+offset] != 'C' &&
            input[4+offset] != 'F') {
        return CMD_INVALID;
    }
    if (input[4+offset] == 'C' &&
            !(input[5+offset] >= '1' &&
            input[5+offset] <= '7')) {
        return CMD_INVALID;
    } else if (input[4+offset] == 'F' &&
            !(input[5+offset] >= '1' &&
            input[5+offset] <= '4')) {
        return CMD_INVALID;
    }

    // edgecase can't move to and from the same column
    if (input[0] == 'C' &&
            input[4+offset] == 'C' &&
            input[1] == input[5+offset]) {
        return CMD_INVALID;
    }

    if (input[6+offset] != '\0') {
        return CMD_INVALID;
    }

    return CMD_MOVE;
}

int isRank(char input) {
    switch (input) {
        case 'A':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case 'T':
        case 'J':
        case 'Q':
        case 'K':
            return 1;
        default:
            return 0;
    }
}

int isSuit(char input) {
    switch (input) {
        case 'C':
        case 'D':
        case 'H':
        case 'S':
            return 1;
        default:
            return 0;
    }
}

void toUpperCase(char * input) {

    for (int i = 0 ; input[i] != '\0' ; i++) {
        if (input[i] >= 'a' &&
                input[i] <= 'z') {
            input[i] = (char) input[i] - 32; // set to upperCase
        }

        // edgecase for LD_Input
        if (i >= 2 &&
                input[0] == 'L' &&
                input[1] == 'D') {
            break;
        }

    }
}