#pragma once

typedef enum { ERR, OK } Result;
#define MAXSTACKSIZE 100

void panic(const char *message);
