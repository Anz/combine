#include "texture.h"
#include "IL/il.h"

void texture_load(texture_t* texture, char* path) {
    ILuint texid;
    ilGenImages(1, &texid);
    ilBindImage(texid);
    ilLoadImage((const ILstring)path);
    ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
    
    glGenTextures(1, &texture->image);
    glBindTexture(GL_TEXTURE_2D, texture->image);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH),
      ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE,
      ilGetData());
    texture->width = ilGetInteger(IL_IMAGE_WIDTH);
    texture->height = ilGetInteger(IL_IMAGE_HEIGHT);

    ilDeleteImages(1, &texid);
}

void texture_release(texture_t* texture) {
    glDeleteTextures(1, &texture->image);
}
