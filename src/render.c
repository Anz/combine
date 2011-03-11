#include "render.h"
#include <GL/glew.h>
#include <IL/il.h>
#include "array.h"

bool compare_layer(void* a, void* b) {
    sprite_t* sa = a;
    sprite_t* sb = b;

    return sa->layer > sb->layer;
}

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
    glClearColor(0.0f, 1.0f, 0.0f, 0.0f);
}

void render(scene_t* scene) {
    glClear(GL_COLOR_BUFFER_BIT);
    GLint width = 640 / 2;
    GLint height = 480 / 2;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-width, width, -height, height, 0,100);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();

    array_sort(scene->space, &compare_layer);

    for (int i = 0; i < array_count(scene->space); i++) {
        glPopMatrix();
        glPushMatrix();
        sprite_t* sprite = scene->space[i];
        texture_t* texture = sprite->texture;

        glMatrixMode(GL_TEXTURE);
        glLoadIdentity();
        int frame_per_line = texture->width / sprite->width;
        GLfloat twfactor = 1.0f / texture->width;
        GLfloat thfactor = 1.0f / texture->height;
        GLfloat texx = (sprite->width * (((sprite->frame - 1) % frame_per_line))) * twfactor;
        GLfloat texy = (texture->height - sprite->height * ((sprite->frame - 1) / frame_per_line + 1)) * thfactor;
        glTranslatef(texx, texy, 0.0f);


        printf("frame %i/%i (%.3f, %.3f)\n", sprite->frame, frame_per_line, texx, texy);

        // translate
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(sprite->x - scene->camera.x, sprite->y - scene->camera.y, sprite->layer - 100);
        glRotatef(sprite->rotation, 0.0f, 0.0f, -1.0f);


        // draw
        glColor4f(1.0f, 1.0f, 1.0f, sprite->transparency);
        glBindBuffer(GL_ARRAY_BUFFER, sprite->vertices);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sprite->indices);
        glBindTexture(GL_TEXTURE_2D, sprite->texture->image);
        glVertexPointer(3, GL_FLOAT, 5 * sizeof(GLfloat), 0);
        glTexCoordPointer(2, GL_FLOAT, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
    
    glPopMatrix();

    glPushMatrix();

    array_sort(scene->hud, &compare_layer);

    for (int i = 0; i < array_count(scene->hud); i++) {
        glPopMatrix();
        glPushMatrix();
        sprite_t* sprite = scene->hud[i];

        glMatrixMode(GL_TEXTURE);
        glLoadIdentity();

        // translate
        glMatrixMode(GL_MODELVIEW);
        glTranslatef(sprite->x, sprite->y, sprite->layer -100);
        glRotatef(sprite->rotation, 0.0f, 0.0f, -1.0f);

        // draw
        glColor4f(1.0f, 1.0f, 1.0f, sprite->transparency);
        glBindBuffer(GL_ARRAY_BUFFER, sprite->vertices);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sprite->indices);
        glBindTexture(GL_TEXTURE_2D, sprite->texture->image);
        glVertexPointer(3, GL_FLOAT, 5 * sizeof(GLfloat), 0);
        glTexCoordPointer(2, GL_FLOAT, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
    
    glPopMatrix();

}

