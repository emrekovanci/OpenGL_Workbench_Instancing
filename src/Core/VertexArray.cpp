#include <Core/VertexArray.hpp>

#include <glad/glad.h>

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &Id);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &Id);
}

void VertexArray::bind() const
{
    glBindVertexArray(Id);
}

void VertexArray::unbind() const
{
    glBindVertexArray(0);
}

void VertexArray::enableAttribute(unsigned int index, unsigned int size, int stride, const void* pointer) const
{
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, pointer);
}

void VertexArray::divisor(unsigned int index, unsigned int divisor) const
{
    glVertexAttribDivisor(index, divisor);
}
