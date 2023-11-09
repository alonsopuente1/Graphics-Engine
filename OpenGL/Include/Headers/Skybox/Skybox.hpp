#pragma once

#include "Headers/Shader/SkyboxShader.hpp"

#include "Headers/BufferObjects/VAO.hpp"
#include "Headers/BufferObjects/VBO.hpp"
#include "Headers/BufferObjects/EBO.hpp"

class Skybox
{
public:

    Skybox();
    ~Skybox();

    bool LoadSkybox(const char* folderPath);

    void Bind(unsigned int texUnit);

    void Draw(SkyboxShader& shader);

    void Delete();

private:
    unsigned int m_texture = 0;

    VAO m_vao;
    VBO m_vbo;
    EBO m_ebo;
};