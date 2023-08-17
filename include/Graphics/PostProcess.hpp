#pragma once

#include <Core/Shader.hpp>
#include <Core/Texture2D.hpp>
#include <Core/Buffers/FrameBuffer.hpp>
#include <Core/Buffers/RenderBuffer.hpp>

#include <memory>

class PostProcess
{
private:
    void initVao();
    void initShader();

public:
    PostProcess(const Shader& shader, unsigned int width, unsigned int height);
    void setSize(unsigned int width, unsigned height);

    void begin();
    void render();
    void end();

private:
    Shader _shader;
    unsigned int _width;
    unsigned int _height;

    std::unique_ptr<Texture2D> _fboTexture;
    std::unique_ptr<FrameBuffer> _frameBuffer;
    std::unique_ptr<RenderBuffer> _renderBuffer;

    unsigned int _vbo;
    unsigned int _vao;
};