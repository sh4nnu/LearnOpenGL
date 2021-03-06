//
//  main.cpp
//  LearnOpenGL
//
//  Created by Kishan on 15/12/21.
//
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include "Shader.h"
#include <iostream>
#include <filesystem>

void framebuffer_size_callback(GLFWwindow* window,  int width, int height);
void  processInput(GLFWwindow* window);

//screen size
const unsigned int SCR_HEIGHT = 600;
const unsigned int SCR_WIDTH = 800;

int main() {
    // --glfw: initialize and configure--
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    //glfw window creation
    GLFWwindow* window  =  glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Learn OpenGL", NULL, NULL);
    if(window ==  NULL)  {
        std::cout  << "Failed to create a GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    // callback function to change viewport when window size changes.
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    
    //check for glad only  after  GL context is created.
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    //--Build and compile shader program--
	Shader ourShader("/Users/kishan/Desktop/mk/online -courses/LearnOpenGL/LearnOpenGL/LearnOpenGL/shaders/shader.vs","/Users/kishan/Desktop/mk/online -courses/LearnOpenGL/LearnOpenGL/LearnOpenGL/shaders/shader.fs");
    // Drawing....
    // Setup vertex data and configure vertex attributes
    float vertices[] = {
        //positions        //colors
        0.0f,  0.5f, 0.0f, 1.0f,  0.0f, 0.0f, //top right
         0.5f, -0.5f, 0.0f, 0.0f,  1.0f, 0.0f,// bottom right
        -0.5f, -0.5f, 0.0f, 0.0f,  0.0f, 1.0f,//bottom left
        -0.5f, 0.5f, 0.0f, 0.0f,  0.0f, 0.0f,   // top left
    };
    
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    
    // Creating a vertex Buffer Object, to store vertices in GPU's mem.
    unsigned int VBO;
    unsigned int VAO;
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1,&VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //copy the previously defined vertex data into the buffer's memory.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //bind EBO and copy data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    //Linking vertex attributes
    glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    
    // Optional: we can unbind VBO, and VAO now.
//    glBindBuffer(GL_ARRAY_BUFFER,0);
//    glBindVertexArray(0);
    
  //To draw in wireframe mode
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);		

    //-- Render loop --
    while(!glfwWindowShouldClose(window))  {
        // input
        processInput(window);
        
        // rendering magic
           // color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
//        float time = glfwGetTime();
//        float greenValue = (sin(time) / 2.0f) + 0.5f;
//        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		ourShader.use();
//        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
        //glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // using EBO
        // check polls and swap buffers
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}


void framebuffer_size_callback(GLFWwindow* window,  int width, int height) {
    glViewport(0,0, width, height);
}

void  processInput(GLFWwindow* window) {
    //close on  esc key press
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
