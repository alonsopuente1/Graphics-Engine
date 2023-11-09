#include "Headers/Skybox/Skybox.hpp"

#include "Headers/Utility/Util.hpp"
#include "Headers/Utility/Logger.hpp"
#include "Headers/Utility/Error.hpp"

#include "stb/stb_image.h"

Skybox::Skybox()
{
}

Skybox::~Skybox()
{
    Delete();
}

bool Skybox::LoadSkybox(const char* folderPath)
{
    Delete();

    GLCall(glGenTextures(1, &m_texture));
    GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture));

    GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    std::string path = folderPath;

    std::string faceCubeMap[] = {
       path + "/right.jpg",
       path + "/left.jpg",
       path + "/top.jpg",
       path + "/bottom.jpg",
       path + "/front.jpg",
       path + "/back.jpg"
    };

    stbi_set_flip_vertically_on_load(false);
   
    for (int i = 0; i < 6; i++)
    {
        int width, height, numChannels;
        unsigned char* data = stbi_load(faceCubeMap[i].c_str(), &width, &height, &numChannels, 0);
        Logger::Debug("Skybox texture channels: %i", numChannels);
        if (data)
        {
            GLCall(glTexImage2D(
                GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0,
                GL_RGB,
                width,
                height,
                0,
                GL_RGB,
                GL_UNSIGNED_BYTE,
                data
            ));

            stbi_image_free(data);
        }
        else
        {
            Logger::Error("Failed to load image %s", faceCubeMap[i].c_str());
            Delete();
            return false;
        }
    }

    float vertices[] = {
        -0.5f, -0.5f, -0.5f, // back bottom left   0
         0.5f, -0.5f, -0.5f, // back bottom right  1
        -0.5f,  0.5f, -0.5f, // back top left      2
         0.5f,  0.5f, -0.5f, // back top right     3
        -0.5f, -0.5f,  0.5f, // front bottom left  4
         0.5f, -0.5f,  0.5f, // front bottom right 5
        -0.5f,  0.5f,  0.5f, // front top left     6
         0.5f,  0.5f,  0.5f  // front top right    7
    };

    unsigned int indices[] = {
        // front
        7, 6, 4,
        5, 7, 4,

        // left
        6, 3, 0,
        4, 6, 0,

        // back
        2, 3, 1,
        0, 2, 1,

        // right
        3, 6, 5,
        1, 3, 5,

        // top
        3, 2, 6,
        7, 3, 6,

        // bottom
        5, 4, 0,
        1, 5, 0
    };

    m_vao.Create();
    m_vbo.Create();
    m_ebo.Create();

    m_vbo.PushData(vertices, sizeof(vertices));
    m_ebo.PushData(indices, sizeof(indices));

    m_vao.Bind();

    m_vbo.Bind();
    m_vbo.SetAttribute(0, 3, GL_FLOAT, sizeof(float) * 3, (void*)0);
    m_ebo.Bind();

    m_vao.Unbind();

    m_vbo.Unbind();
    m_ebo.Unbind();

    return true;
}



void Skybox::Bind(unsigned int texUnit)
{
    if (m_texture == 0)
    {
        Logger::Warn("Can't bind uncreated texture!");
        return;
    }

    if (texUnit > 31)
    {
        Logger::Warn("Can't bind to texture unit above 31!");
        return;
    }

    GLCall(glActiveTexture(GL_TEXTURE0 + texUnit));
    GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture));
}

void Skybox::Draw(SkyboxShader& shader)
{
    shader.Bind();
    shader.SetSkyboxUnit(0);
    
    Bind(0);

    m_vao.Bind();
    GLCall(glDepthFunc(GL_LEQUAL));
    GLCall(glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0));
    GLCall(glDepthFunc(GL_LESS));
    m_vao.Unbind();
}

void Skybox::Delete()
{
    m_vao.Delete();
    m_vbo.Delete();
    m_ebo.Delete();

    if (m_texture == 0)
        return;

    GLCall(glDeleteTextures(1, &m_texture));
    m_texture = 0;

}