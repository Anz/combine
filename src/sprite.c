#include "sprite.h"

void sprite_init(sprite_t* sprite, texture_t* texture) {
    sprite_ani_init(sprite, texture->width, texture->height, texture);
}

void sprite_ani_init(sprite_t* sprite, int width, int height, texture_t* texture) {
    sprite->x = 0.0f;
    sprite->y = 0.0f;
    sprite->width = width;
    sprite->height = height;
    sprite->frame = 1;
    sprite->rotation = 0.0f;
    sprite->layer = 1.0f;
    sprite->transparency = 1.0f;
    sprite->texture = texture;

    GLfloat texw = 1.0f / texture->width * width;
    GLfloat texh = 1.0f / texture->height * height;

    GLfloat vertices_data[] = {
        -0.5f * width, -0.5f * height, 0.0f, 0.0f, 0.0f,
         0.5f * width, -0.5f * height, 0.0f, texw, 0.0f,
         0.5f * width,  0.5f * height, 0.0f, texw, texh,
        -0.5f * width,  0.5f * height, 0.0f, 0.0f, texh
    };

    GLuint indices_data[] = {
        0, 1, 2,
        0, 2, 3
    };

    // veritces
    glGenBuffers(1, &sprite->vertices);
    glBindBuffer(GL_ARRAY_BUFFER, sprite->vertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 5 * 4, vertices_data, GL_STATIC_DRAW_ARB);

    // veritces
    glGenBuffers(1, &sprite->indices);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sprite->indices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 6, indices_data, GL_STATIC_DRAW_ARB);
}

void sprite_release(sprite_t* sprite) {
    glDeleteBuffers(1, &sprite->vertices);
    glDeleteBuffers(1, &sprite->indices);
}


