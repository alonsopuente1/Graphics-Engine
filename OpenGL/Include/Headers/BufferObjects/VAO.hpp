#pragma once

class VAO
{
public:
    VAO() {}
    ~VAO();

    void Create();

    void Bind();

    static void Unbind();
    
    void Delete();
private:
    unsigned int m_vao = 0;
};