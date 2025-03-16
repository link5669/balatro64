#ifndef STATE_H
#define STATE_H
#include "deck.h"
typedef struct  {
    Card selected_cards[5];
    Card deck[52];
    int hand_size;
    Card hand[8];
} State;

State init_state(State state);
State select_card(State state, Card card);
State add_to_hand(State state, Card card);
bool card_is_selected(State state, int draw_index);
#endif
