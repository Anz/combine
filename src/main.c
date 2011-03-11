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
    draft.layer = 60;

    sprite_t frame;
    sprite_ani_init(&frame, 50, 50, map_get(textures, "frame"));
    frame.layer = 80;

    sprite_t crap;
    sprite_init(&crap, map_get(textures, "crap"));
    crap.layer = 50;

    sprite_t hud;
    sprite_init(&hud, map_get(textures, "draft"));
    hud.x = - 480.0f / 2.0f;
    hud.y = 360.0f / 2.0f;

    // player
    player_t player;
    player_init(&player, &scene, textures, -50, 0);

    scene.space = array_add(scene.space, &crap);
    scene.space = array_add(scene.space, &draft);
    scene.space = array_add(scene.space, &frame);

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
            render(&scene, &player.camera);
            SDL_GL_SwapBuffers();
        }
        draft.rotation += 0.5f;
        draft.transparency = sin(counter) / 2.0f + 0.5f;
        crap.x += 0.5f;
        crap.layer = (sin(counter) * 0.5f + 0.5f) * 65.0f;

        counter += 0.05f;
        //scene.camera.x = sin(counter) * 20.0f;
        player_move(&player, 1);
        player.camera.y = cos(counter) * 20.0f;
        
        frame.frame = ceil((sin(counter) * 0.5f + 0.5f) * 25);
        //printf("frame: %i\n", frame.frame);
    }

    // clean up
    scene_release(&scene);
    textures_release(textures);
    SDL_Quit();

    return 0;
}
