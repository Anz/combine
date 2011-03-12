#ifndef CAMERA_H
#define CAMERA_H

typedef struct camera {
    int x, y, width, height;
} camera_t;

void camera_init(camera_t* camera, int x, int y, int width, int height);

#endif
