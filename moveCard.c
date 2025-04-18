#include "moveCard.h"
#include "generateCards.h"
#include <inttypes.h>
#include <stdbool.h>

bool isEqual(Card * card, Suit suit, Rank rank);
Card * searchColumn(Card * columnHeader, Card cardRequest);
int moveCardFromColumnToColumn(char * Command);
int moveCardToFoundation(char * Command);
int moveCardFromFoundation(char * Command);

// CX:XS->CX
// CX:XS->FX
// CX->CX
// CX->FX
// FX->CX

int moveCard(char * Command) {
    if (Command[0] == 'C') {
        return moveCardFromColumnToColumn(Command);
    } else if (Command[0] == 'F') {
        return moveCardToFoundation(Command);
    }
    moveCardFromFoundation(Command);

    return -1;
}


int moveCardFromColumnToColumn(char * Command) {
    if (Command[2] == ':') {

    } else if (Command[2] == '-') {

    }

    int x = Command[1] - '0';

    return 1;
}


int moveCardToFoundation(char * Command) {

    return 1;
}

int moveCardFromFoundation(char * Command) {


    return 1;
}





Card * searchColumn(Card * columnHeader, Suit searchSuit, Rank searchRank) {
    Card * current = columnHeader;

    while (current != NULL) {
        if (isEqual(current, searchSuit, searchRank)) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

bool isEqual(Card * card, Suit suit, Rank rank) {
    if (card->suit == suit && card->rank == rank) {
        return true;
    }
    return false;
}





