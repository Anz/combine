#ifndef SCENE_H
#define SCENE_H

#include "sprite.h"

typedef struct scene {
    sprite_t** space;
    sprite_t** hud;
} scene_t;

void scene_init(scene_t* scene);
void scene_release(scene_t* scene);
void scene_space_add(scene_t* scene, sprite_t* sprite);
void scene_hud_add(scene_t* scene, sprite_t* sprite);

#endif
