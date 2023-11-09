#include "Headers/Game/Game.hpp"
#include "Headers/Utility/Logger.hpp"

int main(int argc, char** argv)
{
    Game game("Game Engine", 800, 800);

    float oldTime = (float)glfwGetTime();

    while (game.Run())
    {
        float newTime = (float)glfwGetTime();
        float elapsedTime = newTime - oldTime;
        oldTime = newTime;

        game.HandleEvents();
        game.Update(elapsedTime);
        game.Draw();
        glfwPollEvents();
    }

    return 0;
}