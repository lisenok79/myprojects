#include "backend.h"

void next_in_current(GameInfo_t *game) {
  s21_create_matrix(game->next.rows, game->next.columns, &game->current);
  s21_copy_matrix(&game->next, &game->current);
}

int move_down(GameInfo_t *game) {
  int err = 1;
  matrix_t temp = {0};
  s21_create_matrix(game->field.rows, game->field.columns, &temp);
  s21_copy_matrix(&game->current, &temp);
  for (int i = HEIGHT + 1; i > 0; i--) {
    for (int j = WIDTH + 1; j > 0; j--) {
      if (temp.matrix[i - 1][j] == 1) {
        temp.matrix[i][j] = 1;
        temp.matrix[i - 1][j] = 0;
      }
    }
  }
  if (!check_field(game, &temp))
    s21_copy_matrix(&temp, &game->current);
  else
    err = 0;
  s21_remove_matrix(&temp);
  return err;
}

void move_left(GameInfo_t *game) {
  matrix_t temp = {0};
  s21_create_matrix(game->field.rows, game->field.columns, &temp);
  s21_copy_matrix(&game->current, &temp);
  for (int i = HEIGHT + 1; i > 0; i--) {
    for (int j = 1; j < WIDTH + 2; j++) {
      if (temp.matrix[i][j] == 1) {
        temp.matrix[i][j - 1] = 1;
        temp.matrix[i][j] = 0;
      }
    }
  }
  if (!check_field(game, &temp)) s21_copy_matrix(&temp, &game->current);
  s21_remove_matrix(&temp);
}

void move_right(GameInfo_t *game) {
  matrix_t temp = {0};
  s21_create_matrix(game->field.rows, game->field.columns, &temp);
  s21_copy_matrix(&game->current, &temp);
  for (int i = HEIGHT + 1; i > 0; i--) {
    for (int j = WIDTH + 1; j > 0; j--) {
      if (temp.matrix[i][j] == 1) {
        temp.matrix[i][j + 1] = 1;
        temp.matrix[i][j] = 0;
      }
    }
  }
  if (!check_field(game, &temp)) s21_copy_matrix(&temp, &game->current);
  s21_remove_matrix(&temp);
}

int check_field(GameInfo_t *game, matrix_t *object) {
  matrix_t check = {0};
  int err = 0;
  s21_sum_matrix(object, &game->field, &check);
  for (int i = HEIGHT + 1; i >= 0; i--) {
    if (err) break;
    for (int j = WIDTH + 1; j >= 0; j--) {
      if (check.matrix[i][j] == 10 || check.matrix[i][j] == 2) {
        err = 1;
        break;
      }
    }
  }
  s21_remove_matrix(&check);
  return err;
}

void rotation(GameInfo_t *game) {
  int Xc = 0;
  int Yc = 0;
  matrix_t temp = {0};
  s21_create_matrix(game->field.rows, game->field.columns, &temp);
  center_mass(game, &Yc, &Xc);
  for (int i = 0; i < HEIGHT + 1; i++) {
    for (int j = 0; j < WIDTH + 1; j++) {
      if (game->current.matrix[i][j] == 1)
        temp.matrix[Yc - (j - Xc)][Xc + (i - Yc)] = game->current.matrix[i][j];
    }
  }
  if (!check_field(game, &temp)) s21_copy_matrix(&temp, &game->current);
  s21_remove_matrix(&temp);
}

void center_mass(GameInfo_t *game, int *i, int *j) {
  double x = 0;
  double y = 0;
  for (int k = 0; k < HEIGHT + 2; k++) {
    for (int n = 0; n < WIDTH + 2; n++) {
      x += k * game->current.matrix[k][n];
      y += n * game->current.matrix[k][n];
    }
  }
  *i = (int)round(x / 4);
  *j = (int)round(y / 4);
}

void sum_field(GameInfo_t *game) {
  matrix_t temp = {0};
  s21_create_matrix(game->field.rows, game->field.columns, &temp);
  s21_sum_matrix(&game->field, &game->current, &temp);
  s21_copy_matrix(&temp, &game->field);
  s21_remove_matrix(&temp);
}

int game_over(GameInfo_t *game, UserState_t *state) {
  int err = 0;
  if (game->field.matrix != NULL) {
    for (int j = 1; j < WIDTH + 1; j++) {
      if (game->field.matrix[1][j] == 1) {
        *state = GG;
        err = 1;
        break;
      }
    }
  }
  return err;
}

void drop_figure(GameInfo_t *game) {
  while (move_down(game))
    ;
}

void delete_row(GameInfo_t *game) {
  int flag = 0;
  int count = 0;
  for (int i = HEIGHT; i > 0; i--) {
    flag = 0;
    for (int j = WIDTH; j > 0; j--) {
      if (game->field.matrix[i][j] == 0) {
        flag = 1;
        break;
      }
    }
    if (!flag) {
      del(game, i);
      i = HEIGHT + 1;
      count++;
    }
  }
  score_speed(game, count);
}

void del(GameInfo_t *game, int row) {
  for (int i = row; i > 1; i--) {
    for (int j = WIDTH; j > 0; j--) {
      game->field.matrix[i][j] = game->field.matrix[i - 1][j];
    }
  }
}

