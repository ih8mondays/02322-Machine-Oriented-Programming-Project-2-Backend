#include <stdio.h>
#include "main.h"
#include "generateCards.h"
#include "loadCards.h"

int loadCards(char filename[]) {

    // default file name
    if (filename == NULL) {
        filename = "cards.txt";
    }

    FILE * file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file\n");
        return -1;
    }

    //Validation procedure using matrix of zeroes
    int validationMatrix[rankSize][suitSize];
    for (int i = 0; i < rankSize; ++i) {
        for (int j = 0; j < suitSize; ++j) {
            validationMatrix[i][j] = 0;
            printf("%d", validationMatrix[i][j]);
        }
    }

    //Initializing with more than 2 chars so overflows do not occur
    char currentStr[10];
    fscanf(file, "%s", &currentStr);

    //Loop until file ends
    while (!feof(file)) {

        for (int i = 0; i < rankSize; ++i) {
            for (int j = 0; j < suitSize; ++j) {
                if (currentStr[0] == *rankName[i] && currentStr[1] == *suitName[j]) {
                    validationMatrix[i][j]++;
                }
            }
        }

        fscanf(file, "%s", &currentStr);
    }

    //Checks if the matrix contains only ones
    for (int i = 0; i < suitSize; ++i) {
        for (int j = 0; j < rankSize; ++j) {
            printf("%d", validationMatrix[j][i]);
            if (validationMatrix[j][i] != 1) {
                perror("Invalid file format\n");
                fclose(file);
                return -1;
            }
        }
    }

    printf("%s/n", "File valid, loading...");




    //TODO Load procedure
    rewind(file);


    fclose(file);
    return 1;
}