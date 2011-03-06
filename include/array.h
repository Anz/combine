#ifndef ARRAY_H
#define ARRAY_H

void* array_init();
void* array_add(void* array, void* item);
int array_count(void* array);
void array_release(void* array);

#endif
