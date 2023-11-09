#include "Headers/Shader/SkyboxShader.hpp"

#include "Headers/Utility/Util.hpp"
#include "Headers/Utility/Error.hpp"

#include "glm/ext.hpp"

SkyboxShader::SkyboxShader()
{
}

bool SkyboxShader::Create()
{
    if (!Shader::Create())
        return false;
    if (!AddShader(GL_VERTEX_SHADER, "./Resources/Shaders/Skybox/Skybox.vert"))
        return false;
    if (!AddShader(GL_FRAGMENT_SHADER, "./Resources/Shaders/Skybox/Skybox.frag"))
        return false;
    if (!Compile())
        return false;

    m_viewMatUniformLoc = GetUniformLocation("uView");
    m_projMatUniformLoc = GetUniformLocation("uProj");
    m_skyboxUniformLoc  = GetUniformLocation("uSkybox");

    return true;
}

void SkyboxShader::SetViewMat(const glm::mat4& mat)
{
    GLCall(glUniformMatrix4fv(m_viewMatUniformLoc, 1, GL_FALSE, glm::value_ptr(mat)));
}

void SkyboxShader::SetProjMat(const glm::mat4& mat)
{
    GLCall(glUniformMatrix4fv(m_projMatUniformLoc, 1, GL_FALSE, glm::value_ptr(mat)));
}

void SkyboxShader::SetSkyboxUnit(const int& unit)
{
    GLCall(glUniform1i(m_skyboxUniformLoc, unit));
}
