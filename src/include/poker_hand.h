#ifndef HAND_C
#define HAND_C

typedef enum {
    HIGH_CARD,
    PAIR,
    TWO_PAIR,
    THREE_OF_A_KIND,
    STRAIGHT,
    FLUSH,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    STRAIGHT_FLUSH,
    ROYAL_FLUSH,
    FIVE_OF_A_KIND,
    FLUSH_HOUSE,
    FLUSH_FIVE
} PokerHand;

typedef struct Score {
    int chips;
    int mult;
} Score;

PokerHand detect_hand();
Score get_score(PokerHand hand);
#endif
