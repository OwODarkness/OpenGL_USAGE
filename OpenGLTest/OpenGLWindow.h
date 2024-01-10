#pragma once
#include <GLFW/glfw3.h>

class OpenGLWindow
{
public:
	OpenGLWindow();
	~OpenGLWindow()
	{
		glfwTerminate();
	}
	GLFWwindow* CreateWindow(unsigned int window_width = 1600, unsigned int window_height = 1200, const char* name = "OpenGL tutorial");
private:
	GLFWwindow* window;
};

