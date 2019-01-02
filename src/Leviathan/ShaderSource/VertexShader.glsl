#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec2 textureCoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;
uniform vec4 defaultVertexColor = vec4(1.0, 0.0, 0.0, 1.0);

uniform bool UseDefaultVertexColor;
uniform uint VertexTypeMask;

out vec4 outColor;
out vec3 FragPos;
out vec3 Normal;
out vec2 TextureCoord;

void main()
{
    gl_Position = projMatrix * viewMatrix * modelMatrix * vec4(position.x, position.y, position.z, 1.0);

	outColor = vec4(0.7, 0.7, 0.7, 1.0);
	if ((VertexTypeMask & 0x2u) > 0u)
	{
		outColor = color;
	}

	if (UseDefaultVertexColor)
	{
		outColor = defaultVertexColor;
	}

	FragPos = vec3(modelMatrix * vec4(position, 1.0f));
    Normal = mat3(transpose(inverse(modelMatrix))) * normal;  
	TextureCoord = textureCoord;
}
