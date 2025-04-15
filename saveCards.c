#include <stdio.h>
#include "main.h"
#include "generateCards.h"

int saveCards(Card* head) {
    char * nRank[] = {"A","2","3","4","5","6","7","8","9","T","J","Q","K"};
    char * nSuit[] = {"C","D","H","S"};
    FILE * file = fopen("Cards.txt", "w");
    if (file == NULL) {
        printf("Error opening file\n");
    }

    Card *current = head;
    for (int i = 0; i < 52 && current != NULL ; i++) {
        fprintf(file,"%s%s\n",
            nRank[current->rank],
            nSuit[current->suit]);
        current = current -> next;
    }
    fclose(file);
    return 1;
}