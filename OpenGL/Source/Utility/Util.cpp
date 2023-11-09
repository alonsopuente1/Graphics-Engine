#include "Headers/Utility/Util.hpp"

#include "Headers/Utility/Logger.hpp"

bool initGLFW()
{
    return glfwInit();
}

std::string ReadFile(const char* filePath)
{
    std::fstream file(filePath);
    std::string output = "";

    if (!file.is_open())
    {
        Logger::Error("File %s is not open", filePath);
        return output;
    }

    std::stringstream stream;
    stream << file.rdbuf();

    output = stream.str();

    file.close();

    return output;
}
