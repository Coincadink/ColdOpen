cmake_minimum_required(VERSION 3.11.0)
 
set(NAME ColdOpen)
project(${NAME} VERSION 0.23.0)
 
# Vulkan

find_package(Vulkan REQUIRED)
 
# GLFW

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(dependencies/glfw)

# GLM

add_subdirectory(dependencies/glm)

# General

file(GLOB_RECURSE HEADERS "src/*.hpp")
file(GLOB_RECURSE SOURCES "src/*.cpp")
 
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
 
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
 
# Building
 
message(STATUS "CREATING BUILD FOR WINDOWS")

target_include_directories(${PROJECT_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/src
    ${Vulkan_INCLUDE_DIRS}
    ${TINYOBJ_PATH}
    ${GLFW_INCLUDE_DIRS}
    ${GLM_PATH}
)

target_link_directories(${PROJECT_NAME} PUBLIC
    ${Vulkan_LIBRARIES}
    ${GLFW_LIB}
)

target_link_libraries(${PROJECT_NAME} glfw Vulkan::Vulkan glm::glm)

ADD_CUSTOM_TARGET(
    shaderComp
    COMMAND cmd /c C:/dev/ColdOpen/compile.bat
)
ADD_DEPENDENCIES(${PROJECT_NAME} shaderComp)