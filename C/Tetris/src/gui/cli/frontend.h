#ifndef FRONTEND_H
#define FRONTEND_H

#include "../../brick_game/tetris/backend.h"

void game_field(GameInfo_t *game);
void game_object(GameInfo_t *game);
void print_field(GameInfo_t *game, UserState_t *state);
void print_info(GameInfo_t *game);
void start_message();
void pause_message();
void gg_message();

#endif