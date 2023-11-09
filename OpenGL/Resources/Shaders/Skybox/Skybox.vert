#version 460 core

layout (location = 0) in vec3 aPos;

uniform mat4 uView;
uniform mat4 uProj;

out vec3 texCoord;

void main()
{
  vec4 newPos = uProj * uView * vec4(aPos, 1.0f);

  texCoord = vec3(aPos.x, aPos.y, -aPos.z);

  gl_Position = newPos.xyww;
}