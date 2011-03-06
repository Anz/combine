#include "map.h"
#include "array.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct entry {
    char key[80];
    void* value;
} entry_t;

void* map_init() {
    return array_init();
}

void map_release(void* map) {
    for (int i = 0; i < array_count(map); i++) {
        entry_t* entry = ((entry_t**)map)[i];
        free(entry);
    }

    array_release(map);
}

void* map_set(void* map, char* key, void* value) {
    entry_t* entry = map_get(map, key);

    if (entry) {
        entry->value = value;
    } else {
        entry = malloc(sizeof(entry_t));
        strcpy(entry->key, key);
        entry->value = value;
        map = array_add(map, entry);
    }
    return map;
}

void* map_get(void* map, char* key) {
    for (int i = 0; i < array_count(map); i++) {
        entry_t* entry = ((entry_t**)map)[i];
        if (strcmp(key, entry->key) == 0) {
            return entry->value;
        }
    }
    return NULL;
}

char** map_keys(void* map) {
    char** keys = array_init();
    for (int i = 0; i < array_count(map); i++) {
        entry_t* entry = ((entry_t**)map)[i];
        keys = array_add(keys, entry->key);
    }
    return keys;
}
