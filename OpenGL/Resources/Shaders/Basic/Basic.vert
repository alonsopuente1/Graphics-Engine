#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;
layout (location = 2) in vec3 aNorm;

out vec2 texCoord;
out vec3 normal;
out vec3 crntPos;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProj;

void main()
{
  crntPos = vec3(uModel * vec4(aPos, 1.0f));
  normal = mat3(transpose(inverse(uModel))) * aNorm;

  gl_Position = uProj * uView * uModel * vec4(aPos, 1.0f);
  texCoord = aTex;
}