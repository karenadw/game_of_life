#include <ncurses.h>

#include "game_of_life.h"

#define SPEED_STEP_MS 50
#define KEY_QUIT ' '

static void init_screen(void)
{
    initscr();
    cbreak();
    noecho();
    curs_set(0);
}

static void close_screen(void)
{
    endwin();
}

void draw_field(const Game *game)
{
    int row;
    int col;
    char symbol;

    for (row = 0; row < HEIGHT; row++) {
        for (col = 0; col < WIDTH; col++) {
            symbol = (game->field[row][col] == ALIVE) ? CHAR_ALIVE : CHAR_DEAD;
            mvaddch(row, col, symbol);
        }
    }
    mvprintw(HEIGHT, 0, "Gen: %d  Alive: %d  Delay: %d ms   ",
             game->generation, game->alive_count, game->speed_ms);
    refresh();
}

void change_speed(Game *game, int delta)
{
    game->speed_ms -= delta * SPEED_STEP_MS;
    if (game->speed_ms < SPEED_MIN_MS)
        game->speed_ms = SPEED_MIN_MS;
    if (game->speed_ms > SPEED_MAX_MS)
        game->speed_ms = SPEED_MAX_MS;
}

static void handle_key(Game *game, int key)
{
    if (key == 'a' || key == 'A')
        change_speed(game, 1);
    if (key == 'z' || key == 'Z')
        change_speed(game, -1);
}

void game_loop(Game *game)
{
    int key = ERR;

    init_screen();
    while (key != KEY_QUIT) {
        draw_field(game);
        update_field(game);
        timeout(game->speed_ms);
        key = getch();
        handle_key(game, key);
    }
    close_screen();
}
