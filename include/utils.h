#pragma once

typedef enum { ERR, OK } Result;
#define MAXSTACKSIZE 100
#define VERBOSE true

void panic(const char *message);
int max(int a, int b);
