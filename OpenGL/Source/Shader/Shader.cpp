#include "Headers/Shader/Shader.hpp"

#include "Headers/Utility/Util.hpp"
#include "Headers/Utility/Logger.hpp"
#include "Headers/Utility/Error.hpp"

Shader::Shader()
{
    m_shaderProgram = 0;
    m_shaderObjects.reserve(5);
}

Shader::~Shader()
{
    Delete();
}

bool Shader::Create()
{
    GLCall(m_shaderProgram = glCreateProgram());

    if (m_shaderProgram == 0)
        return false;

    return true;
}

void Shader::Bind()
{
    GLCall(glUseProgram(m_shaderProgram));
}

void Shader::Delete()
{
    DeleteShaderObjects();

    if (m_shaderProgram == 0)
        return;

    GLCall(glDeleteProgram(m_shaderProgram));
    m_shaderProgram = 0;
}

bool Shader::AddShader(const unsigned int& shaderType, const char* filePath)
{
    unsigned int shader = 0;
    GLCall(shader = glCreateShader(shaderType));

    if (shader == 0)
    {
        Logger::Error("Failed to create shader!");
        return false;
    }

    std::string shaderSource = ReadFile(filePath);

    if (shaderSource == "")
    {
        GLCall(glDeleteShader(shader));
        return false;
    }

    const char* cstrShaderSource = shaderSource.c_str();

    GLCall(glShaderSource(shader, 1, &cstrShaderSource, nullptr));

    GLCall(glCompileShader(shader));

    int success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        char infoLog[512];

        GLCall(glGetShaderInfoLog(shader, sizeof(infoLog), NULL, infoLog));

        Logger::Error("Failed to compile shader at file '%s'", filePath);
        Logger::Error("Shader error: %s", infoLog);

        GLCall(glDeleteShader(shader));
        return false;
    }
    
    m_shaderObjects.push_back(shader);

    GLCall(glAttachShader(m_shaderProgram, shader));

    return true;
}

bool Shader::Compile()
{
    GLCall(glLinkProgram(m_shaderProgram));

    int success = 0;
    char infoLog[512];

    GLCall(glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success));

    if (!success)
    {
        GLCall(glGetProgramInfoLog(m_shaderProgram, sizeof(infoLog), nullptr, infoLog));

        Logger::Error("Failed to link program: %s", infoLog);
        return false;
    }

    GLCall(glValidateProgram(m_shaderProgram));
    GLCall(glGetProgramiv(m_shaderProgram, GL_VALIDATE_STATUS, &success));

    if (!success)
    {
        GLCall(glGetProgramInfoLog(m_shaderProgram, sizeof(infoLog), nullptr, infoLog));

        Logger::Error("Invalid program: %s", infoLog);
        return false;
    }

    DeleteShaderObjects();

    return true;
}

int Shader::GetUniformLocation(const char* uniformName)
{
    GLCall(int location = glGetUniformLocation(m_shaderProgram, uniformName));
    
    if (location == -1)
    {
        Logger::Warn("Uniform %s doesn't exist!", uniformName);
        return -1;
    }

    return location;
}

void Shader::DeleteShaderObjects()
{
    for (int i = 0; i < m_shaderObjects.size(); i++)
    {
        if (m_shaderObjects[i] == 0)
            continue;
        
        GLCall(glDeleteShader(m_shaderObjects[i]));
        m_shaderObjects[i] = 0;
    }

    m_shaderObjects.clear();
}