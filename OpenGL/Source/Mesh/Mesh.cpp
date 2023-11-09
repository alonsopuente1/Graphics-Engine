#include "Headers/Mesh/Mesh.hpp"

#include <fstream>
#include <string>
#include <sstream>

#include "Headers/Utility/Util.hpp"
#include "Headers/Utility/Logger.hpp"
#include "Headers/Utility/Error.hpp"

Mesh::~Mesh()
{
    Delete();
}

std::vector<std::string> split(const std::string &in, const std::string& token)
{
    std::vector<std::string> out;
    
    out.clear();
    
    std::string temp;
    
    for (int i = 0; i < int(in.size()); i++)
    {
        std::string test = in.substr(i, token.size());
    
        if (test == token)
        {
            if (!temp.empty())
            {
                out.push_back(temp);
                temp.clear();
                i += (int)token.size() - 1;
            }
            else
            {
                out.push_back("");
            }
        }
        else if (i + token.size() >= in.size())
        {
            temp += in.substr(i, token.size());
            out.push_back(temp);
            break;
        }
        else
        {
            temp += in[i];
        }
    }

    return out;
}

void Mesh::Draw(ObjectShader& shader)
{
    shader.Bind();
    m_vao.Bind();
    GLCall(glDrawArrays(GL_TRIANGLES, 0, m_vertexCount));
    m_vao.Unbind();
}

void Mesh::LoadOBJFile(const char* filePath)
{
    std::fstream file(filePath);

    if (!file.is_open())
    {
        Logger::Error("Failed to open file %s!", filePath);
        return;
    }

    std::string curLine = "";
    
    struct vec3
    {
        float p[3] = { 0.0f };
    };

    struct vec2
    {
        float p[2] = { 0.0f };
    };

    struct Vertex
    {
        vec3 p;
        vec2 t;
        vec3 n;
    };

    std::vector<vec3> tempPositions;
    std::vector<vec2> tempTexCoords;
    std::vector<vec3> tempNormals;

    tempPositions.reserve(100);
    tempTexCoords.reserve(100);
    tempNormals.reserve(100);

    std::vector<Vertex> vertices;

    while (std::getline(file, curLine))
    {
        std::stringstream stream;
        stream << curLine;

        std::string temp = "";

        stream >> temp;

        if (temp == "#")
            continue;

        if (temp == "v")
        {   
            vec3 temp;

            stream >> temp.p[0] >> temp.p[1] >> temp.p[2];

            tempPositions.push_back(temp);
        }

        else if (temp == "vt")
        {
            vec2 temp;

            stream >> temp.p[0] >> temp.p[1];

            tempTexCoords.push_back(temp);
        }

        else if (temp == "vn")
        {
            vec3 temp;

            stream >> temp.p[0] >> temp.p[1] >> temp.p[2];

            tempNormals.push_back(temp);
        }

        else if (temp == "f")
        {
            Vertex tempVert;

            for (int i = 0; i < 3; i++)
            {
                stream >> temp;

                std::vector<std::string> indices = split(temp, "/");

                
                if (indices.size() == 1)
                {
                    tempVert.p = tempPositions[std::stoi(indices[0]) - 1];
                }
                else if (indices.size() == 2)
                {
                    if (tempNormals.size() == 0)
                    {
                        tempVert.p = tempPositions[std::stoi(indices[0]) - 1];
                        tempVert.t = tempTexCoords[std::stoi(indices[1]) - 1];
                    }
                    else
                    {
                        tempVert.p = tempPositions[std::stoi(indices[0]) - 1];
                        tempVert.n = tempNormals[std::stoi(indices[1]) - 1];
                    }
                }
                else if (indices.size() == 3)
                {
                    tempVert.p = tempPositions[std::stoi(indices[0]) - 1];
                    tempVert.t = tempTexCoords[std::stoi(indices[1]) - 1];
                    tempVert.n = tempNormals[std::stoi(indices[2]) - 1];
                }

                vertices.push_back(tempVert);
            }
        }
    }

    m_vao.Delete();
    m_vao.Create();

    m_vbo.Delete();
    m_vbo.Create();

    m_vbo.PushData(vertices.data(), vertices.size() * sizeof(Vertex));

    m_vao.Bind();

    m_vbo.Bind();

    m_vbo.SetAttribute(0, 3, GL_FLOAT, sizeof(Vertex), (void*)(0));
    
    if (tempTexCoords.size())
        m_vbo.SetAttribute(1, 2, GL_FLOAT, sizeof(Vertex), (void*)(sizeof(Vertex::p)));
    else
        m_vbo.DisableAttribute(1);

    if (tempNormals.size())
        m_vbo.SetAttribute(2, 3, GL_FLOAT, sizeof(Vertex), (void*)(sizeof(Vertex::p) + sizeof(Vertex::t)));
    else
        m_vbo.DisableAttribute(2);

    m_vao.Unbind();

    m_vbo.Unbind();

    m_vertexCount = vertices.size();

    file.close();
}

void Mesh::Delete()
{
    m_vao.Delete();
    m_vbo.Delete();
}
