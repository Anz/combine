#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <SDL/SDL.h>
#include "render.h"
#include "array.h"
#include "map.h"
#include "texture_loader.h"
#include "scene.h"
#include "player.h"

int main(int argc, char* argv[]) {
    printf("hello combine\n");

    SDL_Surface* window;
    SDL_Event event;
    bool running = true;

    // create window
    int width =  480, height = 360;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    window = SDL_SetVideoMode(width, height, 24, SDL_OPENGL | SDL_GL_DOUBLEBUFFER);

    // init render
    render_init();

    // load all textures
    void* textures = textures_load("img");

    // scene
    scene_t scene;
    scene_init(&scene);

    sprite_t draft;
    sprite_init(&draft, map_get(textures, "draft"));
    draft.layer = 60;

    sprite_t hud;
    sprite_init(&hud, map_get(textures, "draft"));
    hud.x = (hud.texture->width - width) / 2.0f;
    hud.y = (height - hud.texture->height) / 2.0f;

    // player
    player_t player;
    player_init(&player, &scene, textures, -50, -40);

    scene.space = array_add(scene.space, &draft);

    scene.hud = array_add(scene.hud, &hud);

    level_load(&scene, textures, "cave.lvl");

    float counter = 0;

    int speed = 0;

    // main
    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: running = false; break;
                case SDL_KEYUP:
                case SDL_KEYDOWN: {
                    switch(event.key.keysym.sym) {
                        case SDLK_a: { if (speed == -1) { speed = 0; } else { speed = -1; }  break; }
                        case SDLK_d: { if (speed == 1) { speed = 0; } else { speed = 1; } break; }
                        default: break;
                    }
                }
            }
        }

        player_move(&player, speed * 2);

        if (running) {
            render(&scene, &player.camera);
            SDL_GL_SwapBuffers();
        }
        draft.rotation += 0.5f;
        draft.transparency = sin(counter) / 2.0f + 0.5f;

        counter += 0.05f;
    }

    // clean up
    scene_release(&scene);
    textures_release(textures);
    SDL_Quit();

    return 0;
}
