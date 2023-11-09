#include "Headers/Shader/ObjectShader.hpp"

#include "Headers/Utility/Util.hpp"
#include "Headers/Utility/Error.hpp"

ObjectShader::ObjectShader()
{
}

bool ObjectShader::Create()
{
    if (!Shader::Create())
        return false;

    if (!AddShader(GL_VERTEX_SHADER, "./Resources/Shaders/Basic/Basic.vert"))
        return false;
    
    if (!AddShader(GL_FRAGMENT_SHADER, "./Resources/Shaders/Basic/Basic.frag"))
        return false;

    if (!Compile())
        return false;

    m_modelMatUniformLoc = GetUniformLocation("uModel");
    m_viewMatUniformLoc = GetUniformLocation("uView");
    m_projMatUniformLoc = GetUniformLocation("uProj");
    m_texSamplerUniformLoc = GetUniformLocation("texture1");
    m_lightColourUniformLoc = GetUniformLocation("uLightColour");
    m_lightPosUniformLoc = GetUniformLocation("uLightPos");
    m_camPosUniformLoc = GetUniformLocation("uCamPos");
    
    return true;
}

void ObjectShader::SetModelMat(const glm::mat4& mat)
{
    GLCall(glUniformMatrix4fv(m_modelMatUniformLoc, 1, GL_FALSE, glm::value_ptr(mat)));
}

void ObjectShader::SetViewMat(const glm::mat4& mat)
{
    GLCall(glUniformMatrix4fv(m_viewMatUniformLoc, 1, GL_FALSE, glm::value_ptr(mat)));
}

void ObjectShader::SetProjMat(const glm::mat4& mat)
{
    GLCall(glUniformMatrix4fv(m_projMatUniformLoc, 1, GL_FALSE, glm::value_ptr(mat)));
}

void ObjectShader::SetTextureUnit(int texUnit)
{
    GLCall(glUniform1i(m_texSamplerUniformLoc, texUnit));
}

void ObjectShader::SetLightColour(const glm::vec3& vec)
{
    GLCall(glUniform3f(m_lightColourUniformLoc, vec.x, vec.y, vec.z));
}

void ObjectShader::SetLightPos(const glm::vec3& vec)
{
    GLCall(glUniform3f(m_lightPosUniformLoc, vec.x, vec.y, vec.z));
}

void ObjectShader::SetCamPos(const glm::vec3& vec)
{
    GLCall(glUniform3f(m_camPosUniformLoc, vec.x, vec.y, vec.z));
}

void ObjectShader::SetVec3Uniform(const char* uniformName, const glm::vec3& vec)
{
    GLCall(glUniform3f(GetUniformLocation(uniformName), vec.x, vec.y, vec.z));
}

void ObjectShader::SetFloatUniform(const char* uniformName, const float& num)
{
    GLCall(glUniform1f(GetUniformLocation(uniformName), num));
}

void ObjectShader::SetIntUniform(const char* uniformName, const int& num)
{
    GLCall(glUniform1i(GetUniformLocation(uniformName), num));
}
