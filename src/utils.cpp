#include "utils.h"
#include <cstdio>
#include <signal.h>

void panic(const char *message) {
  printf("ERROR: %s\n", message);
  raise(SIGABRT);
}