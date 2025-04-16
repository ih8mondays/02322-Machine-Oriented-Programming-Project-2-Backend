#include <stdio.h>
#include "main.h"
#include "generateCards.h"

int saveCards(Card* head) {
    FILE * file = fopen("Cards.txt", "w");
    if (file == NULL) {
        printf("Error opening file\n");
    }

    Card *current = head;
    for (int i = 0; i < 52 && current != NULL ; i++) {
        fprintf(file,"%s%s %s\n",
            rankName[current->rank],
            suitName[current->suit],
            hiddenName[current->hidden]);
        current = current -> next;
    }
    fclose(file);
    return 1;
}