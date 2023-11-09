#pragma once

class VBO
{
public:
    VBO() {}
    ~VBO();

    void Create();

    void PushData(const void* data, const unsigned int& size);

    void Bind();
    
    void SetAttribute(const unsigned int& index, const int& componentSize, const unsigned int& attribType, const int& stride, const void* offset);

    void DisableAttribute(const unsigned int& index);

    static void Unbind();

    void Delete();

private:
    unsigned int m_vbo = 0;
};