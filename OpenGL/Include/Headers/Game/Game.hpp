#pragma once

#include "Headers/Utility/Util.hpp"

#include "Headers/BufferObjects/VBO.hpp"
#include "Headers/BufferObjects/VAO.hpp"
#include "Headers/BufferObjects/EBO.hpp"

#include "Headers/Shader/ObjectShader.hpp"
#include "Headers/Shader/LightShader.hpp"
#include "Headers/Shader/SkyboxShader.hpp"

#include "Headers/Skybox/Skybox.hpp"

#include "Headers/Camera/Camera.hpp"

#include "Headers/Texture/Texture.hpp"

#include "Headers/Mesh/Mesh.hpp"

class Game
{

public:
    Game(const char* title, const int& width, const int& height);
    ~Game();

    inline bool Run() const { return m_run; }

    void HandleEvents();
    void Update(float deltaTimeS);
    void Draw();

    

private:
    bool m_run = 0;

    std::string m_title;

    Texture m_tex1;

    VAO m_vao;

    VBO m_vbo;
    
    EBO m_ebo;

    Mesh m_mesh;

    Camera m_cam;

    GLFWwindow* m_window = nullptr;

    ObjectShader* m_objShader = nullptr;
    LightShader* m_lightShader = nullptr;
    SkyboxShader* m_skyboxShader = nullptr;

    Skybox m_skybox;


    int m_width, m_height;

    float m_theta = 0.0f;
};