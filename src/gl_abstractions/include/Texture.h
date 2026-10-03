#pragma once
#include <glad/glad.h>
#include "stb_image.h"
#include <string>
#include <cstdio>

struct Texture {
    GLuint id = 0;
    int width = 0, height = 0;

    Texture(const std::string &path) {
        stbi_set_flip_vertically_on_load(true);
        int channels;
        unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 4);
        if (!data) {printf("Failed to load texture from %s.\n", path.c_str()); exit(-1);}

        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }

};