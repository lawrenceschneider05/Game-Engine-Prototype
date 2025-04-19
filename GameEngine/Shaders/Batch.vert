#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;

out vec4 ourColor;

uniform mat4 P;

void main()
{
    //gl_Position = camMatrix * vec4(aPos, 1.0);
    //gl_Position = vec4(aPos, 1.0);

    gl_Position = (P * vec4(aPos.x, aPos.y, aPos.z, 1.0f));

    ourColor = aColor;
}