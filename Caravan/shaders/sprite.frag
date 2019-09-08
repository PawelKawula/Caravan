#version 330 core

out vec4 color;

in vec2 TexCoords;

uniform sampler2D sprite;
uniform vec3 spriteColor;
uniform bool renderColor;

void main()
{
	color = texture(sprite, TexCoords) * vec4(spriteColor, 1.0);
}