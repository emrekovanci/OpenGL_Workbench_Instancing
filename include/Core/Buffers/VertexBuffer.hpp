#pragma once

#include <vector>

#include <glad/glad.h>

struct VertexBuffer
{
	enum class Usage
	{
		Static,
		Dynamic,
		Stream
	};

	explicit VertexBuffer(Usage usage = Usage::Static);
	~VertexBuffer();

	template <typename T>
	void fill(const std::vector<T>& vertices) const;

	void bind() const;
	void unbind() const;

	unsigned int Id {};
	Usage BufferUsage { Usage::Static };
};

namespace
{
	GLenum getUsageType(VertexBuffer::Usage usage)
	{
		switch (usage)
		{
			case VertexBuffer::Usage::Static:
				return GL_STATIC_DRAW;
			case VertexBuffer::Usage::Dynamic:
				return GL_DYNAMIC_DRAW;
			default:
				return GL_STREAM_DRAW;
		}
	}
}

template <typename T>
void VertexBuffer::fill(const std::vector<T>& vertices) const
{
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(T), vertices.data(), getUsageType(BufferUsage));
}