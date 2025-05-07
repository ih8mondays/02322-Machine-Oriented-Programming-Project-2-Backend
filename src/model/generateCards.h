#ifndef GENERATECARDS_H
#define GENERATECARDS_H

typedef enum Suit {
    CLUBS,
    DIAMONDS,
    HEARTS,
    SPADES,
    NOT_SUIT
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
    KING,
    NOT_RANK
  } Rank;

typedef enum Visibility {
    HIDDEN,
    SHOWN
  } Visibility;


typedef struct Card {
    Rank rank;
    Suit suit;
    Visibility visibility;
    struct Card *next;
} Card;


Card * generateCards();
void chainDelete(Card * deckHeader);
void clearBoard();

/** C,D,H,S */
extern const char * rankName[];
/** A, 2, 3, 4, 5, 6, 7, 8, 9 , T, J, Q, K */
extern const char * suitName[];
/** Hidden, Shown */
extern const char * visibilityName[];

extern const int suitSize;
extern const int rankSize;

#endif //GENERATECARDS_H
