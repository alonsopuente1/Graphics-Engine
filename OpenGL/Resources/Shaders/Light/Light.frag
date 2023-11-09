#version 460 core

out vec4 FragColour;

uniform vec3 uLightColour;

void main()
{
  FragColour = vec4(uLightColour, 1.0f);
}