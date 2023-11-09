#include "Headers/BufferObjects/VBO.hpp"

#include "Headers/Utility/Util.hpp"
#include "Headers/Utility/Logger.hpp"
#include "Headers/Utility/Error.hpp"

VBO::~VBO()
{
    Delete();
}

void VBO::Create()
{
    if (m_vbo > 0)
    {
        Logger::Warn("Can't overwrite a VBO that's already created!");
        return;
    }

    GLCall(glGenBuffers(1, &m_vbo));
}

void VBO::PushData(const void* data, const unsigned int& size)
{
    if (m_vbo == 0)
    {
        Logger::Warn("Can't push data to VBO that's not created!");
        return;
    }

    Bind();

    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
    
    Unbind();
}

void VBO::Bind()
{
    if (m_vbo == 0)
    {
        Logger::Warn("Can't bind an uncreated VBO!");
        return;
    }
 
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
}

void VBO::SetAttribute(const unsigned int& index, const int& componentSize, const unsigned int& attribType, const int& stride, const void* offset)
{
    GLCall(glVertexAttribPointer(index, componentSize, attribType, GL_FALSE, stride, offset));
    GLCall(glEnableVertexAttribArray(index));
}

void VBO::DisableAttribute(const unsigned int& index)
{
    GLCall(glEnableVertexAttribArray(index));
}

void VBO::Unbind()
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void VBO::Delete()
{
    if (m_vbo == 0)
        return;

    GLCall(glDeleteBuffers(1, &m_vbo));
    m_vbo = 0;
}
