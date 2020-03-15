#version 330 core

in vec2 voTexCoords;
uniform sampler2D fuTexture;
out vec4 foColor;

void main()
{
    foColor = texture(fuTexture, voTexCoords);
}