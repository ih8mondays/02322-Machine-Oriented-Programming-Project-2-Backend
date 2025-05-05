#include "printBoard.h"
#include "../controller/gameController.h"
#include "../model/generateCards.h"
#include <stdio.h>
void print_current_board() {
    int maxRows = get_max_rows();

    for (int col = 0; col < COLUMNS; col++) {
        printf("C%d\t", col + 1);
    }
    printf("\n\n");
    // For each row find and print the element at each depth. No element is printed as blank space
    for (int row = 0; row < maxRows; row++) {
        for (int col = 0; col < COLUMNS; col++) {
            Card *currentCard = columnHeader[col];
            int depth = 0;

            while (currentCard != NULL && depth < row) {
                currentCard = currentCard->next;
                depth++;
            }
            if (currentCard != NULL) {
                printf("%s%s\t", rankName[currentCard->rank], suitName[currentCard->suit]);
            } else {
                printf("\t");
            }
        }
        // Traverse through foundationPiles and prints last element. If no element excist in pile a placeholder is printed.
        if (row == 0 || row == 2 || row == 4 || row == 6) {
            printf("\t");
            Card *pileCard = foundationHeader[row / 2];

            while (pileCard != NULL && pileCard->next != NULL) {
                pileCard = pileCard->next;
            }
            if (pileCard != NULL) {
                printf(" %s%s     F%d", rankName[pileCard->rank], suitName[pileCard->suit], row / 2 + 1);
            } else {
                printf("[  ]    F%d", row / 2 + 1);
            }
        }
        printf("\n");
    }
    printf("LAST Command: \n");
    printf("Message: \n");
    printf("INPUT > \n");
}

// Function to print the board layout.
void print_empty_board() {

    for (int col = 1; col <= COLUMNS; col++) {
        printf(" C%d\t", col);
    }
    printf("\n");
    for (int row = 0; row < MAX_ROWS; row++) {
        for (int col = 0; col < COLUMNS; col++) {
            printf("\t");
        }
        if (row == 0 || row == 2 || row == 4 || row == 6) {
            printf("\t");
            if (row == 0)
                printf("[  ]    F1");
            else if (row == 2)
                printf("[  ]    F2");
            else if (row == 4)
                printf("[  ]    F3");
            else if (row == 6)
                printf("[  ]    F4");
        }
        printf("\n");
    }
    printf("LAST Command: \n");
    printf("Message: \n");
    printf("INPUT > \n");
}
// Hacky print of the hidden board, does not actually take card locations into account
void print_hidden_board() {
    for (int col = 1; col <= COLUMNS; col++) {
        printf(" C%d\t", col);
    }
    printf("\n\n");
    for (int row = 0; row < MAX_ROWS; row++) {
        for (int col = 0; col < COLUMNS; col++) {
            if (row < 7 || (row < 8 && col < 3)) {
                printf("%s\t", " []");
            } else {
                printf("\t");
            }
        }
        if (row == 0 || row == 2 || row == 4 || row == 6) {
            printf("\t");
            if (row == 0)
                printf("[  ]    F1");
            else if (row == 2)
                printf("[  ]    F2");
            else if (row == 4)
                printf("[  ]    F3");
            else if (row == 6)
                printf("[  ]    F4");
        }
        printf("\n");
    }
    printf("LAST Command: \n");
    printf("Message: \n");
    printf("INPUT > \n");
}

void print_shown_board() {
    Card *current = deckHeader;
    for (int col = 1; col <= COLUMNS; col++) {
        printf(" C%d\t", col);
    }
    printf("\n\n");
    for (int row = 0; row < MAX_ROWS; row++) {
        for (int col = 0; col < COLUMNS; col++) {
            if (row < 7 || (row < 8 && col < 3)) {
                printf("%s%s%s\t",
                       " ",
                       rankName[current->rank],
                       suitName[current->suit]);
                current = current->next;
            } else {
                printf("\t");
            }
        }
        if (row == 0 || row == 2 || row == 4 || row == 6) {
            printf("\t");
            if (row == 0)
                printf("[  ]    F1");
            else if (row == 2)
                printf("[  ]    F2");
            else if (row == 4)
                printf("[  ]    F3");
            else if (row == 6)
                printf("[  ]    F4");
        }
        printf("\n");
    }
    printf("LAST Command: \n");
    printf("Message: \n");
    printf("INPUT > \n");
}

/*
 Returns the longest list in columnHeader as an int, so board can dynamically print the correct length
 */
int get_max_rows() {
    int maxRows = 0;
    for (int col = 0; col < COLUMNS; col++) {
        int depth = 0;
        Card *currentCard = columnHeader[col];

        while (currentCard != NULL) {
            currentCard = currentCard->next;
            depth++;
        }
        if (depth > maxRows) {
            maxRows = depth;
        }
    }
    return maxRows;
}

