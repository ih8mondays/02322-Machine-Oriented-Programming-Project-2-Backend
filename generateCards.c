#include "generateCards.h"
#include <stdio.h>
#include <stdlib.h>

const Rank rank[] = {ACE,TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE,TEN,JACK,QUEEN,KING};
const Suit suit[] = {CLUBS,DIAMONDS,HEARTS,SPADES};
const Hidden hidden[] = {HIDDEN,SHOWN};
const char * rankName[] = {"A","2","3","4","5","6","7","8","9","T","J","Q","K"};
const char * suitName[] = {"C","D","H","S"};
const char * hiddenName[] = {"Hidden","Shown"};

extern const int suitSize = sizeof(suit)/sizeof(suit[0]);
extern const int rankSize = sizeof(rank)/sizeof(rank[0]);


/**
 * @return Returns a linked list containing a standard unshuffled deck.
 */
Card * generateCards() {

    Card * head = (Card*)malloc(sizeof(Card));
    Card * current = head;

    if (head == NULL) {
        printf("Memory couldn't be allocated while generating cards");
        return NULL;
    }

    for (int i = 0 ; i < suitSize ; i++) {
        for (int j = 0 ; j < rankSize; j++) {

            if (current == NULL) {
                printf("Memory couldn't be allocated while generating cards");
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