#include "Headers/Texture/Texture.hpp"

#include "Headers/Utility/Util.hpp"
#include "Headers/Utility/Logger.hpp"
#include "Headers/Utility/Error.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

Texture::~Texture()
{
    Delete();
}

void Texture::Create()
{
    if (m_texture != 0)
    {
        Logger::Warn("Can't overwrite a texture that's already created!");
        return;
    }

    GLCall(glGenTextures(1, &m_texture));
}

void Texture::Bind(unsigned int texUnit)
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
    GLCall(glBindTexture(GL_TEXTURE_2D, m_texture));
}

void Texture::LoadTexture(const char* texturePath)
{
    int width, height, numChannels;

    stbi_set_flip_vertically_on_load(1);

    unsigned char* img = stbi_load(texturePath, &width, &height, &numChannels, 0);

    if (!img)
    {
        Logger::Error("Failed to load texture! File path %s", texturePath);
        return;
    }

    Delete();

    Create();

    Bind(0);

    Logger::Debug("Num channels in texture: %i", numChannels);

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT));

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img));
    GLCall(glGenerateMipmap(GL_TEXTURE_2D));

    stbi_image_free(img);
}

void Texture::Delete()
{
    if (m_texture == 0)
        return;

    GLCall(glDeleteTextures(1, &m_texture));
    m_texture = 0;
}

void Texture::Unbind(unsigned int texUnit)
{
    GLCall(glActiveTexture(GL_TEXTURE0 + texUnit));
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
