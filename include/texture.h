#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>

typedef struct texture {
    GLuint image;
    GLint width;
    GLint height;        
} texture_t;

void texture_load(texture_t* texture, char* path);
void texture_release(texture_t* texture);

#endif
