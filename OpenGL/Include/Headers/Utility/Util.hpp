#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


#define initOpenGL() (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
bool initGLFW();

std::string ReadFile(const char* filePath);
