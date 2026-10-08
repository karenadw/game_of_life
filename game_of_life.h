#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

#include <stdio.h>

#define WIDTH 80
#define HEIGHT 25

#define ALIVE 1
#define DEAD 0

#define CHAR_ALIVE '#'
#define CHAR_DEAD ' '

#define SPEED_MIN_MS 50
#define SPEED_MAX_MS 1000
#define SPEED_DEFAULT_MS 200

typedef struct {
    int field[HEIGHT][WIDTH];
    int generation;
    int alive_count;
    int speed_ms;
} Game;

void init_game(Game *game);
int load_field(Game *game, FILE *src);
void draw_field(const Game *game);
int count_neighbors(const Game *game, int row, int col);
void update_field(Game *game);
int count_alive(const Game *game);
int next_cell_state(int state, int neighbors);
void change_speed(Game *game, int delta);
void game_loop(Game *game);

#endif
