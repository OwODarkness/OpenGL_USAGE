#include "ExampleTexture01.h"
#include <iostream>
#include "ShaderTool.h"
#include "OpenGLWindow.h"
#include "CommonUtils.h"
#include "CommonDefs.h"
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

    //载入Shader程序
    ShaderTool* shaderTool = new ShaderTool("SimpleVertexShader.vs", "SimpleFragmentShader.fs");
    unsigned int shaderProgram = shaderTool->GetProgram();

    //顶点信息
    float vertexInfo[] =
    {
        //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
             0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
             0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
    };
    //顶点Index，对应vertexInfo
    unsigned int indices[] =
    {
        0, 1, 3,//第一个三角形的顶点
        1, 2, 3//第二个三角形的顶点
    };

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    //顶点缓存, 生成并注入信息
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexInfo), vertexInfo, GL_STATIC_DRAW);

    //Element Buffer
    unsigned int EBO;
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //顶点属性格式
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    unsigned int texture1 = CommonUtils::textureLoader("D:\\Photo\\container.jpg", GL_RGB);
    unsigned int  texture2 = CommonUtils::textureLoader("D:\\Photo\\awesomeface.png", GL_RGBA);

    shaderTool->Use(); // 不要忘记在设置uniform变量之前激活着色器程序！
    shaderTool->setInt("texture1", 0);
    shaderTool->setInt("texture2", 1); // 或者使用着色器类设置
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    std::unique_ptr<GLMatrix> gl_model = std::make_unique<GLMatrix>(Eigen::Matrix4f::Identity());
    std::unique_ptr<GLMatrix> gl_view = std::make_unique<GLMatrix>(Eigen::Matrix4f::Identity());
    std::unique_ptr<GLMatrix> gl_projection = std::make_unique<GLMatrix>(Eigen::Matrix4f::Identity());
    //model transformation
    gl_model->RotationWithAxis(45, {1,0,0});
    //view transformation
    gl_view->CameraTransform({ 0, 0, -3.f }, { 0, 0, 1 }, { 1, -1, 0 });
    //perspective projection transformation
    gl_projection->PerProjection(45,(float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f,1000.0f);


    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        shaderTool->Use();

        unsigned int Loc = glGetUniformLocation(shaderProgram, "transform");

        //glUniformMatrix4fv(Loc, 1, GL_FALSE, gl_mat->GLMatFormat());
        unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
        unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
        unsigned int projLoc = glGetUniformLocation(shaderProgram, "projection");

         //pass them to the shaders (3 different ways)
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, gl_model->GLMatFormat());
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, gl_view->GLMatFormat());
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, gl_projection->GLMatFormat());

        glActiveTexture(GL_TEXTURE0); // 在绑定纹理之前先激活纹理单元
        glBindTexture(GL_TEXTURE_2D, texture1);

        glActiveTexture(GL_TEXTURE1); // 在绑定纹理之前先激活纹理单元
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
