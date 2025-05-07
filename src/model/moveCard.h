#ifndef SEARCHCOLUMN_H
#define SEARCHCOLUMN_H

#include "generateCards.h"
#include "validateInput.h"

typedef struct DualPointer{
    Card * previous;
    Card * current;
} DualPointer;

void moveCard(char * input);
Rank strToRank(char input);
Suit strToSuit(char input);
Card * retColEnd(Card * columnHeader);
DualPointer retColEndDual(Card * columnHeader);
DualPointer searchColumn(Card * searchHeader, Rank searchRank, Suit searchSuit);

#endif //SEARCHCOLUMN_H
