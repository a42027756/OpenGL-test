/*
这个学习程序目前用到的库：
GLFW3 提供了一些渲染物体所需的最低限度的接口。它允许用户创建OpenGL上下文，定义窗口参数以及处理用户输入。
GLAD 对底层OpenGL接口的封装
stb_image.h 统一处理输入图像
GLM 数学运算
外接vscode进行shader编程
*/



#include <glad/glad.h>
#include <GL/glfw3.h>
#include <iostream>
#include "Shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace std;



void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
//创建摄像机
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

//DeltaTime
float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间

bool firstMouse = true;
float lastX = 400, lastY = 300;



//鼠标回调函数
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

//鼠标缩放函数
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}


int main()
{

    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //3D立方体！带颜色和纹理版
    float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  1.0f, 0.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f, 1.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f, 0.0f, 1.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  1.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  1.0f, 1.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  1.0f, 1.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  1.0f, 1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  1.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  1.0f, 1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  1.0f, 0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,  1.0f, 0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  1.0f, 0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  1.0f, 0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f, 1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f, 1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  0.0f, 1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f, 1.0f, 1.0f
    };

    //10个3D立方体！
    glm::vec3 cubePositions[] = {
      glm::vec3(0.0f,  0.0f,  0.0f),
      glm::vec3(2.0f,  5.0f, -15.0f),
      glm::vec3(-1.5f, -2.2f, -2.5f),
      glm::vec3(-3.8f, -2.0f, -12.3f),
      glm::vec3(2.4f, -0.4f, -3.5f),
      glm::vec3(-1.7f,  3.0f, -7.5f),
      glm::vec3(1.3f, -2.0f, -2.5f),
      glm::vec3(1.5f,  2.0f, -2.5f),
      glm::vec3(1.5f,  0.2f, -1.5f),
      glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    //EBO数据
    //unsigned int indices[] =
    //{
    //    //0,1,2
    //    // for rectangle
    //    0,1,3,
    //    1,2,3
    //};

    //float vertices[] = {
    //    0.5f,  0.5f, 0.0f,  // top right
    //    0.5f, -0.5f, 0.0f,  // bottom right
    //   -0.5f, -0.5f, 0.0f,  // bottom left
    //   -0.5f,  0.5f, 0.0f   // top left 
    //};
    //unsigned int indices[] = {  // note that we start from 0!
    //    0, 1, 3,  // first Triangle
    //    1, 2, 3   // second Triangle
    //};

    unsigned int VBO, cubeVAO, EBO;


    //立方体的VAO
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(cubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //顶点指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    //着色器类使用
    Shader ourshader("Shaders/shader.vs", "Shaders/shader.fs");

    //创建纹理
    unsigned int texture1, texture2;
    glGenTextures(1, &texture1);
    glGenTextures(1, &texture2);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // 为当前绑定的纹理对象设置环绕、过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // 加载并生成纹理1
    int width1, height1, nrChannels1;
    unsigned char* data1 = stbi_load("container.jpg", &width1, &height1, &nrChannels1, 0);
    if (data1)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, data1);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data1);

    //纹理2
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // 加载并生成纹理2
    int width2, height2, nrChannels2;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data2 = stbi_load("awesomeface.png", &width2, &height2, &nrChannels2, 0);
    if (data2)
    {
        /*为什么要RGBA？？*/
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width2, height2, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data2);

    

    //开启深度测试
    glEnable(GL_DEPTH_TEST);
    

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        //设置鼠标事件
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetScrollCallback(window, scroll_callback);
        //计算新的deltatime
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        // input
        // -----
        processInput(window);

        // render
        // ------
        //绿色
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //使用shader
        ourshader.use();
        glUniform1i(glGetUniformLocation(ourshader.ID, "texture1"), 0); // 手动设置
        ourshader.setInt("texture2", 1); // 或者使用着色器类设置



        //使用纹理
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
       

        

        //定义所有矩阵
        //摄像机类的view矩阵
        glm::mat4 view = glm::mat4(1.0f);
        view = camera.GetViewMatrix();
        ourshader.setMat4("view", view);


        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        ourshader.setMat4("projection", projection);

        glBindVertexArray(cubeVAO);

        for (unsigned int i = 0; i < 10; i++)
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, cubePositions[i]);
                float angle = 20.0f * i;
                model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
                ourshader.setMat4("model", model);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
    
        

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightVAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
   

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    //camera.ProcessKeyboard();
    //float cameraSpeed = 2.5f * deltaTime; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}