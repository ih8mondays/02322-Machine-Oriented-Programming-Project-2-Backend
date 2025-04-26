#include "moveCard.h"
#include "generateCards.h"
#include "main.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


bool isEqual(Card * card, Suit suit, Rank rank);
DualPointer searchColumn(Card * searchHeader, Suit searchSuit, Rank searchRank);

// Possible valid inputs ... C1-C7 & F1-F4
// C = Column, F = Foundation, R = Rank, S = Suit
//-----------------------------------------------
//   CX:RS->CX      colToCol
//   CX:RS->FX      toF
//   CX->CX         colToCol
//   CX->FX         toF
//   FX->CX         fromF
//-----------------------------------------------

/** Returns 0 on success, -1 on error and -2 on invalid move */
int moveCard(char * input) {
    if (input == NULL) { return -1; }

    char startType = input[0];
    int startPos = input[1]-'0'-1;
    char endType;
    int endPos;
    DualPointer dualStartPointer;

    // find startPoint
    if (input[2] == ':') {
        endType = input[7];
        endPos = input[8]-'0'-1;
        Rank searchRank = rank[input[3]-'0'-1];
        Suit searchSuit = suit[input[4]-'0'-1];
        dualStartPointer = searchColumn(columnHeader[startPos], searchRank, searchSuit);
    } else if (input[2] == '-') {
        endType = input[4];
        endPos = input[5]-'0'-1;

            // look in columnHeader or foundationHeader
            if (startType == 'C') {
                dualStartPointer = retColEnd(columnHeader[startPos]);
            } else if (startType == 'F') {
                dualStartPointer = retColEnd(foundationHeader[startPos]);
            } else {
                return -1;
            }
    } else {
        return -1;
    }

    Card * startPoint = dualStartPointer.current;       // move card from
    Card * startPointPrev = dualStartPointer.previous;  // card above startPoint
    Card * endPoint;                                    // move card to

    // find endpoint
    if (endType == 'C') {
        endPoint = retColEnd(columnHeader[endPos]).current;
    } else if (endType == 'F') {
        endPoint = retColEnd(foundationHeader[endPos]).current;
    } else {
        return -1;
    }

    // faulty input guard clause
    if (startPoint == NULL ||
        startPointPrev == NULL ||
        endPoint == NULL ||
        startPos < 0 ||
        startPos > 6) {
        //printf("Invalid input given to columnToColumn() in %s\n",__FILE__);
        return -1;
        }

    // invalid move guard clause
    if (endType == 'C' &&
        startPoint->rank != endPoint->rank - 1 &&
        startPoint->suit == endPoint->suit) {
        return -2;
    }
    if (endType == 'F' &&
        startPoint->rank != endPoint->rank + 1 &&
        startPoint->suit != endPoint->suit) {
        return -2;
    }

    // detach from start column
    if (startPoint != startPointPrev) {
        startPointPrev->next = NULL;
    } else if (startType == 'C') {
        columnHeader[startPos] = NULL;
    } else if (startType == 'F') {
        foundationHeader[startPos] = NULL;
    }

    // attach to end column
    endPoint->next = startPoint;

    return 0;
}

/** Can return a DualPointer containing NULLs */
DualPointer retColEnd(Card * columnHeader) {
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

// TODO consolidate this?
bool isEqual(Card * card, Suit suit, Rank rank) {
    return card->suit == suit && card->rank == rank;
}



