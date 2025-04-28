#include <stdio.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "shuffleDeck.h"
/*
 *
 *
 **/


Card *shuffleDeck(Card *passedDeck) {
    Card *shuffledDeck = NULL;
    Card *currentCard = passedDeck;
    int max_position = 0;

    while (currentCard != NULL) {
        Card *nextCard = currentCard->next;
        currentCard->next = NULL; // detach card from passedDeck

        int pick = rand() % (max_position + 1); // picks random number between 0-max_position
        insert_at_random(&shuffledDeck, currentCard, pick);
        max_position++;
        currentCard = nextCard;
    }
    return shuffledDeck;
}

/**
* Inserts the passed card and the randomized pick location in a linked list
*/
Card *insert_at_random(Card **head, Card *card_to_insert, int pick) {

    if (pick == 0 || *head == NULL) {
        card_to_insert->next = *head;
        *head = card_to_insert;
        return *head;
    }
    Card *temp = *head;
    for (int i = 1; i < pick && temp->next != NULL; i++) {
        temp = temp->next; //travers
    }
    card_to_insert->next = temp->next;
    temp->next = card_to_insert;

    return *head;
}

