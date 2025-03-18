#include <malloc.h>
#include <stdint.h>
#include <stdbool.h>
#include <libdragon.h>
#include "include/deck.h"
#include "include/poker_hand.h"
#include "include/state.h"

State state;

void draw_card(surface_t *disp, int x, int y,  Rank rank,  Suite suite, bool selected) {
    graphics_draw_box(disp, x, y, 40, 70, graphics_make_color(230, 230, 230, 255));
    if (suite == CLUB) {
        graphics_set_color(graphics_make_color(66, 135, 245, 255),graphics_make_color(230, 230, 230, 255));
        graphics_draw_character(disp, x+5, y+5, 'C');
    } else if (suite == SPADE) {
        graphics_set_color(graphics_make_color(23, 23, 20, 255),graphics_make_color(230, 230, 230, 255));
        graphics_draw_character(disp, x+5, y+5, 'S');
    } else if (suite == HEART) {
        graphics_set_color(graphics_make_color(171, 22, 49, 255),graphics_make_color(230, 230, 230, 255));
        graphics_draw_character(disp, x+5, y+5, 'H');
    } else if (suite == DIAMOND) {
        graphics_set_color(graphics_make_color(224, 137, 22, 255),graphics_make_color(230, 230, 230, 255));
        graphics_draw_character(disp, x+5, y+5, 'D');
    }
    if (rank == TWO) {
        graphics_draw_character(disp, x+5, y+15, '2');
    } else if (rank == THREE) {
        graphics_draw_character(disp, x+5, y+15, '3');
    } else if (rank == FOUR) {
        graphics_draw_character(disp, x+5, y+15, '4');
    } else if (rank == FIVE) {
        graphics_draw_character(disp, x+5, y+15, '5');
    } else if (rank == SIX) {
        graphics_draw_character(disp, x+5, y+15, '6');
    } else if (rank == SEVEN) {
        graphics_draw_character(disp, x+5, y+15, '7');
    } else if (rank == EIGHT) {
        graphics_draw_character(disp, x+5, y+15, '8');
    } else if (rank == NINE) {
        graphics_draw_character(disp, x+5, y+15, '9');
    } else if (rank == TEN) {
        graphics_draw_text(disp, x+5, y+15, "10");
    } else if (rank == JACK) {
        graphics_draw_text(disp, x+5, y+15, "J");
    } else if (rank == QUEEN) {
        graphics_draw_text(disp, x+5, y+15, "Q");
    } else if (rank == KING) {
        graphics_draw_text(disp, x+5, y+15, "K");
    } else if (rank == ACE) {
        graphics_draw_text(disp, x+5, y+15, "A");
    }
}

void draw_card_border(surface_t *disp, int highlighted) {
    for (int i = 0; i < state.hand_size; i++) {
        int color = highlighted  == i? graphics_make_color(50, 50, 240, 255):graphics_make_color(0, 0, 0, 255);
        int x = 240+(i*30);
        int y = card_is_selected(i) ? 280: 300;
        graphics_draw_line(disp, x, y, i != state.hand_size -1 ? x+30 : x+40, y, color);
        graphics_draw_line(disp, x, y, x, y+70, color);
    }
}

void draw_hand(surface_t *disp, int highlighted_card) {
    sort_hand(state.sort_type);
    for (int i = 0; i < state.hand_size; i++) {
        draw_card(disp, 240+(i*30), 300, state.deck[state.hand[i]].rank, state.deck[state.hand[i]].suite, i == highlighted_card);
    }
}

void draw_ui(surface_t *disp) {
    graphics_draw_box(disp, 5, 0, 170, 480, graphics_make_color(80, 80, 80, 255));
    graphics_draw_box(disp, 5, 100, 170, 40, graphics_make_color(40, 40, 40, 255));
    graphics_draw_box(disp, 5, 100, 170, 40, graphics_make_color(40, 40, 40, 255));

    graphics_draw_text(disp, 8, 105, "Your\nScore");
    graphics_draw_box(disp, 310, 400, 140, 40, graphics_make_color(40, 40, 40, 255));
    graphics_draw_box(disp, 315, 405, 60, 30, graphics_make_color(200, 40, 40, 255));
    graphics_draw_box(disp, 385, 405, 60, 30, graphics_make_color(200, 40, 40, 255));
    graphics_draw_text(disp, 317, 407, "LT");
    graphics_draw_text(disp, 428, 407, "RT");
}

