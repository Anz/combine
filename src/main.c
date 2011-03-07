#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <SDL/SDL.h>
#include "render.h"
#include "array.h"
#include "map.h"
#include "texture_loader.h"
#include "scene.h"

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

    // load all textures
    void* textures = textures_load("img");

    // scene
    scene_t scene;
    scene_init(&scene);

    sprite_t draft;
    sprite_init(&draft, map_get(textures, "draft"));

    sprite_t crap;
    sprite_init(&crap, map_get(textures, "crap"));

    sprite_t hud;
    sprite_init(&hud, map_get(textures, "draft"));
    hud.x = - 480.0f / 2.0f;
    hud.y = 360.0f / 2.0f;

    scene.space = array_add(scene.space, &crap);
    scene.space = array_add(scene.space, &draft);

    scene.hud = array_add(scene.hud, &hud);

    level_load(&scene, textures, "cave.lvl");

    float counter = 0;

    // main
    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: running = false; break;
            }
        }

        if (running) {
            render(&scene);
            SDL_GL_SwapBuffers();
        }
        draft.rotation += 0.5f;
        draft.transparency = sin(counter) / 2.0f + 0.5f;
        crap.x += 0.5f;

        counter += 0.05f;
        //scene.camera.x = sin(counter) * 20.0f;
        scene.camera.x = counter * 50.0f;
        scene.camera.y = cos(counter) * 20.0f;
    }

    // clean up
    scene_release(&scene);
    textures_release(textures);
    SDL_Quit();

    return 0;
}
