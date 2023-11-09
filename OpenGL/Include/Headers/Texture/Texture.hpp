#pragma once

class Texture
{

public:
    Texture() {}

    ~Texture();

    void Create();

    void Bind(unsigned int texUnit);

    void LoadTexture(const char* texturePath);

    void Delete();

    static void Unbind(unsigned int texUnit);

private:

    unsigned int m_texture = 0;

};

