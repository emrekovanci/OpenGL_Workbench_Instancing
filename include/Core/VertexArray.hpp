#pragma once

struct VertexArray
{
    VertexArray();
    ~VertexArray();

    void bind() const;
    void unbind() const;

    void enableAttribute(unsigned int index, unsigned int size, int stride, const void* pointer) const;
    void divisor(unsigned int index, unsigned int divisor) const;

    unsigned int Id {};
};