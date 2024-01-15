#include "ExampleTexture01.h"
#include <iostream>
#include "ShaderTool.h"
#include "OpenGLWindow.h"
#include "CommonUtils.h"
#include "CommonDefs.h"
#include "TransTool.h"
#include "Camera.h"
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

    glEnable(GL_DEPTH_TEST);
    //顶点信息
    float vertexInfo[] =
    {
        //     ---- 位置 ----     - 纹理坐标 -
        //后侧面
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        //正侧面
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         //底面
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        //顶面
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    Eigen::Vector3f cubePosition[] = {
        {0.0f,  0.0f,  0.0f},
        {2.0f,  5.0f, -15.0f },
        {-1.5f, -2.2f, -2.5f},
        {-3.8f, -2.0f, -12.3f },
        {2.4f, -0.4f, -3.5f},
        {-1.7f,  3.0f, -7.5f},
        {1.3f, -2.0f, -2.5f},
        {1.5f,  2.0f, -2.5f},
        {1.5f,  0.2f, -1.5f},
        {-1.3f,  1.0f, -1.5f}
    };

    //    int triangle_num =  sizeof(indices)/sizeof(unsigned int);
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    //顶点缓存, 生成并注入信息
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexInfo), vertexInfo, GL_STATIC_DRAW);

    //顶点属性格式
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5* sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    unsigned int texture1 = CommonUtils::textureLoader("D:\\Photo\\container.jpg", GL_RGB);
    unsigned int  texture2 = CommonUtils::textureLoader("D:\\Photo\\awesomeface.png", GL_RGBA);

    shaderTool->Use(); // 不要忘记在设置uniform变量之前激活着色器程序！
    shaderTool->setInt("texture1", 0);
    shaderTool->setInt("texture2", 1); // 或者使用着色器类设置

    std::unique_ptr<Camera> camera = std::make_unique<Camera>();

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    std::unique_ptr<GLMatrix> gl_model = std::make_unique<GLMatrix>(Eigen::Matrix4f::Identity());
    std::unique_ptr<GLMatrix> gl_view = std::make_unique<GLMatrix>(Eigen::Matrix4f::Identity());
    std::unique_ptr<GLMatrix> gl_projection = std::make_unique<GLMatrix>(Eigen::Matrix4f::Identity());
    //model transformation
    gl_model->RotationWithAxis(0, {1,0,0});
    //gl_view->SetDebugflag(true);
    //view transformation
    gl_view->CameraTransform(camera->GetCameraLocation(), camera->GetLookAtDirection(), camera->GetLookUpDirection());
    //perspective projection transformation
    gl_projection->PerProjection(45,(float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f,100.0f);

    Eigen::Matrix4f transform;
    float  deltaTime = 0.f;
    float lastFrame = 0.f;
    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        float angle = 10 * 0.01 ;


        {
            if (glfwGetKey(window, GLFW_KEY_D))
            {
                //gl_model->RotationWithAxis(angle, { 0, 1, 0 });
                camera->MoveRight(deltaTime);
            }
            if (glfwGetKey(window, GLFW_KEY_A))
            {
                camera->MoveLeft(deltaTime);
            }
            if (glfwGetKey(window, GLFW_KEY_W))
            {
                camera->MoveForward(deltaTime);
            }
            if (glfwGetKey(window, GLFW_KEY_S))
            {
                camera->MoveBackward(deltaTime);
            }
            if (glfwGetKey(window, GLFW_KEY_SPACE))
            {
                camera->MoveUp(deltaTime);
            }
            if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT))
            {
                camera->MoveDown(deltaTime);
            }
        }


        float step = 0.001f;
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        {
            //alpha = CommonUtils::Clamp(alpha+0.001f, 0.f, 1.f);
            gl_model->RotationWithAxis(angle, { 1,0,0 });
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            gl_model->RotationWithAxis(-angle, { 1,0,0 });

        }
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        {
            gl_model->RotationWithAxis(angle, { 0,1,0 });
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        {
            gl_model->RotationWithAxis(-angle, { 0,1,0 });


        }

        glActiveTexture(GL_TEXTURE0); // 在绑定纹理之前先激活纹理单元
        glBindTexture(GL_TEXTURE_2D, texture1);

        glActiveTexture(GL_TEXTURE1); // 在绑定纹理之前先激活纹理单元
        glBindTexture(GL_TEXTURE_2D, texture2);

        shaderTool->setFloat("alpha", alpha);
        shaderTool->Use();
        gl_view->SetCameraTransform(camera->GetCameraLocation(), camera->GetLookAtDirection(), camera->GetLookUpDirection());

        transform = gl_projection->GetMat() * gl_view->GetMat() * gl_model->GetMat();
        shaderTool->setMat4f("transform", transform.data());

        shaderTool->Use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    //glDeleteBuffers(1, &EBO);
    // glfw: terminate, clearing all previously allocated GLFW resources
    delete shaderTool;
    delete windowObject;
}
void ExampleTexture01::processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
