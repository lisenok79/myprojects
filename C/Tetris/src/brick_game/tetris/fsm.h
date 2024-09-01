#ifndef FSM_H
#define FSM_H

#include "backend.h"

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

typedef enum {
  START,
  SPAWN,
  MOVING,
  ROTATE,
  SHIFTING,
  COLLIDE,
  GG,
  EXIT,
  PAUSE
} UserState_t;

typedef struct {
  matrix_t field;
  matrix_t next;
  matrix_t current;
  int score;
  int score_tmp;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

void userInput(GameInfo_t *game, UserAction_t action, UserState_t *state);
void user_state(GameInfo_t *game, UserAction_t action, UserState_t *state);
UserAction_t get_action(int key);

#endif