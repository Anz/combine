#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "texture_loader.h"
#include "array.h"
#include "map.h"
#include "texture.h"

void* textures_load(char* path) {
    void* map = map_init();

    chdir(path);
    DIR* dir = opendir(".");
    if (!dir) {
        fprintf(stderr, "cannot open dir: %s\n", path);
        return map;
    }

    struct dirent* file;
    while ((file = readdir(dir)) != NULL) {
        char* name = file->d_name;
        size_t length = strlen(name);
        if (length > 4 && strcmp(".png", &name[length - 4]) == 0) {
            char file_path[80];
            strcat(file_path, path);
            texture_t* texture = malloc(sizeof(texture_t));
            texture_load(texture, name);
            map = map_set(map, strtok(name, "."), texture);
        }
        
    }

    return map;
}

void textures_release(void* textures) {
    char** keys = map_keys(textures);
    for (int i = 0; i < array_count(keys); i++) {
        char* key = keys[i];
        texture_t* texture = map_get(textures, key);
        free(texture);
    }
    array_release(keys);
}
