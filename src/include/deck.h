#ifndef DECK_H
#define DECK_H

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

// Define the Card struct
typedef struct {
    Rank rank;  // Now the compiler knows what Rank is
    Suite suite; // Now the compiler knows what Suite is
} Card;

// Function declarations
void init_deck(Card deck[]);
Card pick_card(Card deck[]);

#endif
