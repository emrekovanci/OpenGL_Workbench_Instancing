#version 330 core

in vec2 TexCoords;
out vec4 Color;

uniform sampler2D scene;
uniform vec2 offsets[9];
uniform float kernel[9];

vec4 applyImageKernel(vec3 samples[9])
{
	vec4 result = vec4(0.0);

	for (int i = 0; i < 9; ++i)
	{
		result += vec4(samples[i] * kernel[i], 0.0);
	}

	result.a = 1.0;

	return result;
}

void main()
{
	vec3 samples[9];
	for (int i = 0; i < 9; ++i)
	{
		samples[i] = vec3(texture(scene, TexCoords.st + offsets[i]));
	}

	Color = applyImageKernel(samples);
}