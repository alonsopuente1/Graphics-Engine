#version 460 core

struct Material
{

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float shininess;

};

out vec4 FragColour;

in vec2 texCoord;
in vec3 normal;
in vec3 crntPos;

uniform sampler2D texture1;
uniform vec3 uLightColour;
uniform vec3 uLightPos;
uniform vec3 uCamPos;
uniform Material uMaterial;

void main()
{
  // ambient
  vec3 ambient = uMaterial.ambient * uLightColour;

  // diffuse
  vec3 newNormal = normalize(normal);
  vec3 lightDir = normalize(uLightPos - crntPos);
  float diffStrength = max(dot(normal, lightDir), 0.0f);
  vec3 diffuse = (uMaterial.diffuse * diffStrength) * uLightColour;

  // specular light
  vec3 viewDir = normalize(uCamPos - crntPos);
  vec3 reflectDir = reflect(-lightDir, normal);
  float specAmount = pow(max(dot(viewDir, reflectDir), 0.0f), uMaterial.shininess);
  vec3 specular = (uMaterial.specular * specAmount) * uLightColour;

  FragColour = texture(texture1, texCoord) * vec4(diffuse + ambient + specular, 1.0f);
}