#include "render.h"
#include <GL/glew.h>
#include <IL/il.h>
#include "array.h"

void render_init() {
    // glew
    glewInit();

    // devIL
    ilInit();
    ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
    ilEnable(IL_ORIGIN_SET);

    // opengl setting
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClientActiveTexture(GL_TEXTURE0);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}

void render(sprite_t** sprites) {
    glClearDepth(0.0f);
    glClearColor(0.0f, 1.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    GLint width = 640 / 2;
    GLint height = 480 / 2;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-width, width, -height, height, 0,100);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();

    for (int i = 0; i < array_count(sprites); i++) {
        glPopMatrix();
        glPushMatrix();
        sprite_t* sprite = sprites[i];

        // translate
        glTranslatef(sprite->x, sprite->y, -sprite->layer);

        // draw
        glBindBuffer(GL_ARRAY_BUFFER, sprite->vertices);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sprite->indices);
        glBindTexture(GL_TEXTURE_2D, sprite->texture->image);
        glVertexPointer(3, GL_FLOAT, 5 * sizeof(GLfloat), 0);
        glTexCoordPointer(2, GL_FLOAT, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
    
    glPopMatrix();
}

