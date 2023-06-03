#pragma once

#include "window.hpp"
#include "pipeline.hpp"
#include "device.hpp"

class Application
{
public:
    static constexpr int WIDTH = 800;
    static constexpr int HEIGHT = 600;

    void run();

private:
    Window window{WIDTH, HEIGHT, "Hello Vulkan!"};
    Device device{window};
    Pipeline pipeline{device, "../../src/shaders/vert.spv", "../../src/shaders/frag.spv", Pipeline::defaultPipelineConfigInfo(WIDTH, HEIGHT)};
};