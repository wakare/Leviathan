#pragma once

namespace Leviathan
{
	namespace Viewer
	{
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
