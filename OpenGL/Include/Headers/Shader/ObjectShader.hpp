#pragma once

#include "Headers/Shader/Shader.hpp"
#include "glm/glm.hpp"
#include "glm/ext.hpp"

class ObjectShader : public Shader
{

public:
    ObjectShader();
    
    virtual bool Create();

    void SetModelMat(const glm::mat4& mat);
    void SetViewMat(const glm::mat4& mat);
    void SetProjMat(const glm::mat4& mat);
    void SetTextureUnit(int texUnit);

    void SetLightColour(const glm::vec3& vec);
    void SetLightPos(const glm::vec3& vec);
    void SetCamPos(const glm::vec3& vec);

    void SetVec3Uniform(const char* uniformName, const glm::vec3& vec);
    void SetIntUniform(const char* uniformName, const int& num);
    void SetFloatUniform(const char* uniformName, const float& num);
private:
    int m_modelMatUniformLoc    = 0;
    int m_viewMatUniformLoc     = 0;
    int m_projMatUniformLoc     = 0;
    int m_texSamplerUniformLoc  = 0;
    int m_lightColourUniformLoc = 0;
    int m_lightPosUniformLoc    = 0;
    int m_camPosUniformLoc      = 0;
};