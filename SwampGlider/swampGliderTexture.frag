#version 330 core

in vec2 ourTexCoord;
in vec3 fragPos;
in vec3 ourNormal;

uniform vec3 lightPos; 
uniform vec3 lightColor;

out vec4 fragColor;

uniform sampler2D Texture;

void main()
{
    fragColor = texture(Texture, ourTexCoord);

    // ambient
    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * lightColor;
  	
    // diffuse 
    vec3 norm = normalize(ourNormal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse) * vec3(fragColor[0], fragColor[1], fragColor[2]);
    fragColor = vec4(result, 1.0);
}