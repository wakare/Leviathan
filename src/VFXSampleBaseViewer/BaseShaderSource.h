#pragma once

namespace Leviathan
{
	namespace Viewer
	{
		const char* defer_main_vert =
			"#version 330 core\n"
			"layout(location = 0) in vec3 position;"
			"layout(location = 1) in vec3 normal;"

			"uniform mat4 modelMatrix;"
			"uniform mat4 worldMatrix;"
			"uniform mat4 viewMatrix;"
			"uniform mat4 projMatrix;"
			"uniform vec4 defaultVertexColor = vec4(1.0, 1.0, 1.0, 1.0);"

			"out vec4 outColor;"
			"out vec3 outNormal;"
			"out vec3 fragment_coordination;"

			"void main()"
			"{"
			"	gl_Position = projMatrix * viewMatrix * worldMatrix * modelMatrix * vec4(position, 1.0);"

			"	outColor = defaultVertexColor;"
			"	outNormal = normal;"
			"	fragment_coordination = vec3(worldMatrix * modelMatrix * vec4(position, 1.0));"
			"}";

		const char* defer_main_frag =
			"#version 330 core\n"

			"layout(location = 0) out vec4 Frag0;"
			"layout(location = 1) out vec4 Frag1;"

			"in vec4 outColor;"
			"in vec3 outNormal;"
			"in vec3 fragment_coordination;"

			"out vec4 color;"

			"struct point_light_struct"
			"{"
			"	vec3 coord;"
			"	vec3 diffuse_color;"
			"};"

			"uniform point_light_struct point_light[100];"
			"uniform vec4 view_coord;"
			"uniform int light_count = 0;"

			"vec4 calculate_light_contribution(vec3 view_coordination, point_light_struct cur_point_light)"
			"{"
			"	vec3 light_direction = normalize(cur_point_light.coord - view_coordination);"
			"	vec3 normal = normalize(outNormal);"

			"	float diff = max(dot(normal, light_direction), 0.0);"
			"	vec3 diffuse_color = diff * cur_point_light.diffuse_color;"

			"	return vec4(diffuse_color, 1.0);"
			"}"

			"void main()"
			"{"
			"	int light_max_count = max(light_count, 100);"
			"	for (int i = 0; i < light_max_count; i++)"
			"	{"
			"		Frag0 += outColor * calculate_light_contribution(fragment_coordination, point_light[i]);"
			"	}"

			"	Frag1 = vec4(1.0, 0.0, 0.0, 1.0);"
			"}";

		const char* defer_quad_vert = R"(
			#version 330 core
			layout(location = 0) in vec3 position;
			layout(location = 1) in vec2 tex_coord;
			
			out vec2 tex;

			void main()
			{
				gl_Position = vec4(position, 1.0);
				tex = tex_coord;
			}
		)";

		const char* defer_quad_frag = R"(
			#version 330 core

			in vec2 tex;
	
			out vec4 color;
			uniform sampler2D Quad_texture;

			void main()
			{
				color = texture(Quad_texture, tex);
			}
		)";
	}
}

