#include "application.hpp"

void Application::run()
{
    while (!window.shouldClose())
    {
        glfwPollEvents();
    }
}