#include <stdio.h>
#include "printBoard.h"

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

