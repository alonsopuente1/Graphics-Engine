#include "Headers/BufferObjects/EBO.hpp"

#include "Headers/Utility/Util.hpp"
#include "Headers/Utility/Error.hpp"
#include "Headers/Utility/Logger.hpp"


EBO::~EBO()
{
    Delete();
}

void EBO::Create()
{
    if (m_ebo > 0)
    {
        Logger::Warn("Can't overwrite an EBO that's already created!");
        return;
    }

    glGenBuffers(1, &m_ebo);
}

void EBO::PushData(const void* data, const unsigned int& size)
{
    if (m_ebo == 0)
    {
        Logger::Warn("Can't push data to EBO that's not created!");
        return;
    }

    Bind();

    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));

    Unbind();
}

void EBO::Bind()
{
    if (m_ebo == 0)
    {
        Logger::Warn("Can't bind an uncreated EBO!");
        return;
    }

    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo));
}

void EBO::Unbind()
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

void EBO::Delete()
{
    if (m_ebo == 0)
        return;

    GLCall(glDeleteBuffers(1, &m_ebo));
    m_ebo = 0;
}
