#include "camera.h"

void camera_init(camera_t* camera, int x, int y, int width, int height) {
    camera->x = x;
    camera->y = y;
    camera->width = width;
    camera->height = height;
}
