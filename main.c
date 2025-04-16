#include "generateCards.h"
#include "fillBoard.h"
#include "saveCards.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {

    // Initialize empty board
    Card * columnHeader[7] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL};
    Card * foundationHeader[4] = {NULL,NULL,NULL,NULL};

    // Set up 52 cards in a linked list
    Card *deckHeader = generateCards();
    if (deckHeader == NULL) {
        free(deckHeader);
        printf("Error in generateCards\n");
        return -1;
    }

    // TEST - display content of linked list
    Card *test = deckHeader;
    for (int i = 0; i < 52 && test != NULL ; i++) {
        printf("%s",rankName[test->rank]);
        printf("%s",suitName[test->suit]);
        printf("  %s\n",hiddenName[test->hidden]);
        test = test->next;
    }

    // TEST - save function
    saveCards(deckHeader);


    // Shuffle
    //
    //
    //
    //
    //
    //
    //
    //


    fillBoard(deckHeader, columnHeader);

    // TEST - display content of columns
    printf("\n");
    for (int i = 0; i < 7; i++) {
        Card * currentTestHeader = columnHeader[i];
        printf("%s%d\n","Column ",i+1);
        int k = 0;
        while (currentTestHeader != NULL) {
            printf("%s","  ");
            printf("%s",rankName[currentTestHeader->rank]);
            printf("%s",suitName[currentTestHeader->suit]);
            printf(" %s\n",hiddenName[currentTestHeader->hidden]);

            currentTestHeader = currentTestHeader->next;
            k++;
        }
    }


    return 0;
}





