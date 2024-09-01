#include "s21_grep.h"

int main(int argc, char **argv) {
  char c = '\n';
  char *pc = &c;
  search_flags(argc, argv);
  int e = 1;
  if (flags.e) e = 0;
  int sum_files = argc - (optind + e);
  if (flags.f && !flags.e) {
    fflag(argv[optind]);
  } else if (!flags.e) {
    strcat(flags.exp, argv[optind]);
  }
  if (!flags.err) {
    for (int i = optind + e; i < argc; i++) {
      grep(argv[i], sum_files, pc);
    }
  } else {
    printf("Error flag\n");
  }
  return 0;
}

// Проверка флагов
void search_flags(int argc, char **argv) {
  int c;
  opterr = 0;
  while (flags.err == 0 && (c = getopt(argc, argv, "ne:viclhsfo")) != -1) {
    switch (c) {
      case 'n':
        flags.n = 1;
        break;
      case 'e':
        flags.e = 1;
        strcat(flags.earr, optarg);
        strcat(flags.earr, "|");
        break;
      case 'v':
        flags.v = 1;
        flags.o = 0;
        break;
      case 'i':
        flags.i = 1;
        break;
      case 'c':
        flags.c = 1;
        break;
      case 'l':
        flags.l = 1;
        break;
      case 'h':
        flags.h = 1;
        break;
      case 's':
        flags.s = 1;
        break;
      case 'f':
        flags.f = 1;
        break;
      case 'o':
        flags.o = 1;
        break;
      default:
        flags.err = 1;
    }
  }
  if (flags.e) {
    flags.earr[strlen(flags.earr) - 1] = '\0';
  }
}

// Основная функция грепа
void grep(char *name, int sum_files, char *pc) {
  regex_t regex;
  regmatch_t match;
  int reti, sovp;
  int sovp_count = 0, lines = 1;
  int f = REG_EXTENDED;
  if (flags.i) {
    f = REG_EXTENDED | REG_ICASE;
  }
  FILE *file = fopen(name, "r");
  if (file) {
    while (fgets(flags.line, 10000, file) != NULL) {
      if (flags.e) {
        reti = regcomp(&regex, flags.earr, f);
      } else {
        reti = regcomp(&regex, flags.exp, f);
      }
      if (reti) {
        fprintf(stderr, "oshibka\n");
      }
      sovp = regexec(&regex, flags.line, 1, &match, 0);
      if ((!sovp && !flags.v) || (sovp && flags.v)) {
        if (flags.line[0] != '\n') sovp_count++;
        if (flags.c || flags.l) {
          regfree(&regex);
          continue;
        }
        if (sum_files > 1 && !flags.h) {
          printf("%s:", name);
        }
        if (flags.n) {
          printf("%d:", lines);
        }
        if (flags.o) {
          oflag(match, regex, sum_files, name, lines);
        } else {
          printf("%s", flags.line);
          *pc = flags.line[strlen(flags.line) - 1];
        }
      }
      lines++;
      regfree(&regex);
    }
    ost(pc, sovp_count, sum_files, name);
  } else if (!flags.s) {
    fprintf(stderr, "No such file or directory\n");
  }
  fclose(file);
}

// Флаг f
void fflag(char *name) {
  FILE *file = fopen(name, "r");
  if (file) {
    fgets(flags.exp, 10000, file);
  } else {
    printf("No such file or directory\n");
  }
  fclose(file);
}

// Флаг o
void oflag(regmatch_t match, regex_t regex, int sum_files, char *name,
           int lines) {
  printf("%.*s\n", (int)(match.rm_eo - match.rm_so), flags.line + match.rm_so);
  char *rem = flags.line + match.rm_eo;
  while (!regexec(&regex, rem, 1, &match, 0)) {
    if (sum_files > 1 && !flags.h) {
      printf("%s:", name);
    }
    if (flags.n) {
      printf("%d:", lines);
    }
    printf("%.*s\n", (int)(match.rm_eo - match.rm_so), rem + match.rm_so);
    rem = rem + match.rm_eo;
  }
}

// Остальные проверки
void ost(char *pc, int sovp_count, int sum_files, char *name) {
  if (*pc != '\n' && sovp_count != 0) {
    printf("\n");
  }
  if (flags.c && sum_files == 1) {
    printf("%d\n", sovp_count);
  } else if (flags.c && sum_files > 1) {
    printf("%s:%d\n", name, sovp_count);
  }
  if (sovp_count > 0 && flags.l) {
    printf("%s\n", name);
  }
}