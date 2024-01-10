#include "ExampleTriangle01.h"
#include "OpenGLWindow.h"
#include "CommonUtils.h"
#include <iostream>
#include "ShaderTool.h"
void ExampleTriangle01::run()
{
	OpenGLWindow* windowObject = new OpenGLWindow;
	GLFWwindow* window = windowObject->CreateWindow();

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, CommonUtils::framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		exit(-1);
	}

	ShaderTool* Shader = new ShaderTool("TriangleVertexShader.vs", "TriangleFragmentShader.fs");
	unsigned int ProgramID = Shader->GetProgram();

	float vertexInfo[] = {
		0.f, 0.5f, 0.f,
		0.5f, -0.5f, 0.f,
		-0.5f, -0.5f, 0.f,
		0.f, -0.8f, 0.f,
		0.5f, 0.3f, 0.f,
		-0.5f, 0.3f, 0.f
	};

	unsigned VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned VBO;
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexInfo), vertexInfo, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//draw
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		Shader->Use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	delete Shader;
	delete windowObject;

}

void ExampleTriangle01::processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
