#include "main.h"
#include "src/model/generateCards.h"
#include "src/model/shuffleDeck.h"
#include "src/model/fillBoard.h"
#include "src/model/saveCards.h"
#include "src/model/loadCards.h"
#include "src/model/moveCard.h"
#include "src/model/validateInput.h"
#include "src/controller/gameController.h"
#include "src/view/printBoard.h"
#include "src/model/validateInput.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>




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

// TODO implement gameController()   X = done
//      X   fix loadCards()
//          fix shuffleSplit()
//      X   fix saveCards()
//      test gameController()
//  ->  implement printBoard()
//      test printBoard()
//      test print_empty_board()
//      test print_hidden_board()
//      test print_shown_board()
//      test loadCards()
//      test saveCards()
//      test randomShuffle()
//      test splitShuffle()
//      commands write into boardCommands[]   X = done
//          fillBoard()
//      X   gameController()
//          generateCards()
//      X   loadCards()
//          main()
//          moveCards()
//      X   saveCards()
//          shuffleDeck()         create checks to see if you return a full deck (52 cards)


int main(void) {

    // ---------TESTS------------
    // testPrintDeck(deckHeader);
    // testPrintBoard();
    // testShuffleDeck();
    // testLoadSave();
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
            //printf(" %d",currentCard->visibility);

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
    splitDeck = splitShuffle(splitDeck, 26);
    printf("Split shuffle deck: \n");
    testPrintDeck(splitDeck);


    Card *randomDeck = generateCards();
    randomShuffle(randomDeck);
    printf("Random shuffle deck: \n");
    testPrintDeck(randomDeck);

    // cleanup
    chainDelete(deckHeader);
    deckHeader = NULL;
}

void testLoadSave() {
    // TEST - save/load function
    deckHeader = generateCards();
    saveCards(CMD_SD,NULL);
    saveCards(CMD_SD_FILENAME, "test.txt");

    loadCards("LD notReal.txt");
    loadCards("LD real.txt");
    loadCards("LD /test.txt");
}

void testFillBoard() {
    deckHeader = generateCards();
    fillBoard(deckHeader);
    fillBoard(deckHeader);
    testPrintBoard();
    testPrintDeck(deckHeader);

    // cleanup
    clearBoard();
    chainDelete(deckHeader);
    deckHeader = NULL;
}

void testChainDelete() {
    deckHeader = generateCards();
    chainDelete(deckHeader);
    deckHeader = NULL;          // prevents unintended use
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
    loadCards("test.txt");
    fillBoard(deckHeader);
    testPrintBoard();


    moveCard("C5:3H->C4");
    testPrintBoard();

    // cleanup
    clearBoard();
    chainDelete(deckHeader);
    deckHeader = NULL;
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