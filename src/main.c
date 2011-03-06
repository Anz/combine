#include <stdio.h>
#include <stdbool.h>
#include <dirent.h>
#include <SDL/SDL.h>
#include "render.h"
#include "array.h"
#include "map.h"

void* load_texture(char* path) {
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
            printf("image: '%s'\n", name);
            texture_t* texture = malloc(sizeof(texture_t));
            texture_load(texture, name);
            map = map_set(map, name, texture);
        }
        
    }

    return map;
}

int main(int argc, char* argv[]) {
    printf("hello combine\n");

    SDL_Surface* window;
    SDL_Event event;
    bool running = true;

    // create window
    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    window = SDL_SetVideoMode(480, 360, 24, SDL_OPENGL | SDL_GL_DOUBLEBUFFER);


    /*DIR* imgdir = opendir("img");
    struct dirent* file;
    while ((file = readdir(imgdir)) != NULL) {
        printf("file: %s\n", file->d_name);
    }*/

    // init render
    render_init();

    void* textures = load_texture("img");

    texture_t texture;
    texture_load(&texture, "draft.png");

    texture_t texture2;
    texture_load(&texture2, "crap.png");

    sprite_t sprite;
    sprite_init(&sprite, &texture);

    sprite_t sprite3;
    sprite_init(&sprite3, &texture2);

    sprite_t** sprites = array_init();
    sprites = array_add(sprites, &sprite3);
    sprites = array_add(sprites, &sprite);

    // main
    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: running = false; break;
            }
        }

        if (running) {
            render(sprites);
            SDL_GL_SwapBuffers();
        }
    }

    // clean up
    texture_release(&texture);
    texture_release(&texture2);
    SDL_Quit();

    return 0;
}
