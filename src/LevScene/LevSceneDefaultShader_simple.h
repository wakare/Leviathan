#pragma once

namespace Leviathan
{
	namespace Scene
	{
		const char* default_vertex_shader =
			"#version 330 core\n"
			"layout(location = 0) in vec3 position;"

			"uniform mat4 modelMatrix;"
			"uniform mat4 worldMatrix;"
			"uniform mat4 viewMatrix;"
			"uniform mat4 projMatrix;"
			"uniform vec4 defaultVertexColor = vec4(1.0, 0.0, 0.0, 1.0);"

			"out vec4 outColor;"

			"void main()"
			"{"
			"	gl_Position = projMatrix * viewMatrix * worldMatrix * modelMatrix * vec4(position.x, position.y, position.z, 1.0);"

			"	outColor = vec4(0.7, 0.7, 0.7, 1.0);"
			"	outColor = defaultVertexColor;"
			"}";

		const char* default_frag_shader =
			"#version 330 core\n"

			"in vec4 outColor;"
			"out vec4 color;"

			"void main()"
			"{"
			"		color = outColor;"
			"}";
	}
}