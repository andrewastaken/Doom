#include "Window.h"
#include <glfw/glfw3.h>
#include <string>

Window::Window(unsigned int windowWidth, unsigned int windowHeight, std::string windowName) : 
    width(windowWidth), height(windowHeight), name(windowName) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
}

Window::~Window() {
    glfwDestroyWindow(window);
}