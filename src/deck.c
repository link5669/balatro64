#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <libdragon.h>
#include "include/deck.h"
#include <stdlib.h>

void init_deck(Card deck[]) {
    int index = 0;
    for ( Suite s = CLUB; s <= DIAMOND; s++) {
           for ( Rank r = TWO; r <= ACE; r++) {
               deck[index].rank = r;
               deck[index].suite = s;
               index++;
           }
       }
}

Card pick_card(Card deck[]) {
    int r = rand() % 52; //change to deck length when deck > 52
    return deck[r];
}
