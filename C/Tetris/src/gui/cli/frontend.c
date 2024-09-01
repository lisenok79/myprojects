#include "frontend.h"

void game_field(GameInfo_t *game) {
  FILE *file = fopen("models/7.txt", "r");
  s21_create_matrix(HEIGHT + 2, WIDTH + 2, &game->field);
  for (int i = 0; i < game->field.rows; i++) {
    for (int j = 0; j < game->field.columns; j++) {
      fscanf(file, "%lf", &game->field.matrix[i][j]);
    }
  }
  fclose(file);
}

void game_object(GameInfo_t *game) {
  char filename[70] = {0};
  int a = RANDOM_FIGURE();
  sprintf(filename, "models/%d.txt", a);
  FILE *file = fopen(filename, "r");
  s21_create_matrix(HEIGHT + 2, WIDTH + 2, &game->next);

  for (int i = 0; i < game->next.rows; i++) {
    for (int j = 0; j < game->next.columns; j++) {
      fscanf(file, "%lf", &game->next.matrix[i][j]);
    }
  }
  fclose(file);
}

void print_field(GameInfo_t *game, UserState_t *state) {
  matrix_t result = {0};
  if (*state == SPAWN || *state == GG) {
    s21_create_matrix(HEIGHT + 2, WIDTH + 2, &result);
    s21_copy_matrix(&game->field, &result);
  } else
    s21_sum_matrix(&game->field, &game->current, &result);
  for (int i = 0; i < game->field.rows; i++) {
    for (int j = 0; j < game->field.columns; j++) {
      if (result.matrix[i][j] >= 9) addch('#');
      if (result.matrix[i][j] == 0)
        addch(' ');
      else if (result.matrix[i][j] == 1)
        addch('*');
    }
    addch('\n');
  }
  if (*state != START) print_info(game);
  if (*state == START) start_message();
  if (*state == GG) gg_message();
  if (*state == PAUSE) pause_message();
  s21_remove_matrix(&result);
}

void print_info(GameInfo_t *game) {
  mvprintw(0, 16, "SCORE: %d", game->score);
  mvprintw(3, 16, "HIGH SCORE: %d", game->high_score);
  mvprintw(6, 16, "NEXT:");
  mvprintw(14, 16, "LEVEL: %d", game->level);
  refresh();
  for (int i = 0; i < game->next.rows; i++) {
    for (int j = 0; j < game->next.columns; j++) {
      if (game->next.matrix[i][j] == 1) {
        mvaddch(i + 8, j + 12, '*');
        refresh();
      }
    }
  }
}

void start_message() {
  WINDOW *win = newwin(4, 15, 7, 7);
  wmove(win, 13, 13);
  wprintw(win, "\n  Press ENTER\n   to START");
  refresh();
  wborder(win, 0, 0, 0, 0, 0, 0, 0, 0);
  wrefresh(win);
  delwin(win);
}

void pause_message() {
  WINDOW *win = newwin(6, 15, 7, 7);
  wmove(win, 13, 13);
  wprintw(win, "\n   Press \"P\"\n  to CONTINUE\n   or ENTER\n   to RETRY");
  refresh();
  wborder(win, 0, 0, 0, 0, 0, 0, 0, 0);
  wrefresh(win);
  delwin(win);
}

void gg_message() {
  WINDOW *win = newwin(5, 26, 7, 7);
  wmove(win, 13, 13);
  wprintw(win,
          "\n       GAME OVER!\n  Press ENTER to RETRY\n     or ESC to QUIT");
  refresh();
  wborder(win, 0, 0, 0, 0, 0, 0, 0, 0);
  wrefresh(win);
  delwin(win);
}