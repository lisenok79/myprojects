#ifndef BACKEND_H
#define BACKEND_H

#include <math.h>
#include <ncurses.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#include "fsm.h"
#include "../../gui/cli/frontend.h"
#include "defines.h"

void game_loop(GameInfo_t *game, UserState_t *state, UserAction_t act);
void next_in_current(GameInfo_t *game);
int move_down(GameInfo_t *game);
void move_left(GameInfo_t *game);
void move_right(GameInfo_t *game);
int check_field(GameInfo_t *game, matrix_t *object);
void sum_field(GameInfo_t *game);
int game_over(GameInfo_t *game, UserState_t *state);
void rotation(GameInfo_t *game);
void center_mass(GameInfo_t *game, int *i, int *j);
void drop_figure(GameInfo_t *game);
void delete_row(GameInfo_t *game);
void del(GameInfo_t *game, int i);
void new_high_score(GameInfo_t *game);
void read_high_score(GameInfo_t *game);
void pause_action(GameInfo_t *game, UserAction_t action, UserState_t *state);
void score_speed(GameInfo_t *game, int count);
// void fall_timer(GameInfo_t *game, UserState_t *state, clock_t *time_fall);

// MATRIX
int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_correct_matrix(matrix_t *A);
void s21_copy_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

#endif