#version 330 core
layout (location = 0) in vec2 viPos;
layout (location = 1) in vec2 viTexCoords;
uniform mat4 vuModel;
uniform mat4 vuProjection;
out vec2 voTexCoords;
void main()
{
   gl_Position = vuProjection * vuModel * vec4(viPos.x, viPos.y, 0.0, 1.0);
	voTexCoords = viTexCoords;
}