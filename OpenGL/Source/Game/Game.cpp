#include "Headers/Game/Game.hpp"

#include "Headers/Utility/Util.hpp"
#include "Headers/Utility/Logger.hpp"
#include "Headers/Utility/Error.hpp"

#include "stb/stb_image.h"

Game::Game(const char* title, const int& width, const int& height)
    : m_run(true), m_width(width), m_height(height), m_title(title)
{
    glfwInitHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    if (!initGLFW())
    {
        const char* x = nullptr;
        glfwGetError(&x);
        Logger::Error("Failed to initialise GLFW! Error: %s", x);
        m_run = false;
        return;
    }

    m_window = glfwCreateWindow(width, height, title, NULL, NULL);

    glfwMakeContextCurrent(m_window);

    if (!initOpenGL())
    {
        Logger::Error("Failed to initialise OpenGL!");
        m_run = false;
        return;
    }

    float vertices[] = {
        -0.5f, -0.5f, -0.5f, // back bottom left   0
         0.5f, -0.5f, -0.5f, // back bottom right  1
        -0.5f,  0.5f, -0.5f, // back top left      2
         0.5f,  0.5f, -0.5f, // back top right     3
        -0.5f, -0.5f,  0.5f, // front bottom left  4
         0.5f, -0.5f,  0.5f, // front bottom right 5
        -0.5f,  0.5f,  0.5f, // front top left     6
         0.5f,  0.5f,  0.5f  // front top right    7
    };

    unsigned int indices[] = {
        // front
        4, 6, 7,
        4, 7, 5,

        // left
        0, 3, 6,
        0, 6, 4,

        // back
        1, 3, 2,
        1, 2, 0,
        
        // right
        5, 6, 3,
        5, 3, 1,

        // top
        6, 2, 3,
        6, 3, 7,

        // bottom
        0, 4, 5,
        0, 5, 1
    };

    m_tex1.LoadTexture("./Resources/Textures/default.jpg");

    glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* window, int width, int height)
        {
            glViewport(0, 0, width, height);
        });

    m_objShader = new ObjectShader();
    m_lightShader = new LightShader();
    m_skyboxShader = new SkyboxShader();

    if (!m_objShader->Create())
        Logger::Error("Failed to create ObjectShader!");
    if (!m_lightShader->Create())
        Logger::Error("Failed to create LightShader!");
    if (!m_skyboxShader->Create())
        Logger::Error("Failed to create SkyboxShader!");

    GLCall(glEnable(GL_DEPTH_TEST));
    
    /*
    GLCall(glEnable(GL_CULL_FACE));
    GLCall(glCullFace(GL_FRONT));
    */

    m_mesh.LoadOBJFile("./Resources/Models/CUBE.obj");

    glfwSwapInterval(0);

    m_vao.Create();
    m_vbo.Create();
    m_ebo.Create();

    m_vbo.PushData(vertices, sizeof(vertices));
    m_ebo.PushData(indices, sizeof(indices));

    m_vao.Bind();

    m_vbo.Bind();
    m_vbo.SetAttribute(0, 3, GL_FLOAT, sizeof(float) * 3, (void*)0);
    m_ebo.Bind();

    m_vao.Unbind();

    if (!m_skybox.LoadSkybox("./Resources/Textures/EddySkybox"))
        Logger::Error("Failed to load skybox!");
}

Game::~Game()
{
    m_vao.Delete();
    
    m_vbo.Delete();

    m_ebo.Delete();

    m_tex1.Delete();

    m_skybox.Delete();

    m_mesh.Delete();

    if (m_objShader)
        delete m_objShader;
    if (m_lightShader)
        delete m_lightShader;

    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void Game::HandleEvents()
{
    if (glfwGetKey(m_window, GLFW_KEY_ESCAPE))  
    {
        glfwSetWindowShouldClose(m_window, 1);
        return;
    }

    m_cam.HandleEvents(m_window);
}

void Game::Update(float deltaTimeS)
{
    m_run = !glfwWindowShouldClose(m_window);

    glfwGetWindowSize(m_window, &m_width, &m_height);

    int fps = 1.0f / deltaTimeS;

    std::string newTitle = m_title;

    newTitle += " [FPS] ";
    newTitle += std::to_string(fps);

    glfwSetWindowTitle(m_window, newTitle.c_str());

    m_theta += deltaTimeS * 1.0f;

    m_cam.Update(deltaTimeS);
}

void Game::Draw()
{
    GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f)) * glm::rotate(glm::mat4(1.0f), m_theta, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 viewMatrx = glm::mat4(1.0f);
    glm::mat4 projectionMatrix = glm::perspective(90.0f, (float)m_width / (float)m_height, 0.1f, 1000.0f);

    glm::vec3 lightColour(1.0f, 1.0f, 1.0f);
    glm::vec3 lightPos(0.0f, 5.0f, 0.0f);

    if (m_objShader)
    {
        m_objShader->Bind();

        m_objShader->SetModelMat(modelMatrix);
        m_objShader->SetViewMat(m_cam.GetViewMatrix());
        m_objShader->SetProjMat(projectionMatrix);

        m_objShader->SetCamPos(m_cam.GetPos());
        m_objShader->SetLightColour(lightColour);
        m_objShader->SetLightPos(lightPos);

        m_objShader->SetVec3Uniform("uMaterial.ambient", glm::vec3(1.0f, 0.5f, 0.31f));
        m_objShader->SetVec3Uniform("uMaterial.diffuse", glm::vec3(1.0f, 0.5f, 0.31f));
        m_objShader->SetVec3Uniform("uMaterial.specular", glm::vec3(0.5f, 0.5f, 0.5f));
        m_objShader->SetFloatUniform("uMaterial.shininess", 32);

        m_objShader->SetTextureUnit(0);
    }

    // Render object

    m_tex1.Bind(0);
    
    m_mesh.Draw(*m_objShader);

    if (m_lightShader)
    {
        m_lightShader->Bind();
        m_lightShader->SetModelMat(glm::translate(glm::mat4(1.0f), lightPos));
        m_lightShader->SetViewMat(m_cam.GetViewMatrix());
        m_lightShader->SetProjMat(projectionMatrix);
        m_lightShader->SetLightColour(lightColour);
    }
    
    // Render light source

    m_vao.Bind();

    GLCall(glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0));

    m_vao.Unbind();

    // Render skybox

    if (m_skyboxShader)
    {
        m_skyboxShader->Bind();
        m_skyboxShader->SetProjMat(projectionMatrix);
        m_skyboxShader->SetViewMat(glm::mat4(glm::mat3(m_cam.GetViewMatrix())));
    }

    m_skybox.Draw(*m_skyboxShader);

    glfwSwapBuffers(m_window);
}