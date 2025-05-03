#include "fillBoard.h"
#include "generateCards.h"
#include "main.h"
#include "moveCard.h"
#include <stdio.h>

/**
 * Fills the deck into the columns and toggles hidden/shown.
 * Afterwards the game should be ready to start.
 *
 * @param deckHeader Input deck pointers
 * @param columnHeader Input board columns pointer array.
 */
void fillBoard(Card * deckHeader, Card * columnHeader[]) {

    //TODO change return value to int

    if (deckHeader == NULL ||
            columnHeader[0] != NULL ||
            columnHeader[1] != NULL ||
            columnHeader[2] != NULL ||
            columnHeader[3] != NULL ||
            columnHeader[4] != NULL ||
            columnHeader[5] != NULL ||
            columnHeader[6] != NULL) {
        return;
    }


    Card * currentFill = deckHeader;
    currentFill->visibility = SHOWN;
    Card * columnEnd = NULL;

    // First column gets 1 card
    columnHeader[0] = currentFill;
    Card * previousFill = currentFill;
    currentFill = currentFill->next;
    previousFill->next = NULL;

    int offset = 0;

    for (int i = 0; i < 11; i++) {     // i = row
        if (i > 5) { offset++; }

        for (int j = 1 + offset; j < 7; j++) {  // j = column
            if (currentFill == NULL) {
                !debug? : printf("\nNullPointerError in row %d column %d during fillBoard()\n",i+1,j+1);
                return;
            }

            // Reveals cards as outlined by the rules
            if (i >= j) {
                currentFill->visibility = SHOWN;
            } else {
                currentFill->visibility = HIDDEN;
            }

            // Put current card in next spot
            if (i == 0) {
                columnHeader[j] = currentFill;
            } else {
                columnEnd = retColEnd(columnHeader[j]).current;
                columnEnd->next = currentFill;
            }

            // Increment to next card
            previousFill = currentFill;
            currentFill = currentFill->next;
            previousFill->next = NULL;

        }
    }

}