#ifndef SEARCHCOLUMN_H
#define SEARCHCOLUMN_H

#include "generateCards.h"

typedef struct DualPointer{
    Card * previous;
    Card * current;
} DualPointer;

int moveCard(char * input);
extern DualPointer retColEnd(Card * columnHeader);

#endif //SEARCHCOLUMN_H
