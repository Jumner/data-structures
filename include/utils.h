#pragma once

typedef enum { ERR, OK } Result;
#define MAXSTACKSIZE 100
#define VERBOSE false

void panic(const char *message);
