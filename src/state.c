#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <libdragon.h>
#include "include/deck.h"
#include "include/state.h"

#define EMPTY_CARD (Card){-1, -1}

State init_state(State state) {
    init_deck(state.deck);
    state.hand_size = 8;
    for (int i = 0; i < 5; i++) {
        state.selected_cards[i] = EMPTY_CARD;
    }
    for (int i = 0; i < state.hand_size; i++) {
        state.hand[i] = EMPTY_CARD;
    }
    return state;
}

State select_card(State state, Card card) {
    for (int i = 0; i < 5; i++) {
        if (state.selected_cards[i].rank == EMPTY_CARD.rank && state.selected_cards[i].suite == EMPTY_CARD.suite) {
            state.selected_cards[i] = card;
            break;
        }
    }

    return state;
}

bool card_is_selected(State state, int draw_index) {
    for (int i = 0; i < 5; i++) {
        if (state.hand[draw_index].suite == state.selected_cards[i].suite && state.hand[draw_index].rank == state.selected_cards[i].rank) {
            return true;
        }
    }
    return false;
}

State add_to_hand(State state, Card card) {
    for (int i = 0; i < state.hand_size; i++) {
        if (state.hand[i].rank == EMPTY_CARD.rank && state.hand[i].suite == EMPTY_CARD.suite) {
            state.hand[i] = card;
            break;
        }
    }

    return state;
}
