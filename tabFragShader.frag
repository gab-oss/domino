#version 330 core
out vec4 FragColor;
  
in vec4 vertexColor;
in vec3 Normal;  
in vec3 FragPos;  

uniform vec3 lightPos;  
uniform vec4 lightColor;

void main()
{
	float ambientStrength = 0.5;
	float diffuseStrength = 1.5;
	vec4 ambient = ambientStrength * lightColor;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);  

	float diff = max(dot(norm, lightDir), 0.0);
	vec4 diffuse = diff * lightColor * diffuseStrength;

	vec4 result = (ambient + diffuse) * vertexColor;

    FragColor = result;
}