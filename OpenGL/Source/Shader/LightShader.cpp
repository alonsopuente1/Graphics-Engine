#include "Headers/Shader/LightShader.hpp"

#include "Headers/Utility/Util.hpp"
#include "Headers/Utility/Error.hpp"

#include "glm/ext.hpp"

LightShader::LightShader()
{
}

bool LightShader::Create()
{
    if (!Shader::Create())
        return false;
    if (!AddShader(GL_VERTEX_SHADER, "./Resources/Shaders/Light/Light.vert"))
        return false;
    if (!AddShader(GL_FRAGMENT_SHADER, "./Resources/Shaders/Light/Light.frag"))
        return false;
    if (!Compile())
        return false;

    m_modelMatUniformLoc = GetUniformLocation("uModel");
    m_viewMatUniformLoc = GetUniformLocation("uView");
    m_projMatUniformLoc = GetUniformLocation("uProj");
    m_lightColourUniformLoc = GetUniformLocation("uLightColour");

    return true;
}

void LightShader::SetModelMat(const glm::mat4& mat)
{
    GLCall(glUniformMatrix4fv(m_modelMatUniformLoc, 1, GL_FALSE, glm::value_ptr(mat)));
}

void LightShader::SetViewMat(const glm::mat4& mat)
{
    GLCall(glUniformMatrix4fv(m_viewMatUniformLoc, 1, GL_FALSE, glm::value_ptr(mat)));
}

void LightShader::SetProjMat(const glm::mat4& mat)
{
    GLCall(glUniformMatrix4fv(m_projMatUniformLoc, 1, GL_FALSE, glm::value_ptr(mat)));
}

void LightShader::SetLightColour(const glm::vec3& vec)
{
    GLCall(glUniform3f(m_lightColourUniformLoc, vec.x, vec.y, vec.z));
}
