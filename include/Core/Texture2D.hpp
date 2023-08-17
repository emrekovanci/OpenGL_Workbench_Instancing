#pragma once

#include <glad/glad.h>

struct Texture2D
{
    Texture2D();
    ~Texture2D();

    void generate(unsigned int width, unsigned int height, unsigned char* data);
    void bind() const;
    void unbind() const;

    unsigned int Id {};
    unsigned int Width {};
    unsigned int Height {};

    unsigned int InternalFormat { GL_RGB };
    unsigned int ImageFormat { GL_RGB };

    unsigned int WrapS { GL_REPEAT };
    unsigned int WrapT { GL_REPEAT };

    unsigned int FilterMin { GL_NEAREST };
    unsigned int FilterMax { GL_NEAREST };
};