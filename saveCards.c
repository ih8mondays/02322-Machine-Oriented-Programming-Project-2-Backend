#include <stdio.h>
#include "main.h"
#include "generateCards.h"


int saveCards(Card* head, char filename[]) {

    // default file name
    if (filename == NULL) {
        filename = "cards.txt";
    }

    FILE * file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file\n");
        return -1;
    }

    Card *current = head;
    for (int i = 0; i < 52 && current != NULL ; i++) {
        fprintf(file,"%s%s\n",
            rankName[current->rank],
            suitName[current->suit]);
        current = current -> next;
    }
    fclose(file);
    return 1;
}