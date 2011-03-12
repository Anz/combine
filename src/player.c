#include "player.h"
#include "map.h"
#include "array.h"

void player_init(player_t* player, scene_t* scene, void* textures, int x, int y) {
    player->lifepoint = 100;
    sprite_ani_init(&player->sprite, 47, 67, map_get(textures, "player"));
    player->sprite.layer = 60;
    player->sprite.x = x;
    player->sprite.y = y;
    camera_init(&player->camera, x, 0, 480, 360);

    scene->space = array_add(scene->space, &player->sprite);
}

void player_move(player_t* player, int x) {
    player->sprite.x += x;
    player->camera.x += x;
    player->sprite.frame = ceil((sin(player->sprite.x) * 0.5 + 0.5f) * 8);
}

void player_release(player_t* player) {
    sprite_release(&player->sprite);
}

