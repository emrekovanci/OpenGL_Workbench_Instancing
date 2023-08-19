#include <Core/Buffers/RenderBuffer.hpp>

#include <glad/glad.h>

RenderBuffer::RenderBuffer(unsigned int width, unsigned int height, int samples)
{
    glGenRenderbuffers(1, &Id);
    glBindRenderbuffer(GL_RENDERBUFFER, Id);

    if (samples == 0)
    {
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    }
    else
    {
        glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, GL_DEPTH24_STENCIL8, width, height);
    }

    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

RenderBuffer::~RenderBuffer()
{
    glDeleteRenderbuffers(1, &Id);
}