#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <string.h>

struct {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
  int err;
  char earr[10000];
  char exp[10000];
  char line[10000];
} flags = {0};

void search_flags(int argc, char **argv);
void grep(char *name, int sum_files, char *pc);
void fflag(char *name);
void oflag(regmatch_t match, regex_t regex, int sum_files, char *name,
           int lines);
void ost(char *pc, int sovp_count, int sum_files, char *name);