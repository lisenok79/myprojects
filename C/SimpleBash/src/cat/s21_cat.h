#include <getopt.h>
#include <stdio.h>

struct {
  int b;
  int n;
  int s;
  int e;
  int t;
  int v;
  int err;
} flags = {0};

void search_flags(int argc, char **argv);
void print_file(char *name);