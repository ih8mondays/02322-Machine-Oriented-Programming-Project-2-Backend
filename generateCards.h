#ifndef GENERATECARDS_H
#define GENERATECARDS_H

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

/** C,D,H,S */
extern const char * rankName[];
/** A, 2, 3, 4, 5, 6, 7, 8, 9 , T, J, Q, K */
extern const char * suitName[];
/** Hidden, Shown */
extern const char * hiddenName[];

extern const int suitSize;
extern const int rankSize;


#endif //GENERATECARDS_H
