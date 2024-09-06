#pragma once

#define GLAD_GL_IMPLEMENTATION
#define GLFW_INCLUDE_NONE

#include <glad/glad.h>
#include <GLFW/glfw3.h> 
#include <string>

class Window {
    public:
        Window(unsigned int width, unsigned int height, std::string name);
        ~Window();

        Window(const Window& window) = delete;
        Window &operator=(const Window& window) = delete;

    private:
        const unsigned int width, height;
        std::string name;
        GLFWwindow* window;
};