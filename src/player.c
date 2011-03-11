#include "player.h"
#include "map.h"
#include "array.h"

void player_init(player_t* player, scene_t* scene, void* textures, int x, int y) {
    player->lifepoint = 100;
    sprite_init(&player->sprite, map_get(textures, "player"));
    player->sprite.layer = 60;
    player->sprite.x = x;
    player->sprite.y = y;
    player->camera.x = x;
    player->camera.y = y;

    scene->space = array_add(scene->space, &player->sprite);
}

void player_move(player_t* player, int x) {
    player->sprite.x += x;
    player->camera.x += x;
}

void player_release(player_t* player) {
    sprite_release(&player->sprite);
}

