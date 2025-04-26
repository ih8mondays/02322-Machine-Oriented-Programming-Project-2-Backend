#include "main.h"
#include "generateCards.h"
#include "fillBoard.h"
#include "saveCards.h"
#include "loadCards.h"
#include "moveCard.h"
#include <stdio.h>
#include <stdlib.h>

// Initialize empty board
Card * columnHeader[] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL};
Card * foundationHeader[] = {NULL,NULL,NULL,NULL};

int debug = 1;
void testPrintDeck(Card * deckHeader);
void testPrintBoard();

    // __FILE__
    // __LINE__
    // sprintf();

int main(void) {

    // Set up 52 cards in a linked list
    Card * deckHeader = generateCards();
    if (deckHeader == NULL) {
        perror("Error in generateCards\n");
        free(deckHeader);
        return -1;
    }

    // TEST - display content of linked-list
    testPrintDeck(deckHeader);

    // TEST - save/load function
    saveCards(deckHeader, "test.txt");
    saveCards(deckHeader,NULL);
    loadCards("test.txt");
    //loadCards("notReal.txt");


    // Shuffle
    //
    //

    fillBoard(deckHeader, columnHeader);

    // TEST - display content of columns
    testPrintBoard();

    char testArray1[] = "C1:AC->F1";
    // char testArray2[] = "C2:2C->F1";  // this should fail and return -2
    char * testCommand = &testArray1[0];

    printf("\n\nmoveCard = %d\n",moveCard(testCommand));
    testPrintBoard();

    // testCommand = &testArray2[0];
    // printf("\n\nmoveCard = %d\n",moveCard(testCommand));
    // testPrintBoard();


    return 0;
}


void testPrintDeck(Card * deckHeader) {
    Card *test = deckHeader;
    for (int i = 0; i < 52 && test != NULL ; i++) {
        printf("%s",rankName[test->rank]);
        printf("%s",suitName[test->suit]);
        printf("  %s\n",hiddenName[test->visibility]);
        test = test->next;
    }
}


void testPrintBoard() {
    for (int i = 0; i < 7; i++) {
        Card * currentCard = columnHeader[i];
        printf("\n%s%d","Column ",i+1);

        while (currentCard != NULL) {
            printf("  ");
            printf("%s",rankName[currentCard->rank]);
            printf("%s",suitName[currentCard->suit]);
            printf(" %d",currentCard->visibility);

            currentCard = currentCard->next;
        }
    }

    printf("\n");

    for (int i = 0; i < 4; i++) {
        Card * currentCard = foundationHeader[i];
        printf("\n%s%d","Foundation ",i+1);
        while (currentCard != NULL) {
            printf("  ");
            printf("%s",rankName[currentCard->rank]);
            printf("%s",suitName[currentCard->suit]);
            //printf(" %d",currentCard->visibility);

            currentCard = currentCard->next;
        }
    }

}