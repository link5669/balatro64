#ifndef DECK_H
#define DECK_H

typedef struct State State;
// Define enums for card suites and ranks
typedef enum {
    CLUB,
    SPADE,
    HEART,
    DIAMOND
} Suite;

typedef enum {
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING,
    ACE
} Rank;

typedef enum {
    SUITE,
    RANK
} SortType;

// Define the Card struct
typedef struct {
    Rank rank;  // Now the compiler knows what Rank is
    Suite suite; // Now the compiler knows what Suite is
    bool used;
} Card;

// Function declarations
void init_deck();
int pick_card();
void sort_hand(SortType sort_type);

#endif
