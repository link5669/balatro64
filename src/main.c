#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <libdragon.h>
#include "include/deck.h"
#include "include/state.h"

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

void draw_card_border(surface_t *disp, int highlighted, State state) {
    for (int i = 0; i < state.hand_size; i++) {
        int color = highlighted  == i? graphics_make_color(50, 50, 240, 255):graphics_make_color(0, 0, 0, 255);
        int x = 240+(i*30);
        int y = card_is_selected(state, i) ? 280: 300;
        graphics_draw_line(disp, x, y, x+40, y, color);
        graphics_draw_line(disp, x, y, x, y+70, color);
    }
}

void draw_hand(surface_t *disp, State state, int highlighted_card) {
    for (int i = 0; i < state.hand_size; i++) {
        draw_card(disp, 240+(i*30), 300, state.hand[i].rank, state.hand[i].suite, i == highlighted_card);
    }
}

void draw_ui(surface_t *disp) {
    graphics_draw_box(disp, 5, 0, 170, 480, graphics_make_color(80, 80, 80, 255));
    graphics_draw_box(disp, 5, 100, 170, 40, graphics_make_color(40, 40, 40, 255));
    graphics_draw_box(disp, 5, 100, 170, 40, graphics_make_color(40, 40, 40, 255));

    graphics_draw_text(disp, 8, 105, "Your\nScore");
}

int main(void)
{
    display_init(RESOLUTION_640x480, DEPTH_16_BPP, 1, GAMMA_NONE, FILTERS_RESAMPLE);
    rdpq_init();
    controller_init();
    timer_init();

    surface_t *disp;
    State state;
    struct controller_data c_data;
    int highlighted_card = 0;
    state = init_state(state);

    disp = display_get();
    graphics_fill_screen(disp, graphics_make_color(0, 180, 0, 255));
    display_show(disp);

    while (1)
    {
        controller_scan();
        disp = display_get();

        c_data = get_keys_down();

        draw_ui(disp);
        if (c_data.c[0].B)
        {
            for (int i = 0; i < state.hand_size; i++) {
                Card rand = pick_card(state.deck);
                state = add_to_hand(state, rand);
                draw_card(disp, 240+(i*30), 300, state.hand[i].rank, state.hand[i].suite, i == highlighted_card);
                draw_card_border( disp,  highlighted_card, state);

            }
        }
        if (c_data.c[0].C_right) {
            if (highlighted_card != state.hand_size -1) {
                highlighted_card++;
                draw_card_border( disp,  highlighted_card, state);
            }
        }
        if (c_data.c[0].C_left) {
            if (highlighted_card != 0) {
                highlighted_card--;
                draw_card_border( disp,  highlighted_card, state);
            }
        }
        if (c_data.c[0].A) {
            graphics_draw_box(disp, 240, 280, 480, 90, graphics_make_color(0, 180, 0, 255));
            state = select_card(state, state.hand[highlighted_card]);
            for (int i = 0; i < state.hand_size; i++) {
                draw_card(disp, 240+(i*30), i == highlighted_card ? 280: 300, state.hand[i].rank, state.hand[i].suite, i == highlighted_card);
            }
            draw_card_border( disp,  highlighted_card, state);
        }
        display_show(disp);
    }
}
