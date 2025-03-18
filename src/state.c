#include <malloc.h>
#include <stdint.h>
#include <stdbool.h>
#include <libdragon.h>
#include "include/deck.h"
#include "include/state.h"

extern State state;

void init_state() {
    init_deck();
    state.hand_size = 8;
    for (int i = 0; i < 5; i++) {
        state.selected_cards[i] = -1;
    }
    for (int i = 0; i < state.hand_size; i++) {
        state.hand[i] = -1;
    }
}

void select_card(int card_index) {
    for (int i = 0; i < 5; i++) {
        if (state.selected_cards[i] == -1) {
            state.selected_cards[i] = card_index;
            break;
        }
    }
}

bool card_is_selected(int draw_index) {
    for (int i = 0; i < 5; i++) {
        if (state.deck[state.hand[draw_index]].suite == state.deck[state.selected_cards[i]].suite && state.deck[state.hand[draw_index]].rank == state.deck[state.selected_cards[i]].rank) {
            return true;
        }
    }
    return false;
}

void add_to_hand(int card_index) {
    for (int i = 0; i < state.hand_size; i++) {
        if ((state.hand[i] == -1) || state.deck[state.hand[i]].used) {
            state.hand[i] = card_index;
            break;
        }
    }
}
