#pragma once

#include <vector>

class Shader
{

public:
    Shader();
    virtual ~Shader();

    virtual bool Create();

    void Bind();

    void Delete();
protected:

    bool AddShader(const unsigned int& shaderType, const char* filePath);

    bool Compile();

    int GetUniformLocation(const char* uniformName);

    unsigned int m_shaderProgram = 0;
private:
    std::vector<unsigned int> m_shaderObjects;

    void DeleteShaderObjects();

};