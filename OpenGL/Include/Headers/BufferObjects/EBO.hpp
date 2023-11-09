#pragma once

class EBO
{
public:
    EBO() {}
    ~EBO();

    void Create();

    void PushData(const void* data, const unsigned int& size);
    
    void Bind();

    static void Unbind();

    void Delete();
    
private:
    unsigned int m_ebo = 0;
};