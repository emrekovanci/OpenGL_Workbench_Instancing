#include <Core/PostProcess.hpp>

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

	// init blur kernel
	const float blur_kernel[9] =
	{
		1.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f,
		2.0f / 16.0f, 4.0f / 16.0f, 2.0f / 16.0f,
		1.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f
	};
	glUniform1fv(glGetUniformLocation(_shader.getProgramId(), "blur_kernel"), 9, blur_kernel);
}

PostProcess::PostProcess(const Shader& shader, unsigned int width, unsigned int height) :
    _shader { shader },
    _width { width },
    _height { height }
{
	_fboTexture.generate(width, height, nullptr);

	glGenFramebuffers(1, &_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _fboTexture.Id, 0);

	glGenRenderbuffers(1, &_rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, _rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _rbo);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	initVao();
	initShader();
}

void PostProcess::prepareBuffers(unsigned int width, unsigned height)
{
}

void PostProcess::begin()
{
	glBindFramebuffer(GL_FRAMEBUFFER, _fbo);

	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void PostProcess::render()
{
	glDisable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT);

	_shader.use();

	glBindVertexArray(_vao);
		_fboTexture.bind();
		glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void PostProcess::end()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
