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
	_shader.setInt("Scene", 0);

	// init offsets
	constexpr float offset = 1.0f / 300.0f;
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
	glUniform2fv(glGetUniformLocation(_shader.getProgramId(), "Offsets"), 9, reinterpret_cast<const float*>(offsets));

	// sharpen
	const float kernel[9] =
	{
		0.0f, -1.0f, 0.0f,
		-1.0f, 5.0f, -1.0f,
		0.0f, -1.0f, 0.0f
	};
	glUniform1fv(glGetUniformLocation(_shader.getProgramId(), "Kernel"), 9, kernel);
}

PostProcess::PostProcess(const Shader& shader, unsigned int width, unsigned int height, unsigned int samples) :
	_shader{ shader },
	_width{ width },
	_height{ height },
	_samples{ samples }
{
	setSize(width, height);

	initVao();
	initShader();
}

void PostProcess::setSize(unsigned int width, unsigned height)
{
	_width = width;
	_height = height;

	_multiSampledColorBuffer.reset(new Texture2D(width, height, nullptr, _samples));
	_multiSampledRenderBuffer.reset(new RenderBuffer(width, height, _samples));
	_intermediateFrameBuffer.reset(new FrameBuffer());
	_fboTexture.reset(new Texture2D(width, height, nullptr));
	_frameBuffer.reset(new FrameBuffer());

	_frameBuffer->bind();
	_frameBuffer->attachColorBuffer(*_multiSampledColorBuffer);
	_frameBuffer->attachDepthStencilBuffer(*_multiSampledRenderBuffer);
	_frameBuffer->unbind();

	_intermediateFrameBuffer->bind();
	_intermediateFrameBuffer->attachColorBuffer(*_fboTexture);
	_intermediateFrameBuffer->unbind();
}

void PostProcess::begin()
{
	_frameBuffer->bind();
}

void PostProcess::render(int mouseX)
{
	glDisable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT);

	_shader.use();
	_shader.setInt("MouseX", mouseX);

	glBindVertexArray(_vao);
		glActiveTexture(GL_TEXTURE0);
		_fboTexture->bind();
		glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void PostProcess::end()
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, _frameBuffer->Id);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _intermediateFrameBuffer->Id);
	glBlitFramebuffer(0, 0, _width, _height, 0, 0, _width, _height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
	_frameBuffer->unbind();
}
