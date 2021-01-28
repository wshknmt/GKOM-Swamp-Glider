#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texCoord;
layout (location = 3) in vec3 normal;
  
out VS_OUT{
    vec4 ourColor;
    vec3 fragPos;
    vec3 ourNormal;
} vs_out;

uniform mat4 model; 
uniform mat4 view; 
uniform mat4 projection;

uniform bool reverse_normals;

void main()
{
    vs_out.fragPos = vec3(model * vec4(position, 1.0f));

    if(reverse_normals)
        vs_out.ourNormal = transpose(inverse(mat3(model))) * (-1.0 * normal);
    else
        vs_out.ourNormal = transpose(inverse(mat3(model))) * normal;

    vs_out.ourColor = color;
    gl_Position = projection * view *  model * vec4(position, 1.0f);
}