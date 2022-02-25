///*
//这个学习程序目前用到的库：
//GLFW3 提供了一些渲染物体所需的最低限度的接口。它允许用户创建OpenGL上下文，定义窗口参数以及处理用户输入。
//GLAD 对底层OpenGL接口的封装
//stb_image.h 统一处理输入图像
//GLM 数学运算
//外接vscode进行shader编程
//assimp 用于导入模型
//*/
//
//
//
//#include <glad/glad.h>
//#include <GL/glfw3.h>
//#include <iostream>
//#include "Shader.h"
//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"
//#include "Camera.h"
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include <assimp/Importer.hpp>
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>
//#include "Mesh.h"
//#include "Model.h"
//#include <fstream>
//#include <string>
//#include <filesystem>
//
//
//
//using namespace std;
//
//
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void processInput(GLFWwindow* window);
//
//// settings
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
////创建摄像机
//Camera camera(glm::vec3(1.2f, 1.3f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, -30.0f);
//
////创建灯的位置
//glm::vec3 lightPos(0.8f, 1.4f, 0.0f);
////开关灯
//bool lightOn = true;
//
//
////DeltaTime
//float deltaTime = 0.0f; // 当前帧与上一帧的时间差
//float lastFrame = 0.0f; // 上一帧的时间
//
//bool firstMouse = true;
//float lastX = 400, lastY = 300;
//
//
//
////鼠标回调函数
//void mouse_callback(GLFWwindow* window, double xpos, double ypos)
//{
//    
//    if (firstMouse)
//    {
//        lastX = xpos;
//        lastY = ypos;
//        firstMouse = false;
//    }
//
//    float xoffset = xpos - lastX;
//    float yoffset = lastY - ypos;
//    lastX = xpos;
//    lastY = ypos;
//
//    camera.ProcessMouseMovement(xoffset, yoffset);
//}
//
////鼠标缩放函数
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//    camera.ProcessMouseScroll(yoffset);
//    /*if (fov >= 1.0f && fov <= 45.0f)
//        fov -= yoffset;
//    if (fov <= 1.0f)
//        fov = 1.0f;
//    if (fov >= 45.0f)
//        fov = 45.0f;*/
//}
//
////加载材质函数
//unsigned int loadTexture(char const* path)
//{
//    unsigned int textureID;
//    glGenTextures(1, &textureID);
//
//    int width, height, nrComponents;
//    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
//    if (data)
//    {
//        GLenum format;
//        if (nrComponents == 1)
//            format = GL_RED;
//        else if (nrComponents == 3)
//            format = GL_RGB;
//        else if (nrComponents == 4)
//            format = GL_RGBA;
//
//        glBindTexture(GL_TEXTURE_2D, textureID);
//        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
//        glGenerateMipmap(GL_TEXTURE_2D);
//
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//        stbi_image_free(data);
//    }
//    else
//    {
//        std::cout << "Texture failed to load at path: " << path << std::endl;
//        stbi_image_free(data);
//    }
//
//    return textureID;
//}
//
//int main()
//{
//
//    // glfw: initialize and configure
//    // ------------------------------
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//
//    // glfw window creation
//    // --------------------
//    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
//    if (window == NULL)
//    {
//        std::cout << "Failed to create GLFW window" << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//    glfwMakeContextCurrent(window);
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//
//    // glad: load all OpenGL function pointers
//    // ---------------------------------------
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//    {
//        std::cout << "Failed to initialize GLAD" << std::endl;
//        return -1;
//    }
//
//
//    // set up vertex data (and buffer(s)) and configure vertex attributes
//    // ------------------------------------------------------------------
//    //float vertices[] = {
//        // 位置              // 颜色
//    // 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
//    //-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
//    // 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
//        // first triangle
//        //-0.9f, -0.5f, 0.0f,  // left 
//        //-0.0f, -0.5f, 0.0f,  // right
//        //-0.45f, 0.5f, 0.0f,  // top 
//        // second triangle
//         //0.0f, -0.5f, 0.0f,  // left
//         //0.9f, -0.5f, 0.0f,  // right
//         //0.45f, 0.5f, 0.0f   // top 
//         //Rectangle
//         //0.5f,  0.5f, 0.0f, // right-up  
//         //0.5f, -0.5f, 0.0f, // right-down
//         //-0.5f, -0.5f, 0.0f, // left-down
//         //-0.5f, 0.5f, 0.0f //left-up
//    //};
//
//    //有纹理的矩形
//    //float vertices[] = {
//    //    //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
//    //         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
//    //         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
//    //        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
//    //        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
//    //};
//
//    //3D立方体！带颜色和纹理版
//    /*float vertices[] = {
//    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
//     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
//     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  1.0f, 0.0f, 0.0f,
//     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  1.0f, 0.0f, 0.0f,
//    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  1.0f, 0.0f, 0.0f,
//    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
//
//    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
//     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
//     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
//     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
//    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  0.0f, 1.0f, 0.0f,
//    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
//
//    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
//    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
//    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.0f, 0.0f, 1.0f,
//    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.0f, 0.0f, 1.0f,
//    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
//    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
//
//     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  1.0f, 1.0f, 0.0f,
//     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  1.0f, 1.0f, 0.0f,
//     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  1.0f, 1.0f, 0.0f,
//     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  1.0f, 1.0f, 0.0f,
//     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  1.0f, 1.0f, 0.0f,
//     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  1.0f, 1.0f, 0.0f,
//
//    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  1.0f, 0.0f, 1.0f,
//     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,  1.0f, 0.0f, 1.0f,
//     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  1.0f, 0.0f, 1.0f,
//     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  1.0f, 0.0f, 1.0f,
//    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  1.0f, 0.0f, 1.0f,
//    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  1.0f, 0.0f, 1.0f,
//
//    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f, 1.0f, 1.0f,
//     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f, 1.0f, 1.0f,
//     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f, 1.0f, 1.0f,
//     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f, 1.0f, 1.0f,
//    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  0.0f, 1.0f, 1.0f,
//    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f, 1.0f, 1.0f
//    };*/
//
//    //3D立方体纯坐标版
//    /*float vertices[] = {
//       -0.5f, -0.5f, -0.5f,
//        0.5f, -0.5f, -0.5f,
//        0.5f,  0.5f, -0.5f,
//        0.5f,  0.5f, -0.5f,
//       -0.5f,  0.5f, -0.5f,
//       -0.5f, -0.5f, -0.5f,
//
//       -0.5f, -0.5f,  0.5f,
//        0.5f, -0.5f,  0.5f,
//        0.5f,  0.5f,  0.5f,
//        0.5f,  0.5f,  0.5f,
//       -0.5f,  0.5f,  0.5f,
//       -0.5f, -0.5f,  0.5f,
//
//       -0.5f,  0.5f,  0.5f,
//       -0.5f,  0.5f, -0.5f,
//       -0.5f, -0.5f, -0.5f,
//       -0.5f, -0.5f, -0.5f,
//       -0.5f, -0.5f,  0.5f,
//       -0.5f,  0.5f,  0.5f,
//
//        0.5f,  0.5f,  0.5f,
//        0.5f,  0.5f, -0.5f,
//        0.5f, -0.5f, -0.5f,
//        0.5f, -0.5f, -0.5f,
//        0.5f, -0.5f,  0.5f,
//        0.5f,  0.5f,  0.5f,
//
//       -0.5f, -0.5f, -0.5f,
//        0.5f, -0.5f, -0.5f,
//        0.5f, -0.5f,  0.5f,
//        0.5f, -0.5f,  0.5f,
//       -0.5f, -0.5f,  0.5f,
//       -0.5f, -0.5f, -0.5f,
//
//       -0.5f,  0.5f, -0.5f,
//        0.5f,  0.5f, -0.5f,
//        0.5f,  0.5f,  0.5f,
//        0.5f,  0.5f,  0.5f,
//       -0.5f,  0.5f,  0.5f,
//       -0.5f,  0.5f, -0.5f,
//    };*/
//
//    //3D立方体带法向量
//    /*float vertices[] = {
//    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//
//    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//
//    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//
//     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//
//    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//
//    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
//     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
//     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
//    };*/
//
//    //3D立方体，法向量，纹理坐标
//    float vertices[] = {
//    // positions          // normals           // texture coords
//    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
//     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
//     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
//     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
//    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
//    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
//
//    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
//     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
//     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
//     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
//    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
//    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
//
//    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
//    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
//    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
//    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
//    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
//    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
//
//     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
//     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
//     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
//     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
//     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
//     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
//
//    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
//     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
//     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
//     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
//    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
//    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
//
//    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
//     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
//     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
//     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
//    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
//    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
//};
//
//    //10个3D立方体！
//    glm::vec3 cubePositions[] = {
//      glm::vec3(0.0f,  0.0f,  0.0f),
//      glm::vec3(2.0f,  5.0f, -15.0f),
//      glm::vec3(-1.5f, -2.2f, -2.5f),
//      glm::vec3(-3.8f, -2.0f, -12.3f),
//      glm::vec3(2.4f, -0.4f, -3.5f),
//      glm::vec3(-1.7f,  3.0f, -7.5f),
//      glm::vec3(1.3f, -2.0f, -2.5f),
//      glm::vec3(1.5f,  2.0f, -2.5f),
//      glm::vec3(1.5f,  0.2f, -1.5f),
//      glm::vec3(-1.3f,  1.0f, -1.5f)
//    };
//
//    //EBO数据
//    //unsigned int indices[] =
//    //{
//    //    //0,1,2
//    //    // for rectangle
//    //    0,1,3,
//    //    1,2,3
//    //};
//
//    //float vertices[] = {
//    //    0.5f,  0.5f, 0.0f,  // top right
//    //    0.5f, -0.5f, 0.0f,  // bottom right
//    //   -0.5f, -0.5f, 0.0f,  // bottom left
//    //   -0.5f,  0.5f, 0.0f   // top left 
//    //};
//    //unsigned int indices[] = {  // note that we start from 0!
//    //    0, 1, 3,  // first Triangle
//    //    1, 2, 3   // second Triangle
//    //};
//
//    unsigned int VBO, cubeVAO, EBO;
//
//
//    //立方体的VAO
//    //glGenVertexArrays(1, &cubeVAO);
//    glGenBuffers(1, &VBO);
//    //glGenBuffers(1, &EBO);
//    //// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
//    //glBindVertexArray(cubeVAO);
//
//    //glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//
//    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//    //顶点指针1
//    /*glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//    glEnableVertexAttribArray(2);*/
//
//    //顶点指针2
//    /*glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
//    glEnableVertexAttribArray(2);*/
//
//    //顶点指针光照版
//    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//    //glEnableVertexAttribArray(0);
//    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//    //glEnableVertexAttribArray(1);
//    //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//    //glEnableVertexAttribArray(2);
//
//
//    //灯的VAO
//    unsigned int lightVAO;
//    glGenVertexArrays(1, &lightVAO);
//    glBindVertexArray(lightVAO);
//    // 只需要绑定VBO不用再次设置VBO的数据，因为箱子的VBO数据中已经包含了正确的立方体顶点数据
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//    // 设置灯立方体的顶点属性（对我们的灯来说仅仅只有位置数据）
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//
//
//    //// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
//    //glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
//    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
//    //glBindVertexArray(0);
//
//
//    // uncomment this call to draw in wireframe polygons.
//    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//
//    //着色器类使用
//    Shader ourshader("Shaders/shader.vs", "Shaders/shader.fs");
//    Shader lightingShader("Shaders/shaderLight.vs", "Shaders/shaderLight.fs");
//    Shader lampShader("Shaders/lamp.vs", "Shaders/lamp.fs");
//    Shader modelShader("Shaders/model_loading.vs", "Shaders/model_loading.fs");
//    Shader modelShader1("Shaders/model_loading.vs", "Shaders/model_loading_notexture.fs");
//
//
//    //创建纹理
//    //unsigned int texture1, texture2, texture3;
//    //glGenTextures(1, &texture1);
//    //glGenTextures(1, &texture2);
//    //glGenTextures(1, &texture3);
//    //glActiveTexture(GL_TEXTURE0);
//    //glBindTexture(GL_TEXTURE_2D, texture1);
//    //// 为当前绑定的纹理对象设置环绕、过滤方式
//    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    //// 加载并生成纹理1
//    //int width1, height1, nrChannels1;
//    //unsigned char* data1 = stbi_load("container.jpg", &width1, &height1, &nrChannels1, 0);
//    //if (data1)
//    //{
//    //    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, data1);
//    //    glGenerateMipmap(GL_TEXTURE_2D);
//    //}
//    //else
//    //{
//    //    std::cout << "Failed to load texture" << std::endl;
//    //}
//    //stbi_image_free(data1);
//
//    ////纹理2
//    //glActiveTexture(GL_TEXTURE1);
//    //glBindTexture(GL_TEXTURE_2D, texture2);
//    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    //// 加载并生成纹理2
//    //int width2, height2, nrChannels2;
//    //stbi_set_flip_vertically_on_load(true);
//    //unsigned char* data2 = stbi_load("awesomeface.png", &width2, &height2, &nrChannels2, 0);
//    //if (data2)
//    //{
//    //    /*为什么要RGBA？？*/
//    //    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width2, height2, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
//    //    glGenerateMipmap(GL_TEXTURE_2D);
//    //}
//    //else
//    //{
//    //    std::cout << "Failed to load texture" << std::endl;
//    //}
//    //stbi_image_free(data2);
//
//    //漫反射贴图
//    //unsigned int texture3;
//    //glGenTextures(GL_TEXTURE_2D, &texture3);
//    //glActiveTexture(GL_TEXTURE2);
//    //glBindTexture(GL_TEXTURE_2D, texture3);
//    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    //int width3, height3, nrChannels3;
//    //unsigned char* data3 = stbi_load("container2.png", &width3, &height3, &nrChannels3, 0);
//    //if (data3)
//    //{
//    //    /*为什么要RGBA？？*/
//    //    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width3, height3, 0, GL_RGBA, GL_UNSIGNED_BYTE, data3);
//    //    glGenerateMipmap(GL_TEXTURE_2D);
//    //}
//    //else
//    //{
//    //    std::cout << "Failed to load texture" << std::endl;
//    //}
//    //stbi_image_free(data3);
//    
//
//    //开启深度测试
//    glEnable(GL_DEPTH_TEST);
//
//    //使用漫反射贴图
//    //unsigned int diffuseMap = loadTexture("container2.png");
//    //unsigned int specularMap = loadTexture("container2_specular.png");
//
//    //lightingShader.use();
//    //lightingShader.setInt("material.diffuse", 0);//0的意思是绑定GL_TEXTURE0
//    
//    //使用镜面光贴图
//    //lightingShader.setInt("material.specular", 1);
//
//   
//
//    // load models
//    // -----------
//    //string temp = "E:/BaiduNetdiskDownload/nanosuit/nanosuit.obj";
//    //string temp = "E:/Learning Materials/OpenGL/Models/Handgun/Handgun_obj.obj";
//    //string temp = "E:/Learning Materials/OpenGL/Models/Sting Sword/Sting-Sword-lowpoly.obj";
//    //string temp = "E:/Learning Materials/OpenGL/Models/Notebook/Lowpoly_Notebook_2.obj"; //笔记本
//    //string temp = "E:/Learning Materials/OpenGL/Models/chair/chair.obj";
//    //string temp = "E:/Learning Materials/OpenGL/Models/Folding_Chairs/13494_Folding_Chairs_v1_L3.obj"; //椅子
//    //string temp = "E:/Learning Materials/OpenGL/Models/floor/Floor.fbx";   
//    string temp = "E:/Learning Materials/OpenGL/Models/desk/StylishDesk.obj"; //书桌和地板
//
//    char* path;
//    int len = temp.length();
//    path = new char[len + 1];
//    strcpy(path, temp.c_str());
//    Model desk(path);
//
//    temp = "E:/Learning Materials/OpenGL/Models/Folding_Chairs/13494_Folding_Chairs_v1_L3.obj"; //椅子
//    len = temp.length();
//    path = new char[len + 1];
//    strcpy(path, temp.c_str());
//    Model chair(path);
//
//    temp = "E:/Learning Materials/OpenGL/Models/Notebook/Lowpoly_Notebook_2.obj"; //笔记本
//    len = temp.length();
//    path = new char[len + 1];
//    strcpy(path, temp.c_str());
//    Model laptop(path);
//
//    temp = "E:/Learning Materials/OpenGL/Models/Lamp/11832_Lamp_v1_l2.obj"; //灯具
//    len = temp.length();
//    path = new char[len + 1];
//    strcpy(path, temp.c_str());
//    Model lamp(path);
//
//
//
//
//    
//
//
//    // render loop
//    // -----------
//    while (!glfwWindowShouldClose(window))
//    {
//        //设置鼠标事件
//        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//        glfwSetCursorPosCallback(window, mouse_callback);
//        glfwSetScrollCallback(window, scroll_callback);
//        //计算新的deltatime
//        float currentFrame = glfwGetTime();
//        deltaTime = currentFrame - lastFrame;
//        lastFrame = currentFrame;
//        // input
//        // -----
//        processInput(window);
//
//        // render
//        // ------
//        //美丽的绿色
//        //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//        //无聊的黑色
//        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//        //使用shader
//        /*ourshader.use();
//        glUniform1i(glGetUniformLocation(ourshader.ID, "texture1"), 0); // 手动设置
//        ourshader.setInt("texture2", 1); // 或者使用着色器类设置*/
//        //lightingShader.use();
//        //lightingShader.setVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
//        //lightingShader.setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
//        ////lightPos.x = 1.0f + sin(glfwGetTime()) * 2.0f;
//        ////lightPos.y = sin(glfwGetTime() / 2.0f) * 1.0f;
//        ////lightingShader.setVec3("lightPos", lightPos);
//        ////lightingShader.setVec3("material.ambient", glm::vec3(1.0f, 0.5f, 0.31f));
//        ////lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, 0.5f, 0.31f));
//        ////lightingShader.setVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
//        //lightingShader.setFloat("material.shininess", 64.0f);
//        //lightingShader.setVec3("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
//        //lightingShader.setVec3("light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f)); // 将光照调暗了一些以搭配场景
//        //lightingShader.setVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
//        //lightingShader.setVec3("light.position", lightPos);
//
//        //光源自动变色
//        /*glm::vec3 lightColor;
//        lightColor.x = sin(glfwGetTime() * 2.0f);
//        lightColor.y = sin(glfwGetTime() * 0.7f);
//        lightColor.z = sin(glfwGetTime() * 1.3f);
//
//        glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f); // 降低影响
//        glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // 很低的影响
//
//        lightingShader.setVec3("light.ambient", ambientColor);
//        lightingShader.setVec3("light.diffuse", diffuseColor);*/
//
//
//        //使用纹理
//        /*glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, texture1);
//        glActiveTexture(GL_TEXTURE1);
//        glBindTexture(GL_TEXTURE_2D, texture2);*/
//        /*glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, diffuseMap);
//        glActiveTexture(GL_TEXTURE1);
//        glBindTexture(GL_TEXTURE_2D, specularMap);*/
//
//        
//
//        //定义所有矩阵
//        //摄像机类的view矩阵
//        //glm::mat4 view = glm::mat4(1.0f);
//        //view = camera.GetViewMatrix();
//        ////ourshader.setMat4("view", view);
//        //lightingShader.setMat4("view", view);
//
//        //glm::mat4 projection = glm::mat4(1.0f);
//        //projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//        ////ourshader.setMat4("projection", projection);
//        //lightingShader.setMat4("projection", projection);
//
//
//        //glm::mat4 model = glm::mat4(1.0f);
//        //lightingShader.setMat4("model", model);
//
//
//
//        //lightingShader.setVec3("viewPos", camera.Position);
//
//       /* glBindVertexArray(cubeVAO);
//        glDrawArrays(GL_TRIANGLES, 0, 36);*/
//
//
//        /*lBindVertexArray(lightVAO);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//
//        model = glm::translate(model, lightPos);
//        model = glm::scale(model, glm::vec3(0.2f));
//
//        lampShader.use();
//        lampShader.setMat4("model", model);
//        lampShader.setMat4("view", view);
//        lampShader.setMat4("projection", projection);*/
//
//        //画十个箱子
//        /*lightingShader.use();
//        glBindVertexArray(cubeVAO);
//        for (unsigned int i = 0; i < 10; i++)
//        {
//            glm::mat4 model1 = glm::mat4(1.0f);
//            model1 = glm::translate(model1, cubePositions[i]);
//            float angle = 20.0f * i;
//            model1 = glm::rotate(model1, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
//            lightingShader.setMat4("model", model1);
//            glDrawArrays(GL_TRIANGLES, 0, 36);
//        }*/
//
//        //model = glm::mat4(1.0f);
//       
//        
//        
//
//        //模型加载和打光
//        modelShader1.use();
//
//        // view/projection transformations
//        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//        glm::mat4 view = camera.GetViewMatrix();
//        modelShader1.setMat4("projection", projection);
//        modelShader1.setMat4("view", view);
//
//        // render the loaded model
//        glm::mat4 model = glm::mat4(1.0f);
//        model = glm::translate(model, glm::vec3(1.7f, -0.5f, 0.0f)); // translate it down so it's at the center of the scene
//        model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));	// it's a bit too big for our scene, so scale it down
//        modelShader1.setMat4("model", model);
//        modelShader1.setVec3("light.ambient", glm::vec3(0.3f, 0.3f, 0.3f));
//        modelShader1.setVec3("light.diffuse", glm::vec3(0.8f, 0.8f, 0.8f)); // 将光照调暗了一些以搭配场景
//        modelShader1.setVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
//        modelShader1.setVec3("light.position", lightPos);
//        modelShader1.setVec3("dirLight.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
//        modelShader1.setVec3("dirLight.diffuse", glm::vec3(0.7f, 0.7f, 0.7f)); // 将光照调暗了一些以搭配场景
//        modelShader1.setVec3("dirLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
//        modelShader1.setVec3("dirLight.direction", glm::vec3(0.0f, -1.0f, -1.0f));
//        modelShader1.setBool("lightOn", lightOn);
//        modelShader1.setFloat("material.ambient", 0.2f);
//        modelShader1.setFloat("material.diffuse", 0.5f);
//        modelShader1.setFloat("material.specular", 1.0f);
//        modelShader1.setFloat("material.shininess", 16.0f);
//        modelShader1.setVec3("viewPos", camera.Position);
//        modelShader1.setVec3("objectColor", glm::vec3(1.0f, 1.0f, 1.0f));
//        desk.Draw(modelShader1);
//        //lamp.Draw(modelShader1);
//
//        modelShader.use();
//        modelShader.setMat4("projection", projection);
//        modelShader.setMat4("view", view);
//        glm::mat4 model1 = glm::mat4(1.0f);
//        model1 = glm::translate(model, glm::vec3(-2.2f, 0.0f, 0.05f));
//        model1 = glm::scale(model1, glm::vec3(0.02f, 0.02f, 0.02f));
//        model1 = glm::rotate(model1, glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0));
//        modelShader.setMat4("model", model1);
//        modelShader.setVec3("light.ambient", glm::vec3(0.3f, 0.3f, 0.3f));
//        modelShader.setVec3("light.diffuse", glm::vec3(0.8f, 0.8f, 0.8f)); // 将光照调暗了一些以搭配场景
//        modelShader.setVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
//        modelShader.setVec3("dirLight.ambient", glm::vec3(0.3f, 0.3f, 0.3f));
//        modelShader.setVec3("dirLight.diffuse", glm::vec3(0.8f, 0.8f, 0.8f)); // 将光照调暗了一些以搭配场景
//        modelShader.setVec3("dirLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
//        modelShader.setVec3("light.position", lightPos);
//        modelShader.setBool("lightOn", lightOn);
//        modelShader.setVec3("dirLight.direction", glm::vec3(0.0f, -1.0f, -1.0f));
//        modelShader.setFloat("material.ambient", 0.2f);
//        modelShader.setFloat("material.diffuse", 0.5f);
//        modelShader.setFloat("material.specular", 1.0f);
//        modelShader.setFloat("material.shininess", 16.0f);
//        modelShader.setVec3("viewPos", camera.Position);
//        lamp.Draw(modelShader);
//
//
//        glm::mat4 model2 = glm::mat4(1.0f);
//        model2 = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.05f));
//        model2 = glm::scale(model2, glm::vec3(0.09f, 0.09f, 0.09f));
//        model2 = glm::rotate(model2, glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0));
//        model2 = glm::rotate(model2, glm::radians(-90.0f), glm::vec3(0.0, 0.0, 1.0));
//        modelShader.setMat4("model", model2);
//        chair.Draw(modelShader);
//
//        glm::mat4 model3 = glm::mat4(1.0f);
//        model3 = glm::translate(model, glm::vec3(-0.2f, 1.6f, 0.05f));
//        model3 = glm::scale(model3, glm::vec3(0.4f, 0.4f, 0.4f));
//        //model3 = glm::rotate(model2, glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0));
//        model3 = glm::rotate(model3, glm::radians(180.0f), glm::vec3(0.0, 1.0, 0.0));
//        modelShader.setMat4("model", model3);
//        laptop.Draw(modelShader);
//
//
//
//
//
//
//        //lightPos.x = sin(glfwGetTime()) * 2.0f + 1.0f;
//        //lightPos.y = sin(glfwGetTime() / 2.0f) * 1.0f;
//        
//        //lightPos.y = sin(glfwGetTime());
//        lampShader.use();
//        
//        model = glm::mat4(1.0f);
//        model = glm::translate(model, lightPos);
//        model = glm::translate(model, glm::vec3(0.0f, -0.1f, 0.0f));
//        model = glm::scale(model, glm::vec3(0.06f, 0.06f, 0.06f));
//        lampShader.setMat4("model", model);
//        lampShader.setMat4("view", view);
//        lampShader.setMat4("projection", projection);
//       
//        glBindVertexArray(lightVAO);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//
//
//
//        
//
//        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
//        // -------------------------------------------------------------------------------
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    // optional: de-allocate all resources once they've outlived their purpose:
//    // ------------------------------------------------------------------------
//   /* glDeleteVertexArrays(1, &cubeVAO);
//    glDeleteVertexArrays(1, &lightVAO);
//    glDeleteBuffers(1, &VBO);
//    glDeleteBuffers(1, &EBO);*/
//   
//
//    // glfw: terminate, clearing all previously allocated GLFW resources.
//    // ------------------------------------------------------------------
//    glfwTerminate();
//    return 0;
//}
//
//// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
//// ---------------------------------------------------------------------------------------------------------
//void processInput(GLFWwindow* window)
//{
//    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, true);
//    //camera.ProcessKeyboard();
//    //float cameraSpeed = 2.5f * deltaTime; // adjust accordingly
//    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//        camera.ProcessKeyboard(FORWARD, deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//        camera.ProcessKeyboard(BACKWARD, deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//        camera.ProcessKeyboard(LEFT, deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//        camera.ProcessKeyboard(RIGHT, deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
//    {
//        lightOn = false;
//    }
//    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
//    {
//        lightOn = true;
//    }
//
//}
//
//// glfw: whenever the window size changed (by OS or user resize) this callback function executes
//// ---------------------------------------------------------------------------------------------
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//    // make sure the viewport matches the new window dimensions; note that width and 
//    // height will be significantly larger than specified on retina displays.
//    glViewport(0, 0, width, height);
//}
//
