#include "ExampleTexture01.h"
#include <iostream>
#include "ShaderTool.h"
#include "OpenGLWindow.h"
#include "CommonUtils.h"
#include "CommonDefs.h"
#include "Eigen/Core"
#include "TransTool.h"

// settings
using namespace gldef;
ExampleTexture01::ExampleTexture01()
{
    this->alpha = 0.2;
}
void ExampleTexture01::run()
{
    // glfw: initialize and configure

    // glfw window creation
    // --------------------
    OpenGLWindow* windowObject = new OpenGLWindow;
    GLFWwindow* window = windowObject->CreateWindow(SCR_WIDTH, SCR_HEIGHT);

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, CommonUtils::framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(-1);
    }

    //����Shader����
    ShaderTool* shaderTool = new ShaderTool("SimpleVertexShader.vs", "SimpleFragmentShader.fs");
    unsigned int shaderProgram = shaderTool->GetProgram();

    //������Ϣ
    float vertexInfo[] =
    {
        //     ---- λ�� ----       ---- ��ɫ ----     - �������� -
             0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // ����
             0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // ����
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // ����
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // ����
    };
    //����Index����ӦvertexInfo
    unsigned int indices[] =
    {
        0, 1, 3,//��һ�������εĶ���
        1, 2, 3//�ڶ��������εĶ���
    };

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    //���㻺��, ���ɲ�ע����Ϣ
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexInfo), vertexInfo, GL_STATIC_DRAW);

    //Element Buffer
    unsigned int EBO;
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //�������Ը�ʽ
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    unsigned int texture1 = CommonUtils::textureLoader("D:\\Photo\\container.jpg", GL_RGB);
    unsigned int  texture2 = CommonUtils::textureLoader("D:\\Photo\\awesomeface.png", GL_RGBA);

    shaderTool->Use(); // ��Ҫ����������uniform����֮ǰ������ɫ������
    shaderTool->setInt("texture1", 0);
    shaderTool->setInt("texture2", 1); // ����ʹ����ɫ��������
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    GLMatrix* gl_mat = new GLMatrix(Eigen::Matrix4f::Identity());
    Eigen::Vector3f v1;
    v1 << -0.1, -0.25, 0;
    Eigen::Vector3f v2;
    v2 << 0.1, 0.25, 0;
    gl_mat->Translation(v1);
    gl_mat->RotationWithAxis(30, {0,0,1});
    gl_mat->Translation(v2);


    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        unsigned int Loc = glGetUniformLocation(shaderProgram, "transform");

        glUniformMatrix4fv(Loc, 1, GL_FALSE, gl_mat->GLMatFormat());
        glActiveTexture(GL_TEXTURE0); // �ڰ�����֮ǰ�ȼ�������Ԫ
        glBindTexture(GL_TEXTURE_2D, texture1);

        glActiveTexture(GL_TEXTURE1); // �ڰ�����֮ǰ�ȼ�������Ԫ
        glBindTexture(GL_TEXTURE_2D, texture2);

        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        {
            alpha = CommonUtils::Clamp(alpha+0.001f, 0.f, 1.f);
        }

        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            alpha = CommonUtils::Clamp(alpha - 0.001f, 0.f, 1.f);
        }
        shaderTool->setFloat("alpha", alpha);

        shaderTool->Use();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    // glfw: terminate, clearing all previously allocated GLFW resources
    delete shaderTool;
    delete windowObject;
}
void ExampleTexture01::processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
