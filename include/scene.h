#ifndef SCENE_H
#define SCENE_H

#include "sprite.h"

typedef struct scene {
    sprite_t** space;
    sprite_t** hud;
} scene_t;

void scene_init(scene_t* scene);
void scene_release(scene_t* scene);

#endif
