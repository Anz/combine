#ifndef ARRAY_H
#define ARRAY_H

#include <stdbool.h>

void* array_init();
void* array_add(void* array, void* item);
int array_count(void* array);
void array_release(void* array);
void array_swap(void* array, int a, int b);
void array_sort(void* array, bool (*compare)(void*, void*));

#endif
