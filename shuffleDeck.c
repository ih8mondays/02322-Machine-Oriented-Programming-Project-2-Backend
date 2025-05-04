#include <stdio.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "shuffleDeck.h"

// Helper functions
Card *shuffle_at_random(Card **head, Card *card_to_insert, int pick);
Card *shuffle(Card *pile1, Card *pile2);
Card *insert_at_start(Card **head, Card *card_to_insert);
Card *insert_at_end(Card **head, Card *card_to_insert);



Card *randomShuffle(Card *passedDeck) {
    Card *shuffledDeck = NULL;
    Card *currentCard = passedDeck;
    int max_position = 0;

    while (currentCard != NULL) {
        Card *nextCard = currentCard->next;
        currentCard->next = NULL; // detach card from passedDeck

        int pick = rand() % (max_position + 1); // picks random number between 0-max_position
        shuffle_at_random(&shuffledDeck, currentCard, pick);
        max_position++;
        currentCard = nextCard;
    }
    return shuffledDeck;
}

/**
* Inserts the passed card at the randomized pick location in the linked list
*/
Card *shuffle_at_random(Card **head, Card *card_to_insert, int pick) {

    if (pick == 0 || *head == NULL) {
        card_to_insert->next = *head;
        *head = card_to_insert;
        return *head;
    }
    Card *temp = *head;
    for (int i = 1; i < pick && temp->next != NULL; i++) {
        temp = temp->next; //traverse
    }
    card_to_insert->next = temp->next;
    temp->next = card_to_insert;

    return *head;
}
/**
* Takes a deck and a split position. Divides the deck into two at the given split
* Passes the two lists onto shuffle
* returns a shuffled deck
*/
Card *splitShuffle(Card *passedDeck, int split) {
    Card *firstPile = passedDeck;
    Card *ptr1 = passedDeck;
    for (int i = 1; i < split && ptr1->next != NULL; i++) {
        ptr1 = ptr1->next;
    }
    Card *secondPile = ptr1->next; // Start of the second pile
    ptr1->next = NULL;

    Card *shuffledDeck = shuffle(firstPile, secondPile);
    return shuffledDeck;
}

   // if (split == NULL || split < 0 || split > 52) {
   // int pick = rand() % (52 + 1);
   // shuffle(&shuffledDeck, currentCard, pick)
   // }
/**
* merges the two piles by taking one from each pile at a time.
* when a pile is exhausted remaining cards, loop makes sure the remaining cards in other pile gets added to the end
*
*/
Card *shuffle(Card *pile1, Card *pile2) {
    Card *shuffledDeck = NULL;

    while (pile1 != NULL || pile2 != NULL) {
        if (pile1 != NULL) {
            Card *nextCard = pile1->next;
            insert_at_end(&shuffledDeck, pile1);
            pile1 = nextCard;
        }
        if (pile2 != NULL) {
            Card *nextCard = pile2->next;
            insert_at_end(&shuffledDeck, pile2);
            pile2 = nextCard;
        }
    }
    return shuffledDeck;
  }

  /**
   * Traverses through the shuffled deck and attaches the passed card.
   * Might be able to do this with tail pointers instead, but for now this works
   */
Card *insert_at_end(Card **head, Card *card_to_insert) {
    card_to_insert->next = NULL;

    if (*head == NULL) {
        *head = card_to_insert;
        return card_to_insert;
    }
    Card *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = card_to_insert;
    return card_to_insert;
}

Card *insert_at_start(Card **head, Card *card_to_insert) {
    card_to_insert->next = *head;
    *head = card_to_insert;
    return card_to_insert;
}

