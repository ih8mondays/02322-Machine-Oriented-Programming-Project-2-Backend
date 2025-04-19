#include "moveCard.h"
#include "generateCards.h"
#include "main.h"
#include <inttypes.h>
#include <stdbool.h>


bool isEqual(Card * card, Suit suit, Rank rank);
Card * searchColumn(Card * searchHeader, Suit searchSuit, Rank searchRank);
int columnToColumn(char * input);
int toFoundation(char * input);
int fromFoundation(char * input);

// Possible valid inputs ... C1-C7 & F1-F4
//   CX:RS->CX
//   CX:RS->FX
//   CX->CX
//   CX->FX
//   FX->CX

int moveCard(char * input) {
    if (input[0] == 'C' && input[2] == ':' && input[7] == 'C'
        || input[0] == 'C' && input[2] == '-' && input[4] == 'C') {
        return columnToColumn(input);
    } else if ( input[0] == 'C' && input[2] == ':' && input[7] == 'F'
        || input[0] == 'C' && input[2] == '-' && input[4] == 'F') {
        return toFoundation(input);
    } else if (input[0] == 'F') {
        return fromFoundation(input);
    }
    return -1;
}


int columnToColumn(char * input) {
    Card * searchHeader = columnHeader[input[1]-'0'-1];

    // find the card we want to move
    if (input[2] == ':') {
        Rank searchRank = rank[input[3]-'0'-1];
        Suit searchSuit = suit[input[4]-'0'-1];
        Card * target = searchColumn(searchHeader,searchRank, searchSuit);
        if (target == NULL) { return -1; }
    } else if (input[2] == '-') {
        Card * columnEnd = searchHeader;
        while (columnEnd->next != NULL) { columnEnd = columnEnd->next; }
        Card * target = columnEnd;
    }





    return 1;
}


//
//  if (searchHeader == NULL) {
//  columnHeader[j] = currentFill;
//  } else {
//            columnEnd = columnHeader[j];
//            while (columnEnd->next != NULL) { columnEnd = columnEnd->next; }
//            columnEnd->next = currentFill;
//  }


int toFoundation(char *input) {
    return 1;
}

int fromFoundation(char *input) {
    return 1;
}


Card *searchColumn(Card * searchHeader, Suit searchSuit, Rank searchRank) {
    Card *current = searchHeader;

    while (current != NULL) {
        if (isEqual(current, searchSuit, searchRank)) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

bool isEqual(Card * card, Suit suit, Rank rank) {
    return card->suit == suit && card->rank == rank;
}





