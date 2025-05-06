#include "fillBoard.h"
#include "generateCards.h"
#include "../../main.h"
#include "moveCard.h"
#include "../controller/gameController.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Copies the deck into the columns and toggles hidden/shown.
 * Afterwards the game should be ready to start.
 */
void fillBoard(){

    if (deckHeader == NULL) {
        setBoardMessage("Can't play without cards.");
        return;
    }

    // empty board before filling it
    clearBoard();

    // Create a copy of the first card
    Card * currentFill = deckHeader;
    Card * currentCopy = (Card*)malloc(sizeof(Card));
    currentCopy->rank = currentFill->rank;
    currentCopy->suit = currentFill->suit;
    currentCopy->visibility = SHOWN;
    currentCopy->next = NULL;


    // First column gets 1 card
    columnHeader[0] = currentCopy;
    Card * previousFill = currentFill;
    Card * previousCopy = currentCopy;
    currentFill = currentFill->next;
    Card * columnEnd = NULL;

    int offset = 0;

    for (int i = 0; i < 11; i++) {     // i = row
        if (i > 5) { offset++; }

        for (int j = 1 + offset; j < 7; j++) {  // j = column
            if (currentFill == NULL) {
                !yukonDebugMode? : memset(boardMessage, '\0', sizeof(boardMessage));
                !yukonDebugMode? : snprintf(boardMessage,sizeof(boardMessage),"NullPointerError in row %d column %d in ",i+1,j+1,__FILE_NAME__);
                clearBoard();
                specificError = 1;
                return;
            }

            // Create cardCopy to fill onto board
            currentCopy = (Card*)malloc(sizeof(Card));
            currentCopy->rank = currentFill->rank;
            currentCopy->suit = currentFill->suit;
            currentCopy->next = NULL;

            // Reveals cardCopy as outlined by the rules
            if (i >= j) {
                currentCopy->visibility = SHOWN;
            } else {
                currentCopy->visibility = HIDDEN;
            }

            // Place currentCopy on board
            if (i == 0) {
                columnHeader[j] = currentCopy;
            } else {
                columnEnd = retColEndDual(columnHeader[j]).current;
                if (columnEnd != NULL) {
                    columnEnd->next = currentCopy;
                } else {
                    setBoardErrorMessage(__LINE__,__FILE_NAME__);
                }
            }

            // Increment to next card
            previousFill = currentFill;
            currentFill = currentFill->next;
        }
    }
}