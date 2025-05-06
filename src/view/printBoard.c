#include "printBoard.h"
#include "../controller/gameController.h"
#include "../model/generateCards.h"
#include "../model/validateInput.h"
#include <stdio.h>

// Helper functions
int get_max_rows();


void print_current_board() {
    int maxRows = get_max_rows();

    for (int col = 0; col < COLUMNS; col++) {
        printf("C%d\t", col + 1);
    }
    printf("\n\n");
    // For each row find and print the element at each depth. No element is printed as blank space
    for (int row = 0; row < (maxRows > 7 ? maxRows : 7); row++) {
        for (int col = 0; col < COLUMNS; col++) {
            Card *currentCard = columnHeader[col];
            int depth = 0;

            while (currentCard != NULL && depth < row) {
                currentCard = currentCard->next;
                depth++;
            }

            if (currentCard != NULL && currentCard->visibility == SHOWN) {
                printf("%s%s\t", rankName[currentCard->rank], suitName[currentCard->suit]);
            } else if (currentCard != NULL && currentCard->visibility == HIDDEN) {
                printf("[ ]\t");
            }else {
                printf("\t");
            }
        }

        if (row % 2 == 0 && row < 7) {
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
    printf("LAST Command: %s\n",commandName[command]);
    printf("Message: %s\n",boardMessage);
    printf("INPUT >");
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
        if (row % 2 == 0) {
            printf("\t");
            printf("[  ]    F%d", row / 2 + 1);
        }
        printf("\n");
    }
        printf("LAST Command: %s\n",commandName[command]);
    printf("Message: %s\n",boardMessage);
    printf("INPUT >");
}

void print_filled_board() {
    for (int col = 1; col <= COLUMNS; col++) {
        printf(" C%d\t", col);
    }
    printf("\n\n");

    Card *current = deckHeader;
    int row = 0;

    while (current != NULL) {
        for (int col = 0; col < COLUMNS && current != NULL; col++) {
            if (current->visibility == SHOWN) {
                printf("%s%s\t ", rankName[current->rank], suitName[current->suit]);
            } else {
                printf("[  ]\t ");
            }
            current = current->next; // Move to next card
        }
        if (row % 2 == 0) {
            printf("\t[  ]    F%d", row / 2 + 1);
        }
        printf("\n");
        row++;
    }
        printf("\n");

    printf("LAST Command: %s\n",commandName[command]);
    printf("Message: %s\n",boardMessage);
    printf("INPUT >");
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


void reveal_all_cards(Card* deckHeader) {
    Card* current = deckHeader;

    while (current != NULL) {
        current->visibility = SHOWN; // Set visibility to SHOWN
        current = current->next; // Move to the next card
    }
}

