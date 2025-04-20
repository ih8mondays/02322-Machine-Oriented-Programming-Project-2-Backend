#include <stdio.h>
#include "main.h"
#include "generateCards.h"

/**
 * Saves deck order to external file
 * @param head pointer to top card in deck
 * @param filename should end in .txt but can be of different types. Defaults to 'cards.txt' if parameter is NULL
 * TODO determine whether the above is a good idea.
 * @return 1 if successful, otherwise -1
 */
int saveCards(Card* head, char filename[]) {

    // default file name
    if (filename == NULL) {
        filename = "cards.txt";
    }

    FILE * file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file\n");
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