#include "scene.h"
#include "array.h"

void scene_init(scene_t* scene) {
    scene->camera.x = 0.0f;
    scene->camera.y = 0.0f;
    scene->space = array_init();
    scene->hud = array_init();
}

void scene_release(scene_t* scene) {
    array_release(scene->space);
    array_release(scene->hud);
}
