#include "deck.h"

#ifndef STATE_H
#define STATE_H

typedef struct State {
    int selected_cards[5];
    Card deck[52];
    int hand_size;
    int hand[8];
} State;

void init_state();
void select_card(int card_index);
void add_to_hand(int card_index);
bool card_is_selected(int draw_index);

#endif
