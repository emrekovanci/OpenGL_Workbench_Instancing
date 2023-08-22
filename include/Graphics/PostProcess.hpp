#pragma once

#include <Core/Shader.hpp>
#include <Core/Texture2D.hpp>
#include <Core/VertexArray.hpp>
#include <Core/Buffers/FrameBuffer.hpp>
#include <Core/Buffers/RenderBuffer.hpp>

#include <memory>

class PostProcess
{
private:
    void initVao();
    void initShader();

public:
    PostProcess(const Shader& shader, unsigned int width, unsigned int height, unsigned int samples = 4);
    void setSize(unsigned int width, unsigned height);

    void begin();
    void render(int mouseX);
    void end();

private:
    Shader _shader;
    unsigned int _width;
    unsigned int _height;
    unsigned int _samples;

    std::unique_ptr<Texture2D> _multiSampledColorBuffer;
    std::unique_ptr<RenderBuffer> _multiSampledRenderBuffer;
    std::unique_ptr<FrameBuffer> _intermediateFrameBuffer;

    std::unique_ptr<Texture2D> _fboTexture;
    std::unique_ptr<FrameBuffer> _frameBuffer;

    VertexArray _vao;
};