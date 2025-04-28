//
// Created by Rasmu on 28-04-2025.
//

#ifndef SHUFFLEDECK_H
#define SHUFFLEDECK_H

Card *randomShuffle(Card *passedDeck);
Card *splitShuffle(Card *passedDeck, int split);
Card *shuffle(Card *pile1, Card *pile2);
Card *shuffle_at_random(Card **head, Card *card_to_insert, int split);
Card *insert_at_start(Card **head, Card *card_to_insert);
Card *insert_at_end(Card **head, Card *card_to_insert);

void testPrintDeck(Card *deck);

#endif //SHUFFLEDECK_H
