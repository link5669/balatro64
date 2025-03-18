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

Score get_score(PokerHand hand) {
    switch (hand){
    case HIGH_CARD:
        return (Score){5,1};
    case PAIR:
        return (Score){10,2};
    case TWO_PAIR:
        return (Score){20,2};
    case THREE_OF_A_KIND:
        return (Score){30,3};
    case STRAIGHT:
        return (Score){30,4};
    case FLUSH:
        return (Score){35,4};
    case FULL_HOUSE:
        return (Score){40,4};
    case FOUR_OF_A_KIND:
        return (Score){60,7};
    case STRAIGHT_FLUSH:
        return (Score){100,8};
    case ROYAL_FLUSH:
        return (Score){100,8};
    case FIVE_OF_A_KIND:
        return (Score){120,12};
    case FLUSH_HOUSE:
        return (Score){140,14};
    case FLUSH_FIVE:
        return (Score){160,16};
    }
    return (Score){0,0};
}
