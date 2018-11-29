#version 330 core

in vec4 outColor;
in vec3 FragPos;
in vec3 Normal;
in vec2 TextureCoord;

out vec4 color;

struct Material 
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform Light light;
uniform vec3 viewPos;
uniform bool bLightOpen;
uniform uint VertexTypeMask;

// Texture samplers
uniform sampler2D ourTexture0;
uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;
uniform sampler2D ourTexture3;
uniform sampler2D ourTexture4;
uniform sampler2D ourTexture5;
uniform sampler2D ourTexture6;
uniform sampler2D ourTexture7;

void main()
{
	if ((VertexTypeMask & 0x8u) > 0u)
	{
		color = texture(ourTexture0, TextureCoord);
	}
	else
	{
		color = outColor;
	}

    if (!bLightOpen)
	{
		return;
	}

	if (gl_FrontFacing)
	{
		vec3 result = vec3(0.0, 0.0, 0.0);

		// Ambient
		vec3 ambient = light.ambient * material.ambient;
  		result += ambient;

		// Diffuse 
		vec3 norm = normalize(Normal);
		vec3 lightDir = normalize(light.position - FragPos);
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = light.diffuse * (diff * material.diffuse);
		result += diffuse;

		// Specular
		vec3 viewDir = normalize(viewPos - FragPos);
		vec3 reflectDir = reflect(-lightDir, norm);  
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
		vec3 specular = light.specular * (spec * material.specular);
		result += specular;

		result.x = min(result.x, 1.0);
		result.y = min(result.y, 1.0);
		result.z = min(result.z, 1.0);

		color = color * vec4(result, 1.0f);
		//color = vec4(result, 1.0f);
	}
}