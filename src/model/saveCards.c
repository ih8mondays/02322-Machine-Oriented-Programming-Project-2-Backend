#include "../controller/gameController.h"
#include "../../main.h"
#include "generateCards.h"
#include "validateInput.h"
#include <stdio.h>
#include <string.h>

/**
 * Saves deck order to external file
 * @param command
 * @param input should end in .txt but can be of different types. Defaults to 'cards.txt'.
 * TODO determine whether the above is a good idea.
 */
void saveCards(Command command, char * input) {

    if (deckHeader == NULL) {
        setBoardMessage("Can't save an empty deck.");
        return;
    }

    char filename[50];

    // default file name
    if (command == CMD_SD) {
        strncpy(filename, "cards.txt", sizeof(filename) - 1);
    // reads file name from input
    } else if (command == CMD_SD_FILENAME) {
        strncpy(filename, &input + 3, sizeof(filename) - 1);
    // shouldn't happen
    } else {
        !debug? : memset(boardMessage, '\0', sizeof(boardMessage));
        !debug? : snprintf(boardMessage,sizeof(boardMessage),"Error in %s line %d",__FILE_NAME__,__LINE__);
        return;
    }

    char savedDeckDirectory[70] = "../../saved_decks/";
    strcat(savedDeckDirectory,filename);
    printf(savedDeckDirectory);

    FILE * file = fopen(savedDeckDirectory, "w");
    if (file == NULL) {
        !debug? : setBoardMessage("Error opening file");
        return;
    }

    // print deck into file
    Card * current = deckHeader;
    for (int i = 0; i < 52 && current != NULL ; i++) {
        fprintf(file,"%s%s\n",
            rankName[current->rank],
            suitName[current->suit]);
        current = current -> next;
    }
    fclose(file);
}