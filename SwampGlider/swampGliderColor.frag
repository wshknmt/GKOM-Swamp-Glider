#version 330 core

in vec4 ourColor;
in vec3 fragPos;
in vec3 ourNormal;

uniform vec3 lightPos; 
uniform vec3 lightColor;

out vec4 fragColor;

void main()
{
    fragColor = ourColor;

    // ambient
    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * lightColor;
  	
    // diffuse 
    vec3 norm = normalize(ourNormal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse) * vec3(ourColor[0], ourColor[1], ourColor[2]);
    fragColor = vec4(result, 1.0);
}