#include "searchColumn.h"
#include "generateCards.h"
#include <inttypes.h>
#include <stdbool.h>

bool isEqual(Card * one, Card two);

Card * searchColumn(Card * columnHeader, Card cardRequest) {
    Card * current = columnHeader;

    while (current != NULL) {
        if (isEqual(current, cardRequest)) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

bool isEqual(Card * one, Card two) {
    if (one->suit == two.suit || one->rank == two.rank) {
        return true;
    }
    return false;
}





