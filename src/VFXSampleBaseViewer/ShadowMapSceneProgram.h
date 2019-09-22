#pragma once

const char* shadow_map_vert = R"(#version 330 core
	layout(location = 0) in vec3 position;
	layout(location = 1) in vec3 normal;

	uniform mat4 modelMatrix;
	uniform mat4 worldMatrix;
	uniform mat4 viewMatrix;
	uniform mat4 projMatrix;
	uniform mat4 light_viewMatrix;
	uniform mat4 light_projMatrix;

	out vec3 outNormal;
	out vec4 outLightSpaceFrag;

	void main()
	{
		gl_Position = projMatrix * viewMatrix * worldMatrix * modelMatrix * vec4(position, 1.0);
		outLightSpaceFrag = light_projMatrix * light_viewMatrix * worldMatrix * modelMatrix * vec4(position, 1.0);
		outNormal = normal;
	};
)";

const char* shadow_map_frag = R"(#version 330 core
	layout(location = 0) out vec4 Frag0;

	in vec3 outNormal;
	in vec4 outLightSpaceFrag;

	uniform sampler2D DEPTH_TEXTURE;	

	void main()
	{
		vec3 light_space_frag = vec3(outLightSpaceFrag / outLightSpaceFrag.w);
		light_space_frag = light_space_frag * 0.5 + 0.5;
		
		if (0.0 < light_space_frag.x && light_space_frag.x < 1.0 && 0.0 < light_space_frag.y && light_space_frag.y < 1.0)
		{
			float depth_bias = 0.0005;

			float texture_value = float(texture(DEPTH_TEXTURE, light_space_frag.xy));

			if ((texture_value + depth_bias) < light_space_frag.z)
			{
				Frag0 = vec4(0.0, 0.0, 0.0, 1.0);
			}
			else
			{
				Frag0 = vec4(texture_value, texture_value, texture_value, 1.0);
			}
		}
		else
		{
			Frag0 = vec4(0.0, 1.0, 0.0, 1.0);
		}		
	};
)";


const char* shadow_preprocess_vert = R"(#version 330 core
	layout(location = 0) in vec3 position;
	layout(location = 1) in vec3 normal;

	uniform mat4 modelMatrix;
	uniform mat4 worldMatrix;
	uniform mat4 light_viewMatrix;
	uniform mat4 light_projMatrix;

	void main()
	{
		gl_Position = light_projMatrix * light_viewMatrix * worldMatrix * modelMatrix * vec4(position, 1.0);
	};
)";

const char* shadow_preprocess_frag = R"(#version 330 core
	void main()
	{
		
	}
)";