#pragma once

namespace Leviathan
{
	const char* fire_vert = R"(#version 330 core
	layout(location = 0) in vec3 position;

	void main()
	{
		gl_Position = vec4(position, 1.0);
	};
	)";

	const char * fire_frag = R"(#version 330 core
	layout(location = 0) out vec4 Frag0;
	
	uniform sampler2D texture;

	void main()
	{
		Frag0 = vec4(1.0, 0.0, 0.0, 1.0);
	};
	)";
}