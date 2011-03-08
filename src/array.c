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

void array_swap(void* array, int a, int b) {
    int** rarray = array;
    int* tmp = rarray[a];
    rarray[a] = rarray[b];
    rarray[b] = tmp;
}

void array_sort(void* array, bool (*compare)(void*, void*)) {
    int count = array_count(array);
    int** rarray = array;

    /*bool unsorted = true;

    while (unsorted) {
        unsorted = false;

        void* first = rarray[0];
        for (int i = 1; i < count; i++) {
            void* element = rarray[i];

            if (compare(first, element)) {
                array_swap(array, 0, i);
                unsorted = true;
                break;
            }
        }
    }*/

    for (int i = 0; i < count; i++) {
        void* smallest = rarray[i];

        for (int j = i; j < count; j++) {
            void* tocompare = rarray[j];
            if (compare(smallest, tocompare)) {
                array_swap(array, i, j);
                smallest = tocompare;
            }
        }
    }

}
