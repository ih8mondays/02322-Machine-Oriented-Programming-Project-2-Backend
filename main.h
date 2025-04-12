//
// Created by bjoer on 10/04/2025.
//

#ifndef MAIN_H
#define MAIN_H

typedef enum Suit {
    CLUBS,
    DIAMONDS,
    HEARTS,
    SPADES
  } Suit;

typedef enum Rank {
    ACE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING
  } Rank;


typedef struct Card {
    Suit suit;
    Rank rank;;
    int hidden;
    struct Card *next;
} Card;

Card * generateCards();


#endif //MAIN_H
