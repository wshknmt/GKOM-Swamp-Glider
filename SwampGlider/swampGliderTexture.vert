#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texCoord;
layout (location = 3) in vec3 normal;

out vec2 ourTexCoord;
out vec3 fragPos;
out vec3 ourNormal;
  
uniform mat4 model; 
uniform mat4 view; 
uniform mat4 projection; 

void main()
{
    gl_Position = projection * view *  model * vec4(position, 1.0f);
    ourTexCoord = texCoord;

    fragPos = vec3(model * vec4(position, 1.0f));
    ourNormal = mat3(transpose(inverse(model))) * normal;  
} 