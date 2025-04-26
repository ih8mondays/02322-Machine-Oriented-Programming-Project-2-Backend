#include "moveCard.h"
#include "generateCards.h"
#include "main.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

// Possible valid inputs ... C1-C7 & F1-F4
// C = Column, F = Foundation, R = Rank, S = Suit
//-----------------------------------------------
//   CX:RS->CX
//   CX:RS->FX
//   CX->CX
//   CX->FX
//   FX->CX
//-----------------------------------------------

/** Returns 0 on success, -1 on error and -2 on invalid move */
int moveCard(char * input) {
    if (input == NULL) {
        !debug? :printf("\n\nError at line %d in moveCard.c\n",__LINE__);
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
        return -2;
    }

    // find startPoint
    if (input[2] == ':') {
        endType = input[7];
        endPos = input[8]-'0'-1;
        Rank searchRank;
        switch (input[3]) {
            case 'A': searchRank = ACE;     break;
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9': searchRank = input[3]-'0'-1;    break;
            case 'T': searchRank = TEN;     break;
            case 'J': searchRank = JACK;    break;
            case 'Q': searchRank = QUEEN;   break;
            case 'K': searchRank = KING;    break;
            default:
                !debug? :printf("\n\nError at line %d in moveCard.c\n",__LINE__);
                return -1;
        }
        Suit searchSuit;
        switch (input[4]) {
            case 'C': searchSuit = CLUBS;       break;
            case 'D': searchSuit = DIAMONDS;    break;
            case 'H': searchSuit = HEARTS;      break;
            case 'S': searchSuit = SPADES;      break;
            default:
                !debug? :printf("\n\nError at line %d in moveCard.c\n",__LINE__);
                return -1;
        }
        if (endType == 'C') {
            dualStartPointer = searchColumn(columnHeader[startPos], searchRank, searchSuit);
        } else if (endType == 'F') {
            dualStartPointer = retColEnd(columnHeader[startPos]);
        } else {
            !debug? :printf("\n\nError at line %d in moveCard.c\n",__LINE__);
            return -1;
        }
    } else if (input[2] == '-') {
        endType = input[4];
        endPos = input[5]-'0'-1;

            // look in columnHeader or foundationHeader
            if (startType == 'C') {
                dualStartPointer = retColEnd(columnHeader[startPos]);
            } else if (startType == 'F') {
                dualStartPointer = retColEnd(foundationHeader[startPos]);
            } else {
                !debug? :printf("\n\nError at line %d in moveCard.c\n",__LINE__);
                return -1;
            }
    } else {
        !debug? :printf("\n\nError at line %d in moveCard.c\n",__LINE__);
        return -1;
    }

    Card * startPoint = dualStartPointer.current;       // move card from
    Card * startPointPrev = dualStartPointer.previous;  // card above startPoint
    Card * endPoint;                                    // move card to

    // find endpoint
    int emptyEndPointFlag = 0;
    if (endType == 'C') {
        if (columnHeader[endPos] == NULL) { emptyEndPointFlag = 1; }
        emptyEndPointFlag? : (endPoint = retColEnd(columnHeader[endPos]).current);
    } else if (endType == 'F') {
        if (foundationHeader[endPos] == NULL) { emptyEndPointFlag = 1; }
        emptyEndPointFlag? : (endPoint = retColEnd(foundationHeader[endPos]).current);
    } else {
        !debug? : printf("\n\nError at line %d in moveCard.c\n",__LINE__);
        return -1;
    }

    // faulty input guard clause
    if (!emptyEndPointFlag &&
        (startPoint == NULL ||
        startPointPrev == NULL ||
        endPoint == NULL)) {
        !debug? : printf("\n\nError at line %d in moveCard.c",__LINE__);
        return -1;
        }

    // invalid move guard clause
    if (!emptyEndPointFlag &&
        endType == 'C' &&
        startPoint->rank != endPoint->rank - 1 &&
        startPoint->suit == endPoint->suit) {
            return -2;
    } else if (!emptyEndPointFlag &&
        endType == 'F' &&
        startPoint->rank != endPoint->rank + 1 &&
        startPoint->suit != endPoint->suit) {
            return -2;
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
    } else if (emptyEndPointFlag &&       // King moves to empty
               endType == 'C' &&
               startPoint->rank == KING) {
        columnHeader[endPos] = startPoint;
    } else if (emptyEndPointFlag &&       // Ace moves to empty
               endType == 'F' &&
               startPoint->rank == ACE) {
        foundationHeader[endPos] = startPoint;
    }

    return 0;
}

/** Can return a DualPointer containing NULLs */
DualPointer retColEnd(Card * columnHeader) {
    if (columnHeader == NULL) {
        !debug? : printf("\n\nError at line %d in moveCard.c",__LINE__);
    }

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



