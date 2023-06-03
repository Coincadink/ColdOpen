#include "pipeline.hpp"

#include <fstream>
#include <stdexcept>
#include <iostream>

Pipeline::Pipeline(Device& device, const std::string& vertFilepath, const std::string& fragFilepath, const PipelineConfigInfo& configInfo) : device{device}
{
    createGraphicsPipeline(vertFilepath, fragFilepath, configInfo);
}

std::vector<char> Pipeline::readFile(const std::string& filepath)
{
    std::ifstream file{filepath, std::ios::ate | std::ios::binary}; // Open filestream at the end of the file.

    if (!file.is_open()) // Check if filestream opened.
    {
        std::runtime_error("Failed to open file: " + filepath);
    }

    size_t fileSize = static_cast<size_t>(file.tellg()); // Read location to get file size.
    std::vector<char> buffer(fileSize); // Store file size.

    file.seekg(0); // Jump to start of file.
    file.read(buffer.data(), fileSize); // Read file data into buffer.

    file.close(); // Close filestream.
    return buffer;
}

void Pipeline::createGraphicsPipeline(const std::string& vertFilepath, const std::string& fragFilepath, const PipelineConfigInfo& configInfo)
{
    auto vertCode = readFile(vertFilepath);
    auto fragCode = readFile(fragFilepath);

    std::cout << "Vertex shader code size: " << vertCode.size() << '\n';
    std::cout << "Fragment shader code size: " << fragCode.size() << '\n';
}

void Pipeline::createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule)
{
    VkShaderModuleCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = code.size();
    createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

    if (vkCreateShaderModule(device.device(), &createInfo, nullptr, shaderModule) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create shader module.");
    }
}

PipelineConfigInfo Pipeline::defaultPipelineConfigInfo(uint32_t width, uint32_t height)
{
    PipelineConfigInfo configInfo{};

    return configInfo; 
}
