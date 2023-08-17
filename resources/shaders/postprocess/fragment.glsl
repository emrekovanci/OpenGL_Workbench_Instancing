#version 330 core

#define KERNEL_ELEMENT_COUNT 9

in vec2 TexCoords;

out vec4 Color;

uniform sampler2D Scene;
uniform vec2 Offsets[KERNEL_ELEMENT_COUNT];
uniform float Kernel[KERNEL_ELEMENT_COUNT];

vec4 applyImageKernel(vec3 samples[KERNEL_ELEMENT_COUNT])
{
	vec4 result = vec4(0.0);

	for (int i = 0; i < KERNEL_ELEMENT_COUNT; ++i)
	{
		result += vec4(samples[i] * Kernel[i], 0.0);
	}

	result.a = 1.0;

	return result;
}

void main()
{
	vec3 samples[KERNEL_ELEMENT_COUNT];

	for (int i = 0; i < KERNEL_ELEMENT_COUNT; ++i)
	{
		samples[i] = vec3(texture(Scene, TexCoords.st + Offsets[i]));
	}

	Color = applyImageKernel(samples);
}