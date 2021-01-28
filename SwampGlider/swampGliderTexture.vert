#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texCoord;
layout (location = 3) in vec3 normal;

out vec2 ourTexCoord;

out VS_OUT {
    vec3 fragPos;
    vec3 ourNormal;
    vec2 ourTexCoords;
} vs_out;
  
uniform mat4 model; 
uniform mat4 view; 
uniform mat4 projection;

void main()
{
    vs_out.fragPos = vec3(model * vec4(position, 1.0));

    vs_out.ourNormal = transpose(inverse(mat3(model))) * normal;

    vs_out.ourTexCoords = texCoord;
    gl_Position = projection * view *  model * vec4(position, 1.0);
} 