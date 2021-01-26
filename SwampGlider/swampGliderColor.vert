#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texCoord;
layout (location = 3) in vec3 normal;
  
uniform mat4 model; 
uniform mat4 view; 
uniform mat4 projection; 

out vec4 ourColor;
out vec3 fragPos;
out vec3 ourNormal;

void main()
{
    gl_Position = projection * view *  model * vec4(position, 1.0f);
    ourColor = color;

    fragPos = vec3(model * vec4(position, 1.0f));
    ourNormal = normal; 
}