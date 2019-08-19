#pragma once

namespace Leviathan
{
	const char* vfx_sdf_vert =
		"#version 330 core\n"
		"layout(location = 0) in vec3 position;"

		"uniform mat4 modelMatrix;"
		"uniform mat4 worldMatrix;"
		"uniform mat4 viewMatrix;"
		"uniform mat4 projMatrix;"
		"uniform vec4 defaultVertexColor = vec4(1.0, 1.0, 1.0, 1.0);"

		"out vec4 frag_world_coord;"
		"flat out vec3 obverse_world_coord;"

		"void main()"
		"{"
		"	vec4 world_coord = worldMatrix * modelMatrix * vec4(position, 1.0);"
		"	frag_world_coord = world_coord;"
		"	gl_Position = projMatrix * viewMatrix * world_coord;"
		"	vec4 obverse = inverse(viewMatrix) * vec4(0.0, 0.0, 0.0, 1.0);"
		"	obverse_world_coord = vec3(obverse);"
		"}";

	const char* vfx_sdf_frag =
		"#version 330 core\n"
		"in vec4 frag_world_coord;"
		"flat in vec3 obverse_world_coord;"

		"out vec4 color;"

		"uniform sampler3D SDF_TEXTURE;"
		"uniform vec3 SDF_MIN;"
		"uniform vec3 SDF_GRID_LENGTH;"

		"float GetWeight(vec3 texture_coord)"
		"{"
		"	return (texture(SDF_TEXTURE, texture_coord)).r;"
		"}"

		"vec3 WorldCoordToTexCoord(vec3 world_coord)"
		"{"
		"	vec3 texture_coord = world_coord - SDF_MIN;"
		"	texture_coord.x /= SDF_GRID_LENGTH.x;"
		"	texture_coord.y /= SDF_GRID_LENGTH.y;"
		"	texture_coord.z /= SDF_GRID_LENGTH.z;"

		"	texture_coord.x = clamp(texture_coord.x, 0.0, 1.0);"
		"	texture_coord.y = clamp(texture_coord.y, 0.0, 1.0);"
		"	texture_coord.z = clamp(texture_coord.z, 0.0, 1.0);"

		"	return texture_coord;"
		"}"

		"vec3 RayMarching(vec3 frag_world_coord, vec3 frag_obverse_dir, float step_length, int step_count)"
		"{"
		"	vec3 step_frag_world_coord = frag_world_coord;"
		"	vec3 step_vector = step_length * frag_obverse_dir;"
		"	vec3 frag_tex_coord = WorldCoordToTexCoord(step_frag_world_coord);"
		"	float weight = GetWeight(frag_tex_coord);"
		"	if (weight < 0.0) return frag_tex_coord;"

		"	for (int i = 0; i < step_count; i++)"
		"	{"
		"		step_frag_world_coord += step_vector;"
		"		vec3 texture_coord = WorldCoordToTexCoord(step_frag_world_coord);"
		"		float weight = GetWeight(texture_coord);"
		"		if (weight < 0.0) return texture_coord;"
		"	}"
		"	discard;"
		"}"

		"void main()"
		"{"
		"	vec3 frag_world_vector = vec3(frag_world_coord / frag_world_coord.w);"
		"	vec3 obverse_dir = normalize(frag_world_vector - obverse_world_coord);"
		"	vec3 tex_coord = RayMarching(frag_world_vector, obverse_dir, 0.2, 100);"
		"	float weight = GetWeight(tex_coord);"
		"	weight = clamp(weight, 0.0, 1.0);"
		"	color = vec4(weight, weight, weight, 1.0);"

		//"	color = vec4(obverse_dir, 1.0);"
		//"	color = vec4(obverse_world_coord, 1.0);"
		//"	vec3 tex_coord = WorldCoordToTexCoord(frag_world_coord);"
		//"	color = vec4(tex_coord, 1.0);"
		//"	float weight = GetWeight(tex_coord);"
		//"	color = vec4(weight, weight, weight, 1.0);"
		"}";
}