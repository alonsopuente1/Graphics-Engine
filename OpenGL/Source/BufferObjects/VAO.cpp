#include "Headers/BufferObjects/VAO.hpp"

#include "Headers/Utility/Util.hpp"
#include "Headers/Utility/Logger.hpp"
#include "Headers/Utility/Error.hpp"

VAO::~VAO()
{
    Delete();
}

void VAO::Create()
{
    if (m_vao > 0)
    {
        Logger::Warn("Can't overwrite a VAO that's already created!");
        return;
    }

    GLCall(glGenVertexArrays(1, &m_vao));
}

void VAO::Bind()
{
    if (m_vao == 0)
    {
        Logger::Warn("Can't bind an uncreated VAO!");
        return;
    }

    GLCall(glBindVertexArray(m_vao));
}

void VAO::Delete()
{
    if (m_vao == 0)
        return;

    GLCall(glDeleteVertexArrays(1, &m_vao));
    m_vao = 0;
}

void VAO::Unbind()
{
    GLCall(glBindVertexArray(0));
}
