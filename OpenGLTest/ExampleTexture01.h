#ifndef  EX_TEXTURE_01_H
#define EX_TEXTURE_01_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
/*****************************************************************//**
 * \file   ExampleTexture01.h
 * \brief  ÌùÍ¼
 *
 * \author Lenovo
 * \date   January 2024
 *********************************************************************/


class ExampleTexture01
{
public:
	ExampleTexture01();
	void run();
private:
	void processInput(GLFWwindow* window);
	float alpha;
};

#endif // ! EX_TEXTURE_01_H


