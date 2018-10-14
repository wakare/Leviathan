#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec3 normal;

uniform mat4 viewMatrix;
uniform mat4 projMatrix;
uniform uint VertexTypeMask;

out vec4 outColor;

void main()
{
    gl_Position = projMatrix * viewMatrix * vec4(position.x, position.y, position.z, 1.0);

	outColor = vec4(0.7, 0.7, 0.7, 1.0);
	if ((VertexTypeMask & 0x2u) > 0u)
	{
		outColor = color;
	}
}
