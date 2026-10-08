#include "game_of_life.h"

int main(void)
{
    Game game;

    init_game(&game);
    load_field(&game, stdin);
    game_loop(&game);
    return (0);
}
