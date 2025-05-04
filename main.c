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
#include <string.h>
#include <time.h>
#include "printBoard.h"
#include "validateInput.h"


int debug = 1;
int convertLowerCaseInput = 1;
void testPrintDeck(Card * deckHeader);
void testPrintBoard();
void testShuffleDeck();
void testLoadSave();
void testFillBoard();
void testChainDelete();
void testClearBoard();
void testMoveCard();
void testValidateInput();
void testHelper(char * cmd);
void countCards();

// Initialize empty board
Card * columnHeader[] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL};
Card * foundationHeader[] = {NULL,NULL,NULL,NULL};

// Game variables



// TODO test save/load
//      test shuffle
//      implement printBoard()
//      test printBoard()
//      implement startUpPhase
//      implement playPhase
//      test game
//      commands write into boardCommands

int main(void) {






    // ---------TESTS------------
    // testPrintDeck(deckHeader);
    // testPrintBoard();
    // testShuffleDeck();
    // testLoadSave()
    // testFillBoard();
    // testChainDelete();
    // testClearBoard();
    // testMoveCard();
    // testValidateInput();


    //   TEST PRINT BOARD
    // printf("BOARD START HERE\n");
    // print_empty_board();

    // srand(time(NULL));

    return 0;
}


// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------
// -------------------  TESTS  ----------------------------------------------------------------
// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------

void testPrintDeck(Card * deck) {
    Card * current = deck;
    printf("\nDeck:\n");
    for (int i = 0; current != NULL ; i++) {
        if (i <= 52) {
            printf("%d: ",i+1);
        }
        printf("%s",rankName[current->rank]);
        printf("%s",suitName[current->suit]);
        printf("  %s\n",hiddenName[current->visibility]);
        current = current->next;
    }
}

void countCards(Card * deck) {
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
        printf("\n%s%d:","Column ",i+1);

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
        printf("\nFoundation %d:",i+1);
        while (currentCard != NULL) {
            printf("  ");
            printf("%s",rankName[currentCard->rank]);
            printf("%s",suitName[currentCard->suit]);
            //printf(" %d",currentCard->visibility);

            currentCard = currentCard->next;
        }
    }

}

void testShuffleDeck() {
    // TEST - display content of shuffled linked-list
    Card *splitDeck = generateCards();
    Card *randomDeck = generateCards();
    splitDeck = splitShuffle(splitDeck, 26);
    randomDeck = randomShuffle(randomDeck);
    printf("Split shuffle deck: \n");
    testPrintDeck(splitDeck);
    printf("Random shuffle deck: \n");
    testPrintDeck(randomDeck);
}

void testLoadSave() {
    // TEST - save/load function
    Card * deckHeader = generateCards();
    saveCards(deckHeader, "test.txt");
    saveCards(deckHeader,NULL);
    loadCards("notReal.txt");
}

void testFillBoard() {
    Card * deckHeader = generateCards();
    fillBoard(deckHeader);
    fillBoard(deckHeader);
    testPrintBoard();
    testPrintDeck(deckHeader);
}

void testChainDelete() {
    Card * deckHeader = generateCards();
    chainDelete(deckHeader);
    deckHeader = NULL;      // prevents unintended use
    printf("\nDeck should be empty:");
    testPrintDeck(deckHeader);
}

void testClearBoard() {
    for (int i = 0; i < 7; i++) {
        columnHeader[i] = generateCards();
    }
    for (int i = 0; i < 4; i++) {
        foundationHeader[i] = generateCards();
    }
    clearBoard();
    testPrintBoard();
}

void testMoveCard(){
    // initialization
    Card * deckHeader = loadCards("test.txt");
    fillBoard(deckHeader);
    testPrintBoard();


    moveCard("C5:3H->C4");
    testPrintBoard();

    // cleanup
    clearBoard();
}

void testValidateInput() {
    char Arr1[] = "C1:kH->C4";
    char * cmd1 = Arr1;

    testHelper(cmd1);
    testHelper("C0:KH->C1");
    testHelper("C8:KH->C1");
    testHelper("C1:0H->C1");
    testHelper("C1:AD->F4");
    testHelper("C1->C7");
    testHelper("C0->C7");
    testHelper("CA->C1");
    testHelper("C1->F1");
    testHelper("F1->C1");
    testHelper("C1->C1");
    testHelper("F1->F1");
    testHelper("LD");
    testHelper("LD ");
    testHelper("LD  ");
    testHelper("LD  /");
    testHelper("LD test.txt");
    testHelper("LD te/st.txt");
    testHelper("LD test");
    testHelper("SW");
    testHelper("SW ");
    testHelper("SI 25");
    testHelper("SI 52");
    testHelper("SI");
    testHelper("SI ");
    testHelper("SI 0");
    testHelper("SR");
    testHelper("SR ");
    testHelper("SD");
    testHelper("SD ");
    testHelper("Q");
    testHelper("Q ");
    testHelper("QQ");
    testHelper("QQ ");
    testHelper("P");
    testHelper("P ");
}

void testHelper(char * cmd) {
    Command output = validateInput(cmd);
    printf("\n%-12s = %s",cmd,toCommandName[output]);
}