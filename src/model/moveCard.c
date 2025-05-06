#include "moveCard.h"
#include "generateCards.h"
#include "../../main.h"
#include "../controller/gameController.h"
#include "validateInput.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Possible valid inputs ... C1-C7 & F1-F4
// C = Column, F = Foundation, R = Rank, S = Suit
//-----------------------------------------------
//   CX:RS->CX
//   CX:RS->FX      command doesn't make sense
//   CX->CX
//   CX->FX
//   FX->CX
//-----------------------------------------------

/** Returns 1 on success, 0 on invalid move and -1 on error */
int moveCard(char * input) {
    if (input == NULL) {
        setBoardErrorMessage(__LINE__,__FILE_NAME__);
        return -1;
    }

    char startType = input[0];
    int startPos = input[1]-'0'-1;
    char endType;
    int endPos;
    DualPointer dualStartPointer;

    //  start can't be empty - guard clause
    if (startType == 'C'&&
            columnHeader[startPos] == NULL ||
            startType == 'F'&&
            foundationHeader[startPos] == NULL) {
        setBoardMessage("Start column can't be empty.");
        specificError = 1;
        return 0;
    }

    // find startPoint
    if (input[2] == ':') {
        endType = input[7];
        endPos = input[8]-'0'-1;
        Rank searchRank = strToRank(input[3]);
        Suit searchSuit = strToSuit(input[4]);
        if (searchRank == NOT_RANK ||
                searchSuit == NOT_SUIT) {
            setBoardErrorMessage(__LINE__,__FILE_NAME__);
            return -1;
        }
        if (endType == 'C') {
            dualStartPointer = searchColumn(columnHeader[startPos], searchRank, searchSuit);
        } else if (endType == 'F') {
            dualStartPointer = retColEndDual(columnHeader[startPos]);
        } else {
            setBoardErrorMessage(__LINE__,__FILE_NAME__);
            return -1;
        }
    } else if (input[2] == '-') {
        endType = input[4];
        endPos = input[5]-'0'-1;

            // look in columnHeader or foundationHeader
            if (startType == 'C') {
                dualStartPointer = retColEndDual(columnHeader[startPos]);
            } else if (startType == 'F') {
                dualStartPointer = retColEndDual(foundationHeader[startPos]);
            } else {
                setBoardErrorMessage(__LINE__,__FILE_NAME__);
                return -1;
            }
    } else {
        setBoardErrorMessage(__LINE__,__FILE_NAME__);
        return -1;
    }

    Card * startPoint = dualStartPointer.current;       // move card from
    Card * startPointPrev = dualStartPointer.previous;  // card above startPoint
    Card * endPoint;                                    // move card to

    // find endpoint
    int emptyEndPointFlag = 0;
    if (endType == 'C') {
        if (columnHeader[endPos] == NULL) { emptyEndPointFlag = 1; }
        emptyEndPointFlag? : (endPoint = retColEndDual(columnHeader[endPos]).current);
    } else if (endType == 'F') {
        if (foundationHeader[endPos] == NULL) { emptyEndPointFlag = 1; }
        emptyEndPointFlag? : (endPoint = retColEndDual(foundationHeader[endPos]).current);
    } else {
        setBoardErrorMessage(__LINE__,__FILE_NAME__);
        return -1;
    }

    // can't start and end in same column/foundation
    if (startType == endType &&
            startPos == endPos) {
        return 0;
    }

    // faulty input guard clause
    if (!emptyEndPointFlag &&
            (startPoint == NULL ||
            startPointPrev == NULL ||
            endPoint == NULL)) {
        setBoardErrorMessage(__LINE__,__FILE_NAME__);
        return -1;
    }

    // invalid move guard clause
    if (!emptyEndPointFlag &&
            endType == 'C' &&
            startPoint->rank != endPoint->rank - 1 &&
            startPoint->suit == endPoint->suit) {
        setBoardMessage("Move breaks rules!");
        return 0;
    } else if (!emptyEndPointFlag &&
            endType == 'F' &&
            startPoint->rank != endPoint->rank + 1 &&
            startPoint->suit != endPoint->suit) {
        setBoardMessage("Move breaks rules!");
        return 0;
    }

    // detach from start column
    if (startPoint != startPointPrev) {
        startPointPrev->visibility = SHOWN;
        startPointPrev->next = NULL;
    } else if (startType == 'C') {
        columnHeader[startPos] = NULL;
    } else if (startType == 'F') {
        foundationHeader[startPos] = NULL;
    }

    // attach to end column
    if (!emptyEndPointFlag) {
        endPoint->next = startPoint;
    } else if (endType == 'C' &&          // King moves to empty
               startPoint->rank == KING) {
        columnHeader[endPos] = startPoint;
    } else if (endType == 'F' &&          // Ace moves to empty
               startPoint->rank == ACE) {
        foundationHeader[endPos] = startPoint;
    }

    return 1;
}

/** Can return a DualPointer containing NULLs */
DualPointer retColEndDual(Card * columnHeader) {

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

Card * retColEnd(Card * columnHeader) {
    Card * current  = columnHeader;
    DualPointer dualPointer = {NULL,NULL};

    while (current->next != NULL) {
        current = current->next;
    }
    return current;
}

/** Can return a DualPointer containing NULL */
DualPointer searchColumn(Card * searchHeader, Rank searchRank, Suit searchSuit) {
    Card * previous = searchHeader;
    Card * current  = searchHeader;
    DualPointer dualPointer = {NULL,NULL};

    while (current != NULL) {
        if (current->suit == searchSuit &&  current->rank == searchRank) {
            dualPointer.previous = previous;
            dualPointer.current = current;
            return dualPointer;
        }
        previous = current;
        current = current->next;
    }
    return dualPointer;
}

Rank strToRank(char input) {
    switch (input) {
        case 'A': return ACE;
        case '2': return TWO;
        case '3': return THREE;
        case '4': return FOUR;
        case '5': return FIVE;
        case '6': return SIX;
        case '7': return SEVEN;
        case '8': return EIGHT;
        case '9': return NINE;
        case 'T': return TEN;
        case 'J': return JACK;
        case 'Q': return QUEEN;
        case 'K': return KING;
        default: return NOT_RANK;
    }
}

Suit strToSuit(char input) {
    switch (input) {
        case 'C': return CLUBS;
        case 'D': return DIAMONDS;
        case 'H': return HEARTS;
        case 'S': return SPADES;
        default: return NOT_SUIT;
    }
}

