#include "backend.h"

int main() {
    GameInfo_t game = {0};
    UserState_t state = START;
    UserAction_t act = 0;
    struct timeval tv;
    game.score = 0;
    game.level = 1;
    game.speed = 600;
    gettimeofday(&tv, NULL);
    srand(tv.tv_usec * tv.tv_sec);
    initscr();
    curs_set(0);
    noecho();
    nodelay(stdscr, 1);
    keypad(stdscr, 1);
    timeout(game.speed);
    game_loop(&game, &state, act);
    s21_remove_matrix(&game.current);
    s21_remove_matrix(&game.field);
    s21_remove_matrix(&game.next);
    endwin();
    
    return 0;
}

void game_loop(GameInfo_t *game, UserState_t *state, UserAction_t act) {
    read_high_score(game);
        
    while (*state != EXIT) {
        timeout(game->speed);
        act = get_action(getch());
        userInput(game, act, state);
        clear();
        print_field(game, state);
    }
}