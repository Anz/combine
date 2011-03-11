#ifndef SPRITE_H
#define SPRITE_h

#include <GL/glew.h>
#include "texture.h"

typedef struct sprite {
    GLfloat x;
    GLfloat y;
    int width;
    int height;
    int frame;
    GLfloat rotation;
    GLfloat layer;
    GLfloat transparency;
    GLuint vertices;
    GLuint indices;
    texture_t* texture;
} sprite_t;

void sprite_init(sprite_t* sprite, texture_t* texture);
void sprite_ani_init(sprite_t* sprite, int width, int height, texture_t* texture);
void sprite_release(sprite_t* sprite);

#endif
