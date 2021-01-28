#version 330 core
out vec4 fragColor;

in VS_OUT {
    vec4 ourColor;
    vec3 fragPos;
    vec3 ourNormal;
} fs_in;

uniform samplerCube depthMap;

uniform vec3 lightPos; 
uniform vec3 lightColor;
uniform vec3 viewPos;

uniform float far_plane;
uniform bool shadows;

float ShadowCalculation(vec3 fragPos)
{
    vec3 fragToLight = fragPos - lightPos;
    float closestDepth = texture(depthMap, fragToLight).r;
    closestDepth *= far_plane;
    float currentDepth = length(fragToLight);
    float bias = 0.08;
    float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;

    return shadow;
}

void main()
{
    fragColor = fs_in.ourColor;

    // ambient
    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * lightColor;
  	
    // diffuse 
    vec3 norm = normalize(fs_in.ourNormal);
    vec3 lightDir = normalize(lightPos - fs_in.fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // calculate shadow
    float shadow = shadows ? ShadowCalculation(fs_in.fragPos) : 0.0;                      
    vec3 lighting = (ambient + (1.0 - shadow) * diffuse) * vec3(fs_in.ourColor[0], fs_in.ourColor[1], fs_in.ourColor[2]);  

    fragColor = vec4(lighting, 1.0);
}