#include "Headers/Camera/Camera.hpp"

#include "Headers/Utility/Settings.hpp"

Camera::Camera()
    : m_pos(0.0f, 0.0f, 0.0f), m_lookDir(0.0f, 0.0f, -1.0f), m_up(0.0f, 1.0f, 0.0f)
{}

Camera::Camera(const glm::vec3 & pos)
    : m_pos(pos), m_lookDir(0.0f, 0.0f, -1.0f), m_up(0.0f, 1.0f, 0.0f)
{}

void Camera::HandleEvents(GLFWwindow* window)
{
    m_keysPressed[W_KEY] = glfwGetKey(window, GLFW_KEY_W);
    m_keysPressed[A_KEY] = glfwGetKey(window, GLFW_KEY_A);
    m_keysPressed[S_KEY] = glfwGetKey(window, GLFW_KEY_S);
    m_keysPressed[D_KEY] = glfwGetKey(window, GLFW_KEY_D);
    m_keysPressed[RIGHT_KEY] = glfwGetKey(window, GLFW_KEY_RIGHT);
    m_keysPressed[LEFT_KEY] = glfwGetKey(window, GLFW_KEY_LEFT);
    m_keysPressed[UP_KEY] = glfwGetKey(window, GLFW_KEY_UP);
    m_keysPressed[DOWN_KEY] = glfwGetKey(window, GLFW_KEY_DOWN);
    m_keysPressed[SPACE_KEY] = glfwGetKey(window, GLFW_KEY_SPACE);
    m_keysPressed[SHIFT_KEY] = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT);
}

void Camera::Update(float deltaTime)
{
    if (m_keysPressed[W_KEY])
        m_pos += m_lookDir * MOVE_SPEED * deltaTime;

    if (m_keysPressed[A_KEY])
        m_pos -= glm::normalize(glm::cross(m_lookDir, m_up)) * MOVE_SPEED * deltaTime;
    
    if (m_keysPressed[S_KEY])
        m_pos -= m_lookDir * MOVE_SPEED * deltaTime;
    
    if (m_keysPressed[D_KEY])
        m_pos += glm::normalize(glm::cross(m_lookDir, m_up)) * MOVE_SPEED * deltaTime;

    if (m_keysPressed[RIGHT_KEY])
        RotateYaw(-ROTATE_SPEED * deltaTime);
    if (m_keysPressed[LEFT_KEY])
        RotateYaw(ROTATE_SPEED * deltaTime);
    if (m_keysPressed[UP_KEY])
        RotatePitch(ROTATE_SPEED * deltaTime);
    if (m_keysPressed[DOWN_KEY])
        RotatePitch(-ROTATE_SPEED * deltaTime);

    if (m_keysPressed[SPACE_KEY])
        m_pos.y += MOVE_SPEED * deltaTime;
    if (m_keysPressed[SHIFT_KEY])
        m_pos.y -= MOVE_SPEED * deltaTime;
        
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(m_pos, m_pos + m_lookDir, m_up);
}

glm::vec3 Camera::GetPos() const
{
    return m_pos;
}

void Camera::RotateYaw(float angle)
{
    m_lookDir = glm::rotate(glm::mat4(1.0f), angle, m_up) * glm::vec4(m_lookDir, 0.0f);
}

void Camera::RotatePitch(float angle)
{
    m_lookDir = glm::rotate(glm::mat4(1.0f), angle, glm::cross(m_lookDir, m_up)) * glm::vec4(m_lookDir, 0.0f);
}