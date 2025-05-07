#ifndef SEARCHCOLUMN_H
#define SEARCHCOLUMN_H

#include "generateCards.h"
#include "validateInput.h"

typedef struct DualPointer{
    Card * previous;
    Card * current;
} DualPointer;

void moveCard(char * input);
Rank charToRank(char input);
Suit charToSuit(char input);
Card * retColEnd(Card * columnHeader);


#endif //SEARCHCOLUMN_H
