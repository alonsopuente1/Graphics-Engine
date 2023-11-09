#pragma once

#include "Headers/Utility/Util.hpp"
#include "glm/glm.hpp"
#include "glm/ext.hpp"

#define W_KEY     0
#define A_KEY     1
#define S_KEY     2
#define D_KEY     3
#define RIGHT_KEY 4
#define LEFT_KEY  5
#define UP_KEY    6
#define DOWN_KEY  7
#define SPACE_KEY 8
#define SHIFT_KEY 9

#define NUM_KEYS 10

class Camera
{

public:
    Camera();
    Camera(const glm::vec3& pos);

    void HandleEvents(GLFWwindow* window);

    void Update(float deltaTime);

    glm::mat4 GetViewMatrix();

    glm::vec3 GetPos() const;

private:
    glm::vec3 m_pos;
    glm::vec3 m_lookDir;
    const glm::vec3 m_up;

    bool m_keysPressed[NUM_KEYS] = { false };

    void RotateYaw(float angle);
    void RotatePitch(float angle);
};