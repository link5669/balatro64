#include <malloc.h>
#include <stdint.h>
#include <stdbool.h>
#include <libdragon.h>
#include "include/poker_hand.h"
#include "include/state.h"

extern State state;

PokerHand detect_hand() {
    PokerHand hand = HIGH_CARD;

    Suite suite = state.deck[state.selected_cards[0]].suite;
    for (int i = 0; i < 5; i++) {
        if (state.selected_cards[i] == -1) continue;
        if (suite != state.deck[state.selected_cards[i]].suite) {
            break;
        }
        if (i == 4) hand = FLUSH;
    }
    Rank lowestRank = ACE;
    for (int i = 0; i < 5; i++) {
        Rank currRank = state.deck[state.selected_cards[i]].rank;
        if (currRank < lowestRank) lowestRank = currRank;
    }
    Rank rankPtr = lowestRank;
    for (int i = 0; i < 5; i++) {
        for (int i = 0; i < 5; i++) {
            Rank currRank = state.deck[state.selected_cards[i]].rank;
            if (rankPtr+1 == currRank) rankPtr++;
        }
    }
    if (rankPtr - 4 == lowestRank) {
        if (hand == FLUSH) hand = STRAIGHT_FLUSH;
        else hand = STRAIGHT;
    }
    return hand;
}
