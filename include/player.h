#ifndef PLAYER_H
#define PLAYER_H

#include "sprite.h"
#include "camera.h"
#include "scene.h"

typedef struct player {
    int lifepoint;
    sprite_t sprite;
    camera_t camera;
} player_t;


void player_init(player_t* player, scene_t* scene, void* textures, int x, int y);
void player_move(player_t* player, int x);
void player_release(player_t* player);

#endif
