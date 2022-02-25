// #version 330 core
// layout (location = 0) in vec3 aPos;
// layout (location = 1) in vec3 aColor;
// uniform float offset;
// out vec3 ourColor;
// void main()
// {
//    gl_Position = vec4(aPos.x + offset, aPos.y, aPos.z, 1.0);
//    ourColor = aColor;
// }

#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aColor;

out vec3 ourColor;
//out vec3 ourPosition;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    //ourColor = aColor;
    //ourPosition = aPos;
    TexCoord = aTexCoord;
    ourColor = aColor;
}
