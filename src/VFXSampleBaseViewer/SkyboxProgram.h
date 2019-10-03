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
		gl_Position.z = gl_Position.w - 0.001;
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

	const char* reflect_vert = R"(
	#version 330 core
	layout(location = 0) in vec3 position;
	layout(location = 1) in vec3 normal;

	uniform mat4 modelMatrix;
	uniform mat4 worldMatrix;
	uniform mat4 viewMatrix;
	uniform mat4 projMatrix;

	flat out vec3 camera_position;
	out vec3 frag_pos;
	out vec3 frag_normal;

	void main()
	{
		vec4 _frag_pos = worldMatrix * modelMatrix * vec4(position, 1.0);
		frag_pos = vec3(_frag_pos);
		gl_Position = projMatrix * viewMatrix * _frag_pos;
		
		camera_position = vec3(inverse(viewMatrix) * vec4(0.0, 0.0, 0.0, 1.0));
		frag_normal = vec3(worldMatrix * modelMatrix * vec4(normal, 0.0));
		frag_normal = normalize(frag_normal);
	};
)";

	const char* reflect_frag = R"(
	#version 330 core
	layout(location = 0) out vec4 Frag0;

	flat in vec3 camera_position;
	in vec3 frag_pos;
	in vec3 frag_normal;

	uniform samplerCube SKY_BOX_TEXTURE;

	void main()
	{
		vec3 view_dir = normalize(frag_pos - camera_position);
		vec3 reflect_dir = reflect(view_dir, frag_normal);

		Frag0 = texture(SKY_BOX_TEXTURE, reflect_dir);
	};
)";

	const char* refract_frag = R"(
	#version 330 core
	layout(location = 0) out vec4 Frag0;

	flat in vec3 camera_position;
	in vec3 frag_pos;
	in vec3 frag_normal;

	uniform samplerCube SKY_BOX_TEXTURE;
	uniform float refract_ratio = 1.0 / 1.52;

	void main()
	{
		vec3 view_dir = normalize(frag_pos - camera_position);
		vec3 refract_dir = refract(view_dir, frag_normal, refract_ratio);

		Frag0 = texture(SKY_BOX_TEXTURE, refract_dir);
	};
)";
}

