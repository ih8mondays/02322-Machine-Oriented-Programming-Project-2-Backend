#include "moveCard.h"
#include "../../main.h"
#include "generateCards.h"
#include "loadCards.h"
#include "../controller/gameController.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <direct.h>


/**
 * Reads a file and validates if it contains exactly one of each card in a standard deck, then generates a deck according to the order listed in the file
 * @param Validated input containing the name of the file to open. Accepted format is one card per line (AC, 2C, 3C...)
 * The loaded deck is assigned to deckHeader.
 */
void loadCards(char * input) {

    ////////////////////////////////////
    //////////// Validation ////////////
    ////////////////////////////////////

    if (input[2] == '\0') {
        chainDelete(deckHeader);
        deckHeader = generateCards();
        return;
    }

    char fileName[50];
    strcpy(fileName,&input[3]);
    printf(fileName);


    //char savedDeckPath[70] = "saved_decks/";
    //strcat(savedDeckPath,fileName);
    //printf("Loading deck %s\n", savedDeckPath);

    FILE * file = fopen(fileName, "r");
    if (file == NULL) {
        !debug? : setBoardMessage("Error while opening file");
        specificError = 1;
        return;
    }

    //Validation procedure using matrix of zeroes
    int validationMatrix[rankSize][suitSize];
    memset(validationMatrix, 0, rankSize * suitSize * sizeof(int));

    char currentStr[10];

    // Reads lines and puts them into matrix
    for  (int lineCount = 1 ; !feof(file) && lineCount <= rankSize * suitSize ; lineCount++) {
        memset(currentStr, '\0', sizeof(currentStr));
        fgets(currentStr, sizeof(currentStr), file);

        //Ensure correct format so program won't crash
        if (!isRank(currentStr[0]) || !isSuit(currentStr[1])) {
            memset(boardMessage, '\0', sizeof(boardMessage));
            snprintf(boardMessage,sizeof(boardMessage),"Incorrect formatting at line %d.",lineCount);
            fclose(file);
            return;
        }

        Rank curR = strToRank(currentStr[0]);
        Suit curS = strToSuit(currentStr[1]);

        // End if we find a duplicate
        if (validationMatrix[curR][curS] == 0) {
            validationMatrix[curR][curS]++;
        } else {
            memset(boardMessage, '\0', sizeof(boardMessage));
            snprintf(boardMessage,sizeof(boardMessage),"Duplicate card at line %d.",lineCount);
            fclose(file);
            return;
        }
    }

    //Checks if the matrix contains only ones
    for (int i = 0; i < suitSize; ++i) {
        for (int j = 0; j < rankSize; ++j) {
            if (validationMatrix[j][i] != 1) {
                memset(boardMessage, '\0', sizeof(boardMessage));
                snprintf(boardMessage,sizeof(boardMessage),"%s%s is missing from the file.",rankName[j],suitName[i]);
                fclose(file);
                return;
            }
        }
    }

    ///////////////////////////////////
    //////// Loading procedure ////////
    ///////////////////////////////////

    rewind(file);
    Card *head = (Card *) malloc(sizeof(Card));
    Card *current = head;

    if (head == NULL) {
        !debug ? : setBoardMessage("Memory couldn't be allocated while generating cards");
        specificError = 1;
        fclose(file);
        return;
    }

    for (int i = 0; i < rankSize * suitSize; i++) {

        // Read next line
        memset(currentStr, '\0', sizeof(currentStr));
        fgets(currentStr, sizeof(currentStr), file);

        // Assign current card values
        current->rank = strToRank(currentStr[0]);
        current->suit = strToSuit(currentStr[1]);
        current->visibility = HIDDEN;

        // Last card won't allocate more memory
        if (i == rankSize * suitSize - 1) {
            current->next = NULL;
        } else {
            // Set up next card
            current->next = malloc(sizeof(Card));
            current = current->next;
        }

        if (current == NULL) {
            !debug ? : setBoardMessage("Memory couldn't be allocated while generating cards");
            specificError = 1;
            chainDelete(head);
            head = NULL;
            fclose(file);
            return;
        }
    }

    fclose(file);
    chainDelete(deckHeader);
    deckHeader = head;
}
