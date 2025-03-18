#include <malloc.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <libdragon.h>
#include "include/deck.h"
#include "include/state.h"

extern State state;

void init_deck() {
    int i = 0;
    for ( Suite s = CLUB; s <= DIAMOND; s++) {
           for ( Rank r = TWO; r <= ACE; r++) {
               state.deck[i].rank = r;
               state.deck[i].suite = s;
               state.deck[i].used = false;
               i++;
           }
       }
}

int pick_card() {
    int r = rand() % 52; //change to deck length when deck > 52
    for (int i = 0; i < 8; i++) { // change to hand size
        if (state.deck[r].used || state.hand[i] == r){
             return pick_card();
        }
    }
    return r;
}

int suite_comp(const void* a, const void* b) {
    int index_a = *(int*)a;
    int index_b = *(int*)b;
    Card* card_a = &state.deck[index_a];
    Card* card_b = &state.deck[index_b];

    if (card_a->suite != card_b->suite)
        return card_a->suite - card_b->suite;
    return card_b->rank - card_a->rank;
}

int rank_comp(const void* a, const void* b) {
    int index_a = *(int*)a;
    int index_b = *(int*)b;
    Card* card_a = &state.deck[index_a];
    Card* card_b = &state.deck[index_b];
    if (card_a->rank != card_b->rank)
        return card_a->rank - card_b->rank;
    return card_b->suite - card_a->suite;
}

void sort_hand(SortType sort_type) {
    if (sort_type == SUITE)
        qsort(state.hand, 8, sizeof(int), (int (*)(const void*, const void*))suite_comp);
    else
        qsort(state.hand, 8, sizeof(int), (int (*)(const void*, const void*))rank_comp);
}
