#include "main.h"
#include <stdio.h>
#include <stdlib.h>

const Rank rank[] = {ACE,TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE,TEN,JACK,QUEEN,KING};
const Suit suit[] = {CLUBS,DIAMONDS,HEARTS,SPADES};
const Hidden hidden[] = {HIDDEN,SHOWN};

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

Card * generateCards() {
    const int suitSize = sizeof(suit)/sizeof(suit[0]);
    const int rankSize = sizeof(rank)/sizeof(rank[0]);

    Card *head = (Card*)malloc(sizeof(Card));
    Card *current = head;

    if (head == NULL) {
        printf("Memory couldn't be allocated");
        return NULL;
    }

    for (int i = 0 ; i < suitSize ; i++) {
        for (int j = 0 ; j < rankSize; j++) {

            if (current == NULL) {
                printf("Memory couldn't be allocated");
                free(head);
                return NULL;
            }

            // Assign current card values
            current->suit = suit[i];
            current->rank = rank[j];
            current->hidden = HIDDEN;

            // Last card won't allocate more memory

            if (i == suitSize - 1 && j == rankSize - 1) {
                current->next = NULL;
                return head;
            }
            // Set up next card
            current->next = malloc(sizeof(Card));
            current = current->next;
        }
    }

    return head;
}




// FillS deck into board
void fillBoard(Card * deckHeader, Card * columnHeader[]) {

    // First column gets 1 card
    Card * currentFill = deckHeader;
    Card * columnEnd = NULL;

    columnHeader[0] = currentFill;
    Card * previousFill = currentFill;
    currentFill = currentFill->next;
    previousFill->next = NULL;

    for (int i = 0; i < 11; i++) {     // row
        for (int j = 1; j < 7; j++) {  // column

            if (i > 5) { j = i - 4; }

            if (i == 0) {
                columnHeader[j] = currentFill;
            } else {
                columnEnd = columnHeader[j];
                while (columnEnd->next != NULL) { columnEnd = columnEnd->next; }
                columnEnd->next = currentFill;
            }

            previousFill = currentFill;
            if (currentFill->next == NULL) {
                printf("NullPointerError in row %d column %d during fillBoard()\n",i,j);
            }
            currentFill = currentFill->next;
            previousFill->next = NULL;

        }
    }

}

