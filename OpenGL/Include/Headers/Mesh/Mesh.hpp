#pragma once

#include "Headers/BufferObjects/VBO.hpp"
#include "Headers/BufferObjects/VAO.hpp"

#include "Headers/Shader/ObjectShader.hpp"

class Mesh
{
public:
    Mesh() {}

    ~Mesh();

    void Draw(ObjectShader& shader);

    void LoadOBJFile(const char* filePath);

    void Delete();
private:
    VBO m_vbo;
    VAO m_vao;
  
    int m_vertexCount = 0;

};