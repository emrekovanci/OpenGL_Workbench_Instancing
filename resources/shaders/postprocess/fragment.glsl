#version 330 core

#define KERNEL_ELEMENT_COUNT 9

in vec2 TexCoords;

out vec4 Color;

uniform sampler2D scene;
uniform vec2 offsets[KERNEL_ELEMENT_COUNT];
uniform float kernel[KERNEL_ELEMENT_COUNT];

vec4 applyImageKernel(vec3 samples[KERNEL_ELEMENT_COUNT])
{
	vec4 result = vec4(0.0);

	for (int i = 0; i < KERNEL_ELEMENT_COUNT; ++i)
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