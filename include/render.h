#ifndef RENDER_H
#define RENDER_H

#include "scene.h"
#include "camera.h"

void render_init();
void render(scene_t* scene, camera_t* camera);

#endif
