#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec4 aColor;

out vec4 ourColor;

uniform mat4 uniformViewProj;

void main()
{
    gl_Position = uniformViewProj * vec4(aPos.xy, 0.0, 1.0);
    ourColor = aColor;
}