void score_speed(GameInfo_t *game, int count) {
  if (count == 1)
    game->score += 100;
  else if (count == 2)
    game->score += 300;
  else if (count == 3)
    game->score += 700;
  else if (count == 4)
    game->score += 1500;
  if (game->score > game->high_score) {
    game->high_score = game->score;
    new_high_score(game);
  }
  if (game->level < 11) {
    if (game->score / 600 >= game->level) {
      game->level += 1;
      game->speed -= 50;
    }
  }
}

void new_high_score(GameInfo_t *game) {
  FILE *file = fopen("HIGH SCORE.txt", "w");
  fprintf(file, "%d", game->score);
  fclose(file);
}

void read_high_score(GameInfo_t *game) {
  char hscore[100] = {0};
  FILE *file = fopen("HIGH SCORE.txt", "r");
  if (file != NULL) {
    fgets(hscore, 99, file);
    sscanf(hscore, "%d", &game->high_score);
    fclose(file);
  } else {
    fclose(file);
    file = fopen("HIGH SCORE.txt", "w");
    game->high_score = 0;
    fclose(file);
  }
}

void pause_action(GameInfo_t *game, UserAction_t action, UserState_t *state) {
  while (*state == PAUSE) {
    userInput(game, action, state);
  }
}

// FSM -------------------------------
UserAction_t get_action(int key) {
  UserAction_t action = -1;
  switch (key) {
    case 10:
      action = Start;
      break;
    case 'P':
    case 'p':
      action = Pause;
      break;
    case 27:
      action = Terminate;
      break;
    case KEY_LEFT:
      action = Left;
      break;
    case KEY_RIGHT:
      action = Right;
      break;
    case KEY_UP:
      action = Up;
      break;
    case KEY_DOWN:
    case ERR:
      action = Down;
      break;
    case 32:
      action = Action;
      break;
  }
  return action;
}

void userInput(GameInfo_t *game, UserAction_t action, UserState_t *state) {
  if (*state == START || *state == GG || *state == PAUSE) {
    if (action == Start) {
      game_field(game);
      game_object(game);
      game->score = 0;
      game->level = 1;
      *state = SPAWN;
    } else if (action == Pause)
      *state = MOVING;
  } else if (*state == COLLIDE) {
    sum_field(game);
    delete_row(game);
    next_in_current(game);
    *state = SPAWN;
    game_over(game, state);
  } else if (*state == MOVING || *state == SHIFTING || *state == ROTATE) {
    user_state(game, action, state);
  }
  if (action == Terminate) {
    *state = EXIT;
  }
  if (*state == SPAWN) {
    next_in_current(game);
    game_object(game);
    *state = MOVING;
  }
}

void user_state(GameInfo_t *game, UserAction_t action, UserState_t *state) {
  switch (action) {
    case Down:
      if (move_down(game))
        *state = MOVING;
      else
        *state = COLLIDE;
      if (game_over(game, state)) *state = GG;
      break;
    case Left:
      move_left(game);
      *state = SHIFTING;
      break;
    case Right:
      move_right(game);
      *state = SHIFTING;
      break;
    case Action:
      rotation(game);
      *state = ROTATE;
      break;
    case Up:
      drop_figure(game);
      *state = COLLIDE;
      break;
    case Pause:
      pause_action(game, action, state);
      *state = PAUSE;
      break;
    case Terminate:
      *state = EXIT;
      break;
    case Start:
      break;
  }
}
// ---------------------------------------

// MATRIX -----------------------------------
int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int err = 0;
  if (rows < 1 || columns < 1) err = 1;
  if (!err) {
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double **)calloc(rows, sizeof(double *));
    for (int i = 0; i < rows; i++) {
      result->matrix[i] = (double *)calloc(columns, sizeof(double));
    }
  }
  return err;
}

void s21_copy_matrix(matrix_t *A, matrix_t *B) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      B->matrix[i][j] = A->matrix[i][j];
    }
  }
}

void s21_remove_matrix(matrix_t *A) {
  if (A != NULL) {
    if (A->matrix != NULL) {
      for (int i = 0; i < A->rows; i++) free(A->matrix[i]);
      free(A->matrix);
    }
    A->matrix = NULL;
    A->rows = 0;
    A->columns = 0;
  }
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int err = 0;
  if (!s21_correct_matrix(A) || !s21_correct_matrix(B)) {
    err = 1;
  } else if (B->rows != A->rows || B->columns != A->columns) {
    err = 2;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  }
  return err;
}

int s21_correct_matrix(matrix_t *A) {
  int err = 1;
  if (A == NULL || A->matrix == NULL || A->rows < 1 || A->columns < 1) {
    err = 0;
  }
  return err;
}
// -------------------------------

// void fall_timer(GameInfo_t *game, UserState_t *state, clock_t *time_fall) {
//     if (game->field.matrix != NULL && game->current.matrix) {
//         if (*state != PAUSE && *state != GG && clock() > *time_fall + 1000 *
//         (765 - game->level * 65)) {
//             *time_fall = clock();
//             if (!move_down(game) && *state != GG) *state = COLLIDE;
//             if (game_over(game, state)) *state = GG;
//         }
//     }
//     clear();
//     print_field(game, state);
// }