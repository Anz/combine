#include "sprite.h"


void sprite_init(sprite_t* sprite, texture_t* texture) {
    sprite->x = 0.0f;
    sprite->y = 0.0f;
    sprite->rotation = 0.0f;
    sprite->layer = 1.0f;

    GLfloat width = texture->width / 2.0f;
    GLfloat height = texture->height / 2.0f;
    sprite->texture = texture;

    GLfloat vertices_data[] = {
        -1.0f * width, -1.0f * height, 0.0f, 0.0f, 0.0f,
         1.0f * width, -1.0f * height, 0.0f, 1.0f, 0.0f,
         1.0f * width,  1.0f * height, 0.0f, 1.0f, 1.0f,
        -1.0f * width,  1.0f * height, 0.0f, 0.0f, 1.0f
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
