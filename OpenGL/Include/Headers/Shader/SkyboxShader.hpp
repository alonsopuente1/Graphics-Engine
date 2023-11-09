#pragma once

#include "Headers/Shader/Shader.hpp"

#include "glm/glm.hpp"

class SkyboxShader : public Shader
{
    
public:
    SkyboxShader();

    virtual bool Create();

    void SetViewMat(const glm::mat4& mat);
    void SetProjMat(const glm::mat4& mat);
    void SetSkyboxUnit(const int& unit);
private:
    int m_viewMatUniformLoc = 0;
    int m_projMatUniformLoc = 0;
    int m_skyboxUniformLoc  = 0;
};