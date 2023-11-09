#pragma once

#include "Headers/Shader/Shader.hpp"
#include "glm/glm.hpp"

class LightShader : public Shader
{
    
public:
    LightShader();

    virtual bool Create();

    void SetModelMat(const glm::mat4& mat);
    void SetViewMat(const glm::mat4& mat);
    void SetProjMat(const glm::mat4& mat);
    void SetLightColour(const glm::vec3& vec);
private:
    int m_modelMatUniformLoc    = 0;
    int m_viewMatUniformLoc     = 0;
    int m_projMatUniformLoc     = 0;
    int m_lightColourUniformLoc = 0;
};
