#include "OpenGLWindow.h"
#include <iostream>
OpenGLWindow::OpenGLWindow()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

}

GLFWwindow* OpenGLWindow::CreateWindow(unsigned int window_width, unsigned int window_height, const char* name)
{
    window = glfwCreateWindow(window_width, window_height, "name", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(-1);
    }
    return window;
}
