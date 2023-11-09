#version 460 core

out vec4 FragColour;

in vec3 texCoord;

uniform samplerCube uSkybox;

void main()
{
  FragColour = texture(uSkybox, texCoord);
}