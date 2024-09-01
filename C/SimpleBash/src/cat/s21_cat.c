#include "s21_cat.h"

int main(int argc, char **argv) {
  search_flags(argc, argv);
  // Вывод файла на экран
  if (!flags.err) {
    for (int i = optind; i < argc; i++) {
      print_file(argv[i]);
    }
  } else {
    printf("Ошибка ввода");
  }
  return 0;
}

// Функция поиска по флагам
void search_flags(int argc, char **argv) {
  int c;
  int opt_index = 0;
  static struct option long_options[] = {{"number-nonblank", 0, 0, 'b'},
                                         {"number", 0, 0, 'n'},
                                         {"squeeze-blank", 0, 0, 's'}};
  opterr = 0;

  while (flags.err == 0 && (c = getopt_long(argc, argv, "bnseEtTv",
                                            long_options, &opt_index)) != -1) {
    switch (c) {
      case 'n':
        flags.n = 1;
        break;
      case 'b':
        flags.b = 1;
        break;
      case 's':
        flags.s = 1;
        break;
      case 'e':
        flags.e = 1;
        flags.v = 1;
        break;
      case 'E':
        flags.e = 1;
        break;
      case 't':
        flags.t = 1;
        flags.v = 1;
        break;
      case 'T':
        flags.t = 1;
        break;
      case 'v':
        flags.v = 1;
        break;
      default:
        flags.err = 1;
    }
  }
  if (flags.b) flags.n = 0;
}

// Функция вывода текста файла на экран
void print_file(char *name) {
  FILE *file = fopen(name, "r");
  if (file) {
    int cnt = 1, empty = 0;
    char pr = '\n';
    while (!feof(file)) {
      int c = fgetc(file);
      if (c == EOF) break;
      // флаг s
      if (flags.s && c == '\n' && pr == '\n') {
        empty++;
        if (empty > 1) {
          continue;
        }
      } else {
        empty = 0;
      }
      // флаги n и b
      if (pr == '\n' && ((flags.b && c != '\n') || flags.n)) {
        printf("%6d\t", cnt);
        cnt++;
      }
      // флаг T
      if (c == '\t' && flags.t) {
        printf("^");
        c = 'I';
      }
      // флаг Е
      if (c == '\n' && flags.e) {
        (flags.b && pr == '\n') ? printf("      \t$") : printf("$");
      }
      // флаг v
      if (flags.v) {
        if (c > 127 && c < 160) {
          printf("M-^");
          c -= 64;
        } else if ((c < 32 && c != '\n' && c != '\t')) {
          printf("^");
          c += 64;
        } else if (c == 127) {
          printf("^");
          c -= 64;
        }
      }
      pr = c;
      putc(c, stdout);
    }
  } else {
    fprintf(stderr, "No such file or directory\n");
  }
  fclose(file);
}