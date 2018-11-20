#version 330 core

in vec4 outColor;
in vec3 FragPos;
in vec3 Normal;

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

void main()
{
    //color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    color = outColor;

	//// Ambient
    //vec3 ambient = light.ambient * material.ambient;
  	
    //// Diffuse 
    //vec3 norm = normalize(Normal);
    //vec3 lightDir = normalize(light.position - FragPos);
    //float diff = max(dot(norm, lightDir), 0.0);
    //vec3 diffuse = light.diffuse * (diff * material.diffuse);
    
    //// Specular
    //vec3 viewDir = normalize(viewPos - FragPos);
    //vec3 reflectDir = reflect(-lightDir, norm);  
    //float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    //vec3 specular = light.specular * (spec * material.specular);  
        
    //vec3 result = ambient + diffuse + specular;
    //color = vec4(result, 1.0f);
}