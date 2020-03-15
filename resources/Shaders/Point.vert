#version 330 core
layout (location = 0) in vec2 viPos;
layout (location = 1) in vec4 viColor;
uniform mat4 vuProjection;
out vec4 voColor;
void main()
{
   gl_Position = vuProjection * vec4(viPos.xy, 0.0, 1.0);
   voColor = viColor;
}