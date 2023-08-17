#include <Core/Texture2D.hpp>

Texture2D::Texture2D()
{
    glGenTextures(1, &Id);
}

Texture2D::~Texture2D()
{
    glDeleteTextures(1, &Id);
}

void Texture2D::generate(unsigned int width, unsigned int height, unsigned char* data)
{
    Width = width;
    Height = height;

    glBindTexture(GL_TEXTURE_2D, Id);
    glTexImage2D(GL_TEXTURE_2D, 0, InternalFormat, width, height, 0, ImageFormat, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, WrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, WrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, FilterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, FilterMax);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::bind() const
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, Id);
}

void Texture2D::unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
