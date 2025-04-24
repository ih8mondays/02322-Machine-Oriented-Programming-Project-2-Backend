#include "main.h"
#include "generateCards.h"
#include "fillBoard.h"
#include "saveCards.h"
#include "loadCards.h"
#include <stdio.h>
#include <stdlib.h>

Card * columnHeader[] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL};
Card * foundationHeader[] = {NULL,NULL,NULL,NULL};


    // __FILE__
    // __LINE__


int main(void) {

    // Initialize empty board

    // Set up 52 cards in a linked list
    Card *deckHeader = generateCards();
    if (deckHeader == NULL) {
        perror("Error in generateCards\n");
        free(deckHeader);
        return -1;
    }

    // TEST - display content of linked list
    Card *test = deckHeader;
    for (int i = 0; i < 52 && test != NULL ; i++) {
        printf("%s",rankName[test->rank]);
        printf("%s",suitName[test->suit]);
        printf("  %s\n",hiddenName[test->visibility]);
        test = test->next;
    }

    // TEST - save/load function
    saveCards(deckHeader, "test.txt");
    saveCards(deckHeader,NULL);
    loadCards("test.txt");
    //loadCards("notreal.txt");


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
            printf(" %s\n",hiddenName[currentTestHeader->visibility]);

            currentTestHeader = currentTestHeader->next;
            k++;
        }
    }


    return 0;
}





