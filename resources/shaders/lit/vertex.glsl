#version 330 core

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in mat4 instanceMatrix;

uniform mat4 View;
uniform mat4 Projection;

out vec4 WorldPosition;
out vec3 WorldNormal;

void main()
{
    WorldPosition = instanceMatrix * vec4(vertexPosition, 1.0);
    WorldNormal = mat3(transpose(inverse(instanceMatrix))) * vertexNormal;

    gl_Position = Projection * View * WorldPosition;
}