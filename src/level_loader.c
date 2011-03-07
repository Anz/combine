#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "level_loader.h"
#include "map.h"
#include "array.h"

#define READ_BUFFER 512

static void* generate_level_elements();
static void add_default(scene_t* scene, void* textures, char* name, int x, int y, int layer);
static void add_draft(scene_t* scene, void* textures, int x, int y, int layer);

void level_load(scene_t* scene, void* textures, char* path) {
    FILE* level = fopen(path, "r");
    if (!level) {
        fprintf(stderr, "cannot load file '%s'\n", path);
        return;
    }

    void* level_elements = generate_level_elements();

    char buffer[READ_BUFFER];
    char* seperator = " \t\r\n";
    while (!feof(level)) {
        memset(buffer, 0, READ_BUFFER);
        fgets(buffer, READ_BUFFER, level);

        char* name = strtok(buffer, seperator);
        if (!name) {
            continue;
        }
        int x = atoi(strtok(NULL, seperator));
        int y = atoi(strtok(NULL, seperator));
        int layer = atoi(strtok(NULL, seperator));

        void (*func)(scene_t*, void*, int, int, int) = map_get(level_elements, name);

        if (func) {
            func(scene, textures, x, y, layer);
       } else {
            add_default(scene, textures, name, x, y, layer);
       } 
    }

    map_release(level_elements);
}

static void* generate_level_elements() {
    void* map = map_init();
    map = map_set(map, "draft", &add_draft);
    return map;
}


static void add_default(scene_t* scene, void* textures, char* name, int x, int y, int layer) {
    sprite_t* sprite = malloc(sizeof(sprite_t));
    sprite_init(sprite, map_get(textures, name));
    sprite->x = x;
    sprite->y = y;
    sprite->layer = layer;

    scene->space = array_add(scene->space, sprite);
}

static void add_draft(scene_t* scene, void* textures, int x, int y, int layer) {
    sprite_t* draft = malloc(sizeof(sprite_t));
    sprite_init(draft, map_get(textures, "draft"));
    draft->x = x;
    draft->y = y;
    draft->layer = layer;

    scene->space = array_add(scene->space, draft);
}
