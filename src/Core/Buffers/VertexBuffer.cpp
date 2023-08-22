#include <Core/Buffers/VertexBuffer.hpp>

VertexBuffer::VertexBuffer(Usage usage) : BufferUsage { usage }
{
	glGenBuffers(1, &Id);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &Id);
}

void VertexBuffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, Id);
}

void VertexBuffer::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}