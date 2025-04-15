#include "fillBoard.h"
#include "generateCards.h"
#include <stdio.h>


/**
 * Fills the deck into the columns and toggles hidden.
 * Afterwards the game should be ready to start.
 *
 * @param deckHeader Input deck pointers
 * @param columnHeader Input board columns pointer array.
 */
void fillBoard(Card * deckHeader, Card * columnHeader[]) {

    Card * currentFill = deckHeader;
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

            // Reveals cards as outlined by the rules
            if (i >= j) {
                currentFill->hidden = SHOWN;
            }

            // Put current card in the next spot
            if (i == 0) {
                columnHeader[j] = currentFill;
            } else {
                columnEnd = columnHeader[j];
                while (columnEnd->next != NULL) { columnEnd = columnEnd->next; }
                columnEnd->next = currentFill;
            }

            // Increment to next card
            previousFill = currentFill;
            if (currentFill->next == NULL) {
                printf("NullPointerError in row %d column %d during fillBoard()\n",i+1,j+1);
            }
            currentFill = currentFill->next;
            previousFill->next = NULL;

        }
    }

}