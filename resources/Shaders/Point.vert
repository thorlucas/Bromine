#version 330 core
layout (location = 0) in vec2 vPos;
layout (location = 1) in vec4 viColor;
out vec4 voColor;
void main()
{
   gl_Position = vec4(vPos.xy, 0.0, 1.0);
   voColor = viColor;
}