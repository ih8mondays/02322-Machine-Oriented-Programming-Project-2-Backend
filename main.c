#include "main.h"
#include "generateCards.h"
#include <stdio.h>
#include <stdlib.h>

const char * rankName[] = {"A","2","3","4","5","6","7","8","9","T","J","Q","K"};
const char * suitName[] = {"C","D","H","S"};
const char * hiddenName[] = {"Hidden","Shown"};

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





