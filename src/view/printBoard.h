//
// Created by Rasmu on 29-04-2025.
//

#ifndef PRINTBOARD_H
#define PRINTBOARD_H
// Constants for board dimensions.

#include "../model/generateCards.h"

#define COLUMNS 7
#define FOUNDATIONS 4
#define MAX_ROWS 8  // You can adjust this if you like

void print_empty_board();
void print_filled_board();
void print_current_board();

void reveal_all_cards(Card* deckHeader);

#endif //PRINTBOARD_H
