#include "scene.h"
#include "array.h"

void scene_init(scene_t* scene) {
    scene->space = array_init();
    scene->hud = array_init();
}

void scene_release(scene_t* scene) {
    array_release(scene->space);
    array_release(scene->hud);
}

void scene_space_add(scene_t* scene, sprite_t* sprite) {
    scene->space = array_add(scene->space, sprite);
}

void scene_hud_add(scene_t* scene, sprite_t* sprite) {
    scene->hud = array_add(scene->hud, sprite);
}
