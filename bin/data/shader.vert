#version 410

layout (location = 0) in vec3 position;
layout (location = 2) in vec3 normal;

uniform mat4 mvp; // Movel-view-projection transform.

uniform mat3 normalMatrix;
out vec3 fragNormal;

void main()
{
	gl_Position = mvp * vec4(position, 1.0);
	fragNormal = normalMatrix * normal;
}