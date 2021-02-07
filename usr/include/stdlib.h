// This is not part of v7. It's just required to play nice with
// modern (post 1980's) C -- robertl

#pragma once

#include <stddef.h>
__attribute__((noreturn)) void abort(void);
int atexit(void (*)(void));
__attribute__((noreturn)) void exit(int);

void *malloc(long unsigned int size);
void free(void *ptr);
void *calloc(long unsigned int count, long unsigned int size);
void *realloc(void *ptr, size_t size);
