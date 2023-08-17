#include <Graphics/PostProcess.hpp>

#include <iostream>
#include <vector>

void PostProcess::initVao()
{
	std::vector<GLfloat> vertices =
	{
		// pos			// tex
		-1.0f, -1.0f,	0.0f, 0.0f,
		1.0f,  1.0f,	1.0f, 1.0f,
		-1.0f,  1.0f,	0.0f, 1.0f,

		-1.0f, -1.0f,	0.0f, 0.0f,
		1.0f, -1.0f,	1.0f, 0.0f,
		1.0f,  1.0f,	1.0f, 1.0f
	};

	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void PostProcess::initShader()
{
	_shader.use();
	_shader.setInt("scene", 0);

	// init offsets
	const float offset = 1.0f / 300.0f;
	const float offsets[9][2] =
	{
		{ -offset,  offset  },  // top-left
		{  0.0f,    offset  },  // top-center
		{  offset,  offset  },  // top-right
		{ -offset,  0.0f    },  // center-left
		{  0.0f,    0.0f    },  // center-center
		{  offset,  0.0f    },  // center - right
		{ -offset, -offset  },  // bottom-left
		{  0.0f,   -offset  },  // bottom-center
		{  offset, -offset  }   // bottom-right
	};
	glUniform2fv(glGetUniformLocation(_shader.getProgramId(), "offsets"), 9, reinterpret_cast<const float*>(offsets));

	// sharpen
	const float kernel[9] =
	{
		0.0f, -1.0f, 0.0f,
		-1.0f, 5.0f, -1.0f,
		0.0f, -1.0f, 0.0f
	};
	glUniform1fv(glGetUniformLocation(_shader.getProgramId(), "kernel"), 9, kernel);
}

PostProcess::PostProcess(const Shader& shader, unsigned int width, unsigned int height) :
    _shader { shader },
    _width { width },
    _height { height },
	_fboTexture { std::make_unique<Texture2D>() },
	_frameBuffer { std::make_unique<FrameBuffer>() },
	_renderBuffer { std::make_unique<RenderBuffer>(width, height) }
{
	_fboTexture->generate(width, height, nullptr);

	_frameBuffer->bind();
	_frameBuffer->attachColorBuffer(*_fboTexture);
	_frameBuffer->attachDepthStencilBuffer(*_renderBuffer);
	_frameBuffer->unbind();

	initVao();
	initShader();
}

void PostProcess::setSize(unsigned int width, unsigned height)
{
	// reset fbo texture
	_fboTexture.reset(new Texture2D());
	_fboTexture->generate(width, height, nullptr);

	// reset renderbuffer
	_renderBuffer.reset(new RenderBuffer(width, height));

	// reset framebuffer
	_frameBuffer.reset(new FrameBuffer());
	_frameBuffer->bind();
	_frameBuffer->attachColorBuffer(*_fboTexture);
	_frameBuffer->attachDepthStencilBuffer(*_renderBuffer);
	_frameBuffer->unbind();
}

void PostProcess::begin()
{
	_frameBuffer->bind();

	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void PostProcess::render()
{
	glDisable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT);

	_shader.use();

	glBindVertexArray(_vao);
		_fboTexture->bind();
		glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void PostProcess::end()
{
	_frameBuffer->unbind();
}
