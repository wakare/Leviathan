#pragma once

namespace Leviathan
{
	namespace Scene
	{
		const char* default_vertex_shader =
			"#version 330 core\n"
			"layout(location = 0) in vec3 position;"
			"layout(location = 1) in vec4 color;"
			"layout(location = 2) in vec3 normal;"
			"layout(location = 3) in vec2 textureCoord;"

			"uniform mat4 modelMatrix;"
			"uniform mat4 worldMatrix;"
			"uniform mat4 viewMatrix;"
			"uniform mat4 projMatrix;"
			"uniform vec4 defaultVertexColor = vec4(1.0, 0.0, 0.0, 1.0);"

			"uniform bool UseDefaultVertexColor;"
			"uniform uint VertexTypeMask;"

			"out vec4 outColor;"
			"out vec3 FragPos;"
			"out vec3 Normal;"
			"out vec2 TextureCoord;"

			"void main()"
			"{"
			"	gl_Position = projMatrix * viewMatrix * worldMatrix * modelMatrix * vec4(position.x, position.y, position.z, 1.0);"

			"	outColor = vec4(0.7, 0.7, 0.7, 1.0);"
			"	if ((VertexTypeMask & 0x2u) > 0u)"
			"	{"
			"		outColor = color;"
			"	}"

			"	if (UseDefaultVertexColor)"
			"	{"
			"		outColor = defaultVertexColor;"
			"	}"

			"	FragPos = vec3(modelMatrix * vec4(position, 1.0f));"
			"	Normal = mat3(transpose(inverse(modelMatrix))) * normal;"
			"	TextureCoord = textureCoord;"
			"}";

		const char* default_frag_shader =
		"#version 330 core\n"

		"in vec4 outColor;"
		"in vec3 FragPos;"
		"in vec3 Normal;"
		"in vec2 TextureCoord;"

		"out vec4 color;"

		"struct Material"
		"{"
		"	vec3 ambient;"
		"	vec3 diffuse;"
		"	vec3 specular;"
		"	float shininess;"
		"};"

		"struct Light {"
		"	vec3 position;"
		"	vec3 ambient;"
		"	vec3 diffuse;"
		"	vec3 specular;"
		"};"

		"uniform Material material;"
		"uniform Light light;"
		"uniform vec3 viewPos;"
		"uniform bool bLightOpen;"
		"uniform uint VertexTypeMask;"

		"// Texture samplers"
		"uniform sampler2D ourTexture0;"
		"uniform sampler2D ourTexture1;"
		"uniform sampler2D ourTexture2;"
		"uniform sampler2D ourTexture3;"
		"uniform sampler2D ourTexture4;"
		"uniform sampler2D ourTexture5;"
		"uniform sampler2D ourTexture6;"
		"uniform sampler2D ourTexture7;"

		"void main()"
		"{"
		"	if ((VertexTypeMask & 0x8u) > 0u)"
		"	{"
		"		color = texture(ourTexture0, TextureCoord);"
		"	}"
		"	else"
		"	{"
		"		color = outColor;"
		"	}"

		"	if (!bLightOpen) return;"
		"	//if (!gl_FrontFacing) return;"

		"	vec3 result = vec3(0.0, 0.0, 0.0);"

		"	// Ambient"
		"	vec3 ambient = light.ambient * material.ambient;"
		"	result += ambient;"

		"	// Diffuse "
		"	vec3 norm = normalize(Normal);"
		"	vec3 lightDir = normalize(light.position - FragPos);"
		"	float diff = max(dot(norm, lightDir), 0.0);"
		"	vec3 diffuse = light.diffuse * (diff * material.diffuse);"
		"	result += diffuse;"

		"	// Specular"
		"	vec3 viewDir = normalize(viewPos - FragPos);"
		"	vec3 reflectDir = reflect(-lightDir, norm);"
		"	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);"
		"	vec3 specular = light.specular * (spec * material.specular);"
		"	result += specular;"

		"	result.x = min(result.x, 1.0);"
		"	result.y = min(result.y, 1.0);"
		"	result.z = min(result.z, 1.0);"

		"	color = color * vec4(result, 1.0f);"
		"}";
	}
}