const char* rank_to_string(Rank rank) {
    static const char* ranks[] = {
        "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"
    };
    return ranks[rank];
}

int main(void)
{
    display_init(RESOLUTION_640x480, DEPTH_16_BPP, 1, GAMMA_NONE, FILTERS_RESAMPLE);
    rdpq_init();
    controller_init();
    timer_init();

    surface_t *disp;
    struct controller_data c_data;
    int highlighted_card = 0;
    init_state();

    disp = display_get();
    graphics_fill_screen(disp, graphics_make_color(0, 180, 0, 255));
    display_show(disp);
    draw_ui(disp);

    while (1)
    {
        controller_scan();
        disp = display_get();

        c_data = get_keys_down();

        if (c_data.c[0].B)
        {
            for (int i = 0; i < state.hand_size; i++) {
                int rand = pick_card();
                add_to_hand(rand);
                draw_card(disp, 240+(i*30), 300, state.deck[state.hand[i]].rank, state.deck[state.hand[i]].suite, i == highlighted_card);
                draw_card_border( disp,  highlighted_card);
            }
        }
        if (c_data.c[0].C_right) {
            if (highlighted_card != state.hand_size -1) {
                highlighted_card++;
                draw_card_border( disp,  highlighted_card);
            }
        }
        if (c_data.c[0].C_left) {
            if (highlighted_card != 0) {
                highlighted_card--;
                draw_card_border( disp,  highlighted_card);
            }
        }
        if (c_data.c[0].A) {
            graphics_draw_box(disp, 240, 280, 200, 90, graphics_make_color(0, 180, 0, 255));
            if (card_is_selected(highlighted_card)) {
                deselect_card(state.hand[highlighted_card]);
            } else {
                select_card(state.hand[highlighted_card]);
            }
            for (int i = 0; i < state.hand_size; i++) {
                draw_card(disp, 240+(i*30), card_is_selected(i) ? 280: 300, state.deck[state.hand[i]].rank, state.deck[state.hand[i]].suite, i == highlighted_card);
            }
            draw_card_border( disp,  highlighted_card);
            PokerHand hand = detect_hand();
            if (hand == STRAIGHT) {
                graphics_draw_text(disp, 20, 300, "Straight");
            } else if (hand == FLUSH) {
                graphics_draw_text(disp, 20, 300, "Flush");
            }
        }
        if (c_data.c[0].L) {
            sort_hand(RANK);
            draw_hand(disp, highlighted_card);
            draw_card_border( disp,  highlighted_card);
        }
        if (c_data.c[0].R) {
            sort_hand(SUITE);
            draw_hand(disp, highlighted_card);
            draw_card_border( disp,  highlighted_card);
        }
        if (c_data.c[0].left) { //discard
            for (int i = 0; i < 5; i++) { //num of selected cards
                state.deck[state.selected_cards[i]].used = true;
                state.selected_cards[i] = -1;
                int rand = pick_card();
                add_to_hand(rand);
            }
            for (int i = 0; i < 8; i++) {
                graphics_draw_text(disp, 20, 20 + (i * 10), state.deck[state.hand[i]].used ? "true" : "false");
            }
            graphics_draw_box(disp, 240, 280, 200, 90, graphics_make_color(0, 180, 0, 255));
            draw_hand(disp, highlighted_card);
            draw_card_border( disp,  highlighted_card);
        }
        if (c_data.c[0].right) {
            PokerHand hand = detect_hand();
            Score score = get_score(hand);
            state.score += score.chips * score.mult;
            char str[20];
            sprintf(str, "%d", state.score);
            graphics_draw_text(disp, 20, 115, str);
            for (int i = 0; i < 5; i++) { //num of selected cards
                state.deck[state.selected_cards[i]].used = true;
                state.selected_cards[i] = -1;
                int rand = pick_card();
                add_to_hand(rand);
            }
            for (int i = 0; i < 8; i++) {
                graphics_draw_text(disp, 20, 20 + (i * 10), state.deck[state.hand[i]].used ? "true" : "false");
            }
            graphics_draw_box(disp, 240, 280, 200, 90, graphics_make_color(0, 180, 0, 255));
            draw_hand(disp, highlighted_card);
            draw_card_border( disp,  highlighted_card);
        }
        display_show(disp);
    }
}
