#include "moveCard.h"
#include "generateCards.h"
#include "main.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>


bool isEqual(Card * card, Suit suit, Rank rank);
DualPointer searchColumn(Card * searchHeader, Suit searchSuit, Rank searchRank);
int columnToColumn(char * input);
int toFoundation(char * input);
int fromFoundation(char * input);

// Possible valid inputs ... C1-C7 & F1-F4
//   CX:RS->CX      colToCol
//   CX:RS->FX      toF
//   CX->CX         colToCol
//   CX->FX         toF
//   FX->CX         fromF

/** Returns 0 on success, -1 on error and -2 on invalid move */
int moveCard(char * input) {
    if (input[0] == 'C' && input[2] == ':' && input[7] == 'C'
        || input[0] == 'C' && input[2] == '-' && input[4] == 'C') {
        return columnToColumn(input);
    } else if ( input[0] == 'C' && input[2] == ':' && input[7] == 'F'
        || input[0] == 'C' && input[2] == '-' && input[4] == 'F') {
        return toFoundation(input);
    } else if (input[0] == 'F') {
        return fromFoundation(input);
    }
    return -1;
}


int columnToColumn(char * input) {
    Card * searchHeader = columnHeader[input[1]-'0'-1];
    Card * startPoint = NULL;       // move card from
    Card * startPointPrev = NULL;   // card one above startPoint
    Card * endPoint = NULL;         // move card to
    DualPointer temp = {NULL,NULL};      // used to return two pointers
    int columnNr = -1;

    // find startPoint, startPointPrev and endPoint
    if (input[2] == ':') {
        Rank searchRank = rank[input[3]-'0'-1];
        Suit searchSuit = suit[input[4]-'0'-1];
        temp = searchColumn(searchHeader, searchRank, searchSuit);
        startPoint = temp.current;
        startPointPrev = temp.previous;
        columnNr = input[8]-'0'-1;
        endPoint = returnColumnEnd(columnHeader[columnNr]).current;

    } else if (input[2] == '-') {
        Card * columnEnd = searchHeader;
        temp = returnColumnEnd(columnEnd);
        startPoint = temp.current;
        startPointPrev = temp.previous;
        columnNr = input[5]-'0'-1;
        endPoint = returnColumnEnd(columnHeader[columnNr]).current;
    }

    // NULL pointer guard clause
    if (startPoint == NULL ||
        startPointPrev == NULL ||
        endPoint == NULL)
        { return -2; }

    // Invalid move guard clause
    if (startPoint->rank != endPoint->rank - 1 &&
        startPoint->suit == endPoint->suit) {
        return -2;
    }

    // if first card in column set columnHeader to NULL
    if (startPoint == startPointPrev ) {
        endPoint->next = startPoint;
        columnHeader[columnNr] = NULL;
    } else {
        endPoint->next = startPoint;
        startPointPrev->next = NULL;
    }
    return 0;
}



int toFoundation(char *input) {


    return 0;
}

int fromFoundation(char *input) {
    return 0;
}



/** Can return a DualPointer containing NULLs */
DualPointer returnColumnEnd(Card * columnHeader) {
    Card * previous = columnHeader;
    Card * current  = columnHeader;
    DualPointer dualPointer = {NULL,NULL};

    while (current->next != NULL) {
        previous = current;
        current = current->next;
    }
    dualPointer.previous = previous;
    dualPointer.current = current;

    return dualPointer;
}

/** Can return a DualPointer containing NULL */
DualPointer searchColumn(Card * searchHeader, Suit searchSuit, Rank searchRank) {
    Card * previous = searchHeader;
    Card * current  = searchHeader;
    DualPointer dualPointer = {NULL,NULL};

    while (current != NULL) {
        if (isEqual(current, searchSuit, searchRank)) {
            dualPointer.previous = previous;
            dualPointer.current = current;
            return dualPointer;
        }
        previous = current;
        current = current->next;
    }
    return dualPointer;
}

// TODO Consider consolidation this

bool isEqual(Card * card, Suit suit, Rank rank) {
    return card->suit == suit && card->rank == rank;
}



