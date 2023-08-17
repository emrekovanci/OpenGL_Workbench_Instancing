#pragma once

#include <Core/Texture2D.hpp>
#include <Core/Buffers/RenderBuffer.hpp>

struct FrameBuffer
{
    FrameBuffer();
    ~FrameBuffer();

    void bind() const;
    void unbind() const;

    void attachColorBuffer(const Texture2D& texture) const;
    void attachDepthStencilBuffer(const RenderBuffer& renderBuffer) const;

    unsigned int Id {};
};