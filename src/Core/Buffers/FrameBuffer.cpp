#include <Core/Buffers/FrameBuffer.hpp>

#include <glad/glad.h>

FrameBuffer::FrameBuffer()
{
	glGenFramebuffers(1, &Id);
}

FrameBuffer::~FrameBuffer()
{
	glDeleteFramebuffers(1, &Id);
}

void FrameBuffer::bind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, Id);
}

void FrameBuffer::unbind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::attachColorBuffer(const Texture2D& texture) const
{
	glFramebufferTexture2D(
		GL_FRAMEBUFFER,
		GL_COLOR_ATTACHMENT0,
		(texture.Samples == 0) ? GL_TEXTURE_2D : GL_TEXTURE_2D_MULTISAMPLE,
		texture.Id,
		0
	);
}

void FrameBuffer::attachDepthStencilBuffer(const RenderBuffer& renderBuffer) const
{
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBuffer.Id);
}
