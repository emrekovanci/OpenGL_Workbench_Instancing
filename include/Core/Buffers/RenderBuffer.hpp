#pragma once

struct RenderBuffer
{
    RenderBuffer(unsigned int width, unsigned int height, int samples = 0);
    ~RenderBuffer();

    unsigned int Id {};
};