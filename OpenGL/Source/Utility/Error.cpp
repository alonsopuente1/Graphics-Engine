#include "Headers/Utility/Error.hpp"

#include "Headers/Utility/Logger.hpp"
#include "Headers/Utility/Util.hpp"

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, const int& line) 
{
    while (GLenum error = glGetError())
    {
        Logger::Warn("OpenGL Error (%x): Function %s in file %s on line %i", error, function, file, line);
        return false;
    }
    return true;
}
