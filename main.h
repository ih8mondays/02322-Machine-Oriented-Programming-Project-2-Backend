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

typedef enum Hidden {
    HIDDEN,
      SHOWN
  } Hidden;


typedef struct Card {
    Rank rank;
    Suit suit;
    int hidden;
    struct Card *next;
} Card;

Card * generateCards();
void fillBoard(Card * deckHeader, Card * columnHeader[]);

#endif //MAIN_H
