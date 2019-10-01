#pragma once

namespace Leviathan
{
	const char * skybox_vert = R"(#version 330 core
	layout(location = 0) in vec3 position;

	uniform mat4 modelMatrix;
	uniform mat4 worldMatrix;
	uniform mat4 viewMatrix;
	uniform mat4 projMatrix;

	out vec3 outTexCoords;

	void main()
	{
		outTexCoords = position;
		mat4 new_view_matrix = viewMatrix;
		new_view_matrix[3][0] = 0.0;
		new_view_matrix[3][1] = 0.0;
		new_view_matrix[3][2] = 0.0;

		gl_Position = projMatrix * new_view_matrix * vec4(position, 1.0);
	};
		
	)";

	const char * skybox_frag = R"(#version 330 core
	layout(location = 0) out vec4 Frag0;

	in vec3 outTexCoords;

	uniform samplerCube SKY_BOX_TEXTURE;	

	void main()
	{
		Frag0 = texture(SKY_BOX_TEXTURE, outTexCoords);
	};
	)";
}