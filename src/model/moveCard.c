#include "moveCard.h"
#include "generateCards.h"
#include "../../main.h"
#include "../controller/gameController.h"
#include "validateInput.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


DualPointer searchColumn(Card * searchHeader, Rank searchRank, Suit searchSuit);
DualPointer retColEndDual(Card * columnHeader);

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
void moveCard(char * input) {
    if (input == NULL) {
        setBoardErrorMessage(__LINE__,__FILE_NAME__);
        return;
    }

    char startType = input[0];
    int startPos = input[1]-'0'-1;
    char endType;
    int endPos;
    DualPointer dualStartPointer;

    //  start can't be empty - guard clause
    if (startType == 'C' &&
            columnHeader[startPos] == NULL ||
            startType == 'F'&&
            foundationHeader[startPos] == NULL) {
        setBoardMessage("Start column can't be empty.");
        dontOverwriteMessage = 1;
        return;
    }

    // find startPoint
    if (input[2] == ':') {
        endType = input[7];
        endPos = input[8]-'0'-1;
        Rank searchRank = charToRank(input[3]);
        Suit searchSuit = charToSuit(input[4]);
        if (searchRank == NOT_RANK ||
                searchSuit == NOT_SUIT) {
            setBoardErrorMessage(__LINE__,__FILE_NAME__);
            return;
        }
        if (endType == 'C') {
            dualStartPointer = searchColumn(columnHeader[startPos], searchRank, searchSuit);
        } else if (endType == 'F') {
            dualStartPointer = retColEndDual(columnHeader[startPos]);
        } else {
            setBoardErrorMessage(__LINE__,__FILE_NAME__);
            return;
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
                return;
            }
    } else {
        setBoardErrorMessage(__LINE__,__FILE_NAME__);
        return;
    }

    if (dualStartPointer.current == NULL) {
        setBoardMessage("Couldn't find card.");
        dontOverwriteMessage = 1;
        return;
    }

    Card * startPoint = dualStartPointer.current;       // move card from
    Card * startPointPrev = dualStartPointer.previous;  // card above startPoint
    Card * endPoint;                                    // move card to

    // find endpoint
    int emptyEndPoint = 0;
    if (endType == 'C') {
        if (columnHeader[endPos] == NULL) { emptyEndPoint = 1; }
        emptyEndPoint? : (endPoint = retColEndDual(columnHeader[endPos]).current);
    } else if (endType == 'F') {
        if (foundationHeader[endPos] == NULL) { emptyEndPoint = 1; }
        emptyEndPoint? : (endPoint = retColEndDual(foundationHeader[endPos]).current);
    } else {
        setBoardErrorMessage(__LINE__,__FILE_NAME__);
        return;
    }

    // can't start and end in same column/foundation
    if (startType == endType &&
            startPos == endPos) {
        return;
    }

    // this should only trigger if something is wrong with the code
    if (!emptyEndPoint &&
        endPoint == NULL ||
            startPointPrev == NULL) {
        setBoardErrorMessage(__LINE__,__FILE_NAME__);
        return;
    }

    // only KING can move to empty column
    if (emptyEndPoint &&
            endType == 'C' &&
            startPoint->rank != KING) {
        setBoardMessage("Move breaks rules!");
        dontOverwriteMessage = 1;
        return;

    // only ACE can move to empty foundation
    } else if (emptyEndPoint &&
        endType == 'F' &&
        startPoint->rank != ACE) {
        setBoardMessage("Move breaks rules!");
        dontOverwriteMessage = 1;
        return;

    // handle other disallowed moves
    } else if (!emptyEndPoint &&
            endType == 'C' &&
            (startPoint->rank != endPoint->rank - 1 ||
            startPoint->suit == endPoint->suit)) {
        setBoardMessage("Move breaks rules!");
        dontOverwriteMessage = 1;
        return;
    } else if ( !emptyEndPoint &&
            endType == 'F' &&
            (startPoint->rank != endPoint->rank + 1 ||
            startPoint->suit != endPoint->suit)) {
        setBoardMessage("Move breaks rules!");
        dontOverwriteMessage = 1;
        return;
    }

    // detach from start column
    if (startPoint != startPointPrev) {
        startPointPrev->visibility = SHOWN;
        startPointPrev->next = NULL;
    // start card must be at the top of column/foundation
    } else if (startType == 'C') {
        columnHeader[startPos] = NULL;
    } else if (startType == 'F') {
        foundationHeader[startPos] = NULL;
    }

    // attach to end column
    if (!emptyEndPoint) {
        endPoint->next = startPoint;
    } else if (endType == 'C' &&          // King moves to empty
               startPoint->rank == KING) {
        columnHeader[endPos] = startPoint;
    } else if (endType == 'F' &&          // Ace moves to empty
               startPoint->rank == ACE) {
        foundationHeader[endPos] = startPoint;
    }
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
        if (current->suit == searchSuit &&
                current->rank == searchRank &&
                current->visibility == SHOWN) {
            dualPointer.previous = previous;
            dualPointer.current = current;
            return dualPointer;
        }
        previous = current;
        current = current->next;
    }
    return dualPointer;
}

Rank charToRank(char input) {
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

Suit charToSuit(char input) {
    switch (input) {
        case 'C': return CLUBS;
        case 'D': return DIAMONDS;
        case 'H': return HEARTS;
        case 'S': return SPADES;
        default: return NOT_SUIT;
    }
}

