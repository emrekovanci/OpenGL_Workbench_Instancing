#pragma once

#include <Core/Shader.hpp>
#include <Core/Texture2D.hpp>

#include <memory>

class PostProcess
{
private:
    void initVao();
    void initShader();

public:
    PostProcess(const Shader& shader, unsigned int width, unsigned int height);
    void prepareBuffers(unsigned int width, unsigned height);

    void begin();
    void render();
    void end();

private:
    Shader _shader;
    unsigned int _width;
    unsigned int _height;

    Texture2D _fboTexture {};
    unsigned int _fbo {};
    unsigned int _rbo {};
    unsigned int _vbo {};
    unsigned int _vao {};
};