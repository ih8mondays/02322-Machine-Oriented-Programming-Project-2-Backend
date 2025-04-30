#include "main.h"
#include "generateCards.h"
#include "shuffleDeck.h"
#include "fillBoard.h"
#include "saveCards.h"
#include "loadCards.h"
#include "moveCard.h"
#include "validateInput.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "printBoard.h"


// Initialize empty board
Card * columnHeader[] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL};
Card * foundationHeader[] = {NULL,NULL,NULL,NULL};

int debug = 1;
void testPrintDeck(Card * deckHeader);
void testPrintBoard();
void countCards();

    // __FILE__
    // __LINE__
    // sprintf();

int main(void) {
    srand(time(NULL));

    // Set up 52 cards in a linked list
    Card * deckHeader = loadCards("test.txt");
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

    //loadCards("notReal.txt");


    // Shuffle
    // TEST - display content of shuffled linked-list
    /*Card *splitDeck = generateCards();
    Card *randomDeck = generateCards();
    splitDeck = splitShuffle(splitDeck, 26);
    randomDeck = randomShuffle(randomDeck);
    printf("Split shuffle deck: \n");
    testPrintDeck(splitDeck);
    printf("Random shuffle deck: \n");
    testPrintDeck(randomDeck);*/


    fillBoard(deckHeader, columnHeader);

    // TEST - display content of columns
    testPrintBoard();

    char testArray1[] = "C1:AC->F1";
    // char testArray2[] = "C2:2C->F1";  // this should fail and return -2
    char * testCommand = &testArray1[0];

    if (validateInput(testArray1)) {
        printf("\n\nmoveCard = %d\n",moveCard(testCommand));
    } else {
        !debug? : printf("\n\nInputvalidation failed\n");
    }

    // testPrintBoard();

    // testCommand = &testArray2[0];
    // printf("\n\nmoveCard = %d\n",moveCard(testCommand));
    // testPrintBoard();

    // TEST PRINT BOARD
    printf("BOARD START HERE\n");
    print_empty_board();

    return 0;
}


void testPrintDeck(Card * deck) {
    Card *test = deck;
    for (int i = 0; i < 52 && test != NULL ; i++) {
        printf("%s",rankName[test->rank]);
        printf("%s",suitName[test->suit]);
        printf("  %s\n",hiddenName[test->visibility]);
        test = test->next;
    }
}

void countCards(Card *deck) {
    int count = 0;
    while (deck != NULL) {
        count++;
        deck = deck->next;
    }
    printf("amount of cards in deck: %d\n",count);
}

void testPrintBoard() {
    for (int i = 0; i < 7; i++) {
        Card * currentCard = columnHeader[i];
        printf("\n%s%d","Column: ",i+1);

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
        printf("\n%s%d","Foundation: ",i+1);
        while (currentCard != NULL) {
            printf("  ");
            printf("%s",rankName[currentCard->rank]);
            printf("%s",suitName[currentCard->suit]);
            //printf(" %d",currentCard->visibility);

            currentCard = currentCard->next;
        }
    }

}