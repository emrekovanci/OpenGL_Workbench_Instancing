#include <Core/Texture2D.hpp>

Texture2D::Texture2D(unsigned int width, unsigned int height, unsigned char* data, unsigned int samples) :
    Width { width },
    Height { height },
    Samples { samples }
{
    glGenTextures(1, &Id);

    bind();

    if (samples == 0)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, InternalFormat, width, height, 0, ImageFormat, GL_UNSIGNED_BYTE, data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, WrapS);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, WrapT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, FilterMin);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, FilterMax);
    }
    else
    {
        glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, InternalFormat, width, height, GL_TRUE);
    }

    unbind();
}

Texture2D::~Texture2D()
{
    glDeleteTextures(1, &Id);
}

void Texture2D::bind() const
{
    glBindTexture(Samples == 0 ? GL_TEXTURE_2D : GL_TEXTURE_2D_MULTISAMPLE, Id);
}

void Texture2D::unbind() const
{
    glBindTexture(Samples == 0 ? GL_TEXTURE_2D : GL_TEXTURE_2D_MULTISAMPLE, 0);
}
