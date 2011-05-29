#include <stdio.h>
#include <stdbool.h>
#include <SDL/SDL.h>
#include <combine/combine.h>

int main(int argc, char* argv[]) {

    // create window
    int width =  480, height = 360;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_Surface* window = SDL_SetVideoMode(width, height, 24, SDL_OPENGL | SDL_GL_DOUBLEBUFFER);
    if (window == NULL) {
        perror("could not create window -- abort\n");
        return 0;
    }

    // create scene
    scene_t scene;
    scene_init(&scene);

    // create camera
    camera_t camera;
    camera_init(&camera, 0, 0, width, height);

    // load texture
    texture_t box_texture;
    texture_load(&box_texture, "../sample/box.png");

    // create sprite
    sprite_t box_sprite;
    sprite_init(&box_sprite, &box_texture);

    // add sprite to scene
    scene_space_add(&scene, &box_sprite);

    // main loop
    SDL_Event event;
    while (true) {

        // catch events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                // on quit clean up
                scene_release(&scene);
                texture_release(&box_texture);
                SDL_Quit();
                return 0;
            }
        }

        /* ... */

        // change sprite attributes
        /*
        box_sprite.x += 5; // move 5 pixel to right
        box_sprite.y += 5; // move 5 pixel to top
        box_sprite.layer += 5; // increase layer height
        box_sprite.rotation += 5; // rotate 5 degree to right
        box_sprite.transparency -= 0.01; // make it less visibile
        */

        // move camera
        /*
        camera.x += 5; // move camera 5 pixel to right
        camera.y += 5; // move camera 5 pixel to top
        */

        // redraw back buffer
        render(&scene, &camera);
        // flip buffer
        SDL_GL_SwapBuffers();
    }

    return 0;
}
