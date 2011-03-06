#include <stdio.h>
#include <stdbool.h>
#include <dirent.h>
#include <SDL/SDL.h>
#include "render.h"
#include "array.h"
#include "map.h"
#include "texture_loader.h"

int main(int argc, char* argv[]) {
    printf("hello combine\n");

    SDL_Surface* window;
    SDL_Event event;
    bool running = true;

    // create window
    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    window = SDL_SetVideoMode(480, 360, 24, SDL_OPENGL | SDL_GL_DOUBLEBUFFER);

    // init render
    render_init();

    void* textures = textures_load("img");

    sprite_t draft;
    sprite_init(&draft, map_get(textures, "draft"));

    sprite_t crap;
    sprite_init(&crap, map_get(textures, "crap"));

    sprite_t** sprites = array_init();
    sprites = array_add(sprites, &crap);
    sprites = array_add(sprites, &draft);

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
        draft.y += 0.5f;
        crap.x += 0.5f;
    }

    // clean up
    textures_release(textures);
    SDL_Quit();

    return 0;
}
