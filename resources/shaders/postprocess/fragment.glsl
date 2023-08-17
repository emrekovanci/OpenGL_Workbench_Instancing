#version 330 core

in vec2 TexCoords;
out vec4 Color;

uniform sampler2D scene;
uniform vec2 offsets[9];
uniform float kernel[9];

void main()
{
	// prepare samples
	vec3 samples[9];
	for (int i = 0; i < 9; ++i)
	{
		samples[i] = vec3(texture(scene, TexCoords.st + offsets[i]));
	}

	// apply blur
	vec4 resultColor = vec4(0.0);
	for (int j = 0; j < 9; ++j)
	{
		resultColor += vec4(samples[j] * kernel[j], 0.0);
	}
	resultColor.a = 1.0;

	Color = resultColor;
}