//
// Created by Rasmu on 29-04-2025.
//

#ifndef PRINTBOARD_H
#define PRINTBOARD_H
// Constants for board dimensions.

#include "../model/generateCards.h"

#define COLUMNS 7
#define FOUNDATIONS 4
#define MAX_ROWS 10  // You can adjust this if you like

void print_empty_board();
void print_hidden_board();
void print_shown_board();
void print_current_board();
int get_max_rows();

#endif //PRINTBOARD_H
