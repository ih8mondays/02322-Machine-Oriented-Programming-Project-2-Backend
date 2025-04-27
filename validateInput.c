#include "validateInput.h"
#include "main.h"
#include "stdio.h"
#include <stddef.h>

int isRank(char input);
int isSuit(char input);

// Possible valid inputs ... C1-C7 & F1-F4
// C = Column, F = Foundation, R = Rank, S = Suit
//-----------------------------------------------
//   CX:RS->CX
//   CX:RS->FX      command doesn't make sense
//   CX->CX
//   CX->FX
//   FX->CX
//-----------------------------------------------

// TODO set chars to UPPERCASE so C and c is accepted

/** Returns 1 , 0 or -1 */
int validateInput(char * input) {

    if (input == NULL) {
        !debug? : printf("\n\nError at line %d in moveCard.c\n",__LINE__);
        return -1;
    }

    // validate CX
    if ( input[0] != 'C' && input[0] != 'F') {
        return 0;
    }
    if (input[0] == 'C' &&
        !(input[1] >= '1' &&
        input[1] <= '7')) {
        return 0;
    } else if (input[0] == 'F' &&
        !(input[1] >= '1' &&
        input[1] <= '4')) {
        return 0;
    }

    int offset = 0;

    // validate :RS
    if (input[2] == ':') {
        offset = 3;
        if(!isRank(input[3]) ||
           !isSuit(input[4])) {
            return 0;
        }
    }

    // validate ->
    if (input[2+offset] != '-' &&
        input[3+offset] != '>') {
        return 0;
    }

    // edgecase can't move F to F
    if (input[0] == 'F' &&
        input[4+offset] == 'F') {
        return 0;
    }
    // validate CX
    if (input[4+offset] != 'C' &&
        input[4+offset] != 'F') {
        return 0;
    }
    if (input[4+offset] == 'C' &&
        !(input[5+offset] >= '1' &&
        input[5+offset] <= '7')) {
        return 0;
    } else if (input[4+offset] == 'F' &&
            !(input[5+offset] >= '1' &&
            input[5+offset] <= '4')) {
            return 0;
    }

    return 1;
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