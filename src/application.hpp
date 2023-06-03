#pragma once

#include "window.hpp"

class Application
{
public:
    static constexpr int WIDTH = 800;
    static constexpr int HEIGHT = 600;

    void run();

private:
    Window window{WIDTH, HEIGHT, "Hello Vulkan!"};
};