//
// Created by Rasmu on 28-04-2025.
//

#ifndef SHUFFLEDECK_H
#define SHUFFLEDECK_H

Card *shuffleDeck(Card *passedDeck);
Card *insert_at_random(Card **head, Card *card_to_insert, int pick);

void testPrintDeck(Card *deck);

#endif //SHUFFLEDECK_H
