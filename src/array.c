#include "array.h"
#include <stdlib.h>
#include <string.h>

static void set_count(void* array, int count) {
    *(int*)(array - sizeof(int)) = count;
}

static void* get_origin_addr(void* addr) {
    return addr - sizeof(int);
}

static void* get_array_addr(void* addr) {
    return addr + sizeof(int);
}

static void* increase(void* array) {
    int count = array_count(array) + 1;
    set_count(array, count);
    
    size_t size = count * sizeof(void*) + sizeof(int);
    void* origin = get_origin_addr(array);
    array = get_array_addr(realloc(origin, size));
    return array;
}

void* array_init() {
    void* array = get_array_addr(malloc(sizeof(int)));
    set_count(array, 0);
    return array;
}

void* array_add(void* array, void* item) {
    int index = array_count(array);

    array = increase(array);

    void* addr = array + sizeof(void*) * index;
    memcpy(addr, &item, sizeof(void*));

    return array;
}

int array_count(void* array) {
    return *(int*)(array - sizeof(int));
}

void array_release(void* array) {
    free(get_origin_addr(array));
}
