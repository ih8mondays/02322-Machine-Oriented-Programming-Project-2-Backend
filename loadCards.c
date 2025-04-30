#include <stdio.h>
#include "main.h"
#include "generateCards.h"
#include "loadCards.h"

#include <stdlib.h>


/**
 * Reads a file and validates if it contains exactly one of each card in a standard deck, then generates a deck according to the order listed in the file
 * @param filename Name of the file to open. Accepted format is one card per line (AC, 2C, 3C...)
 * @return Pointer of the top card of the constructed deck
 */
Card *loadCards(char filename[]) {
    if (filename == NULL) {
        perror("null filename");
        return NULL;
    }

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file\n");
        return NULL;
    }

    //Validation procedure using matrix of zeroes
    // printf("Validating file contents... \n");
    int validationMatrix[rankSize][suitSize];
    for (int i = 0; i < rankSize; ++i) {
        for (int j = 0; j < suitSize; ++j) {
            validationMatrix[i][j] = 0;
        }
    }

    //Initializing with more than 2 chars so overflows do not occur
    char currentStr[10];
    int lineCount = 0;
    fscanf(file, "%s", &currentStr);

    //Loop until file ends
    while (!feof(file) && lineCount < rankSize * suitSize) {
        for (int i = 0; i < rankSize; ++i) {
            for (int j = 0; j < suitSize; ++j) {
                if (currentStr[0] == *rankName[i] && currentStr[1] == *suitName[j]) {
                    validationMatrix[i][j]++;
                }
            }
        }
        ++lineCount;
        fscanf(file, "%s", &currentStr);
    }

    //Checks if the matrix contains only ones
    for (int i = 0; i < suitSize; ++i) {
        for (int j = 0; j < rankSize; ++j) {
            if (validationMatrix[j][i] != 1) {
                perror("Invalid file format\n");
                fclose(file);
                return NULL;
            }
        }
    }

    // printf("%s\n", "File valid, loading...");


    //Loading procedure
    rewind(file);
    Card *head = (Card *) malloc(sizeof(Card));
    Card *current = head;

    if (head == NULL) {
        !debug ? : printf("Memory couldn't be allocated while generating cards");
        return NULL;
    }

    for (int i = 0; i < rankSize * suitSize; i++) {
        fscanf(file, "%s", &currentStr);

        for (int j = 0; j < rankSize; ++j) {
            for (int k = 0; k < suitSize; ++k) {
                if (currentStr[0] == *rankName[j] && currentStr[1] == *suitName[k]) {
                    current->rank = rank[j];
                    current->suit = suit[k];
                    current->visibility = HIDDEN;
                }
            }
        }

        // Last card won't allocate more memory
        if (i == rankSize * suitSize - 1) {
            current->next = NULL;
            fclose(file);
            return head;
        }

        // Set up next card
        current->next = malloc(sizeof(Card));
        current = current->next;

        if (current == NULL) {
            !debug ? : printf("Memory couldn't be allocated while generating cards");
            free(head);
            return NULL;
        }
    }
    fclose(file);
    return head;
}
