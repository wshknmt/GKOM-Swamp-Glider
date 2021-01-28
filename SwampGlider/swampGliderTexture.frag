#version 330 core
out vec4 fragColor;

in VS_OUT {
    vec3 fragPos;
    vec3 ourNormal;
    vec2 ourTexCoords;
} fs_in;

uniform sampler2D Texture;
uniform samplerCube depthMap;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;

uniform float far_plane;
uniform bool shadows;

// array of offset direction for sampling
vec3 gridSamplingDisk[20] = vec3[]
(
   vec3(1, 1,  1), vec3( 1, -1,  1), vec3(-1, -1,  1), vec3(-1, 1,  1), 
   vec3(1, 1, -1), vec3( 1, -1, -1), vec3(-1, -1, -1), vec3(-1, 1, -1),
   vec3(1, 1,  0), vec3( 1, -1,  0), vec3(-1, -1,  0), vec3(-1, 1,  0),
   vec3(1, 0,  1), vec3(-1,  0,  1), vec3( 1,  0, -1), vec3(-1, 0, -1),
   vec3(0, 1,  1), vec3( 0, -1,  1), vec3( 0, -1, -1), vec3( 0, 1, -1)
);

float ShadowCalculation(vec3 fragPos)
{
    vec3 fragToLight = fragPos - lightPos;
    float currentDepth = length(fragToLight);

    float shadow = 0.0;
    float bias = 0.2;
    int samples = 20;
    float viewDistance = length(viewPos - fragPos);
    float diskRadius = (1.0 + (viewDistance / far_plane)) / 25.0;
    for(int i = 0; i < samples; ++i){
        float closestDepth = texture(depthMap, fragToLight + gridSamplingDisk[i] * diskRadius).r;
        closestDepth *= far_plane;
        if(currentDepth - bias > closestDepth)
            shadow += 1.0;
    }
    shadow /= float(samples);

    return shadow;
}

void main()
{
    vec3 color = texture(Texture, fs_in.ourTexCoords).rgb;
    vec3 norm = normalize(fs_in.ourNormal);

    // ambient
    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * lightColor;
  	
    // diffuse 
    
    vec3 lightDir = normalize(lightPos - fs_in.fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // calculate shadow
    float shadow = shadows ? ShadowCalculation(fs_in.fragPos) : 0.0;
    vec3 result = (ambient + (1.0 - shadow) * diffuse) * color;
    fragColor = vec4(result, 1.0);
}