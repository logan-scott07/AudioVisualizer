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
        unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        if (!data) {printf("Failed to load texture from %s.\n", path.c_str()); exit(-1);}

        GLenum format = channels == 4 ? GL_RGBA : GL_RGB;
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }

};