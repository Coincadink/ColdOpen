#include "window.hpp"

Window::Window(int w, int h, std::string name) : width{w}, height{h}, windowName{name} 
{
    initWindow();
}

Window::~Window()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Window::initWindow()
{
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // Turn off OpenGL.
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // Disable resizing.

    window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
}
