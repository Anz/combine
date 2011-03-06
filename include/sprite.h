#ifndef SPRITE_H
#define SPRITE_h

#include <GL/glew.h>
#include "texture.h"

typedef struct sprite {
    GLfloat x, y, rotation, layer;
    GLuint vertices;
    GLuint indices;
    texture_t* texture;
} sprite_t;

void sprite_init(sprite_t* sprite, texture_t* texture);
void sprite_release(sprite_t* sprite);

#endif
