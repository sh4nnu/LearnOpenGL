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
#include "stb_image.h"
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
	Shader ourShader("/Users/kishan/Desktop/mk/online-courses/LearnOpenGL/LearnOpenGL/LearnOpenGL/shaders/shader.vs","/Users/kishan/Desktop/mk/online-courses/LearnOpenGL/LearnOpenGL/LearnOpenGL/shaders/shader.fs");
    // Drawing....
    // Setup vertex data and configure vertex attributes
    float vertices[] = {
		// positions          // colors           // texture coords
				 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
				 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
				-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
				-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
		
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));
	glEnableVertexAttribArray(2);
    // Optional: we can unbind VBO, and VAO now.
	    glBindBuffer(GL_ARRAY_BUFFER,0);
	    glBindVertexArray(0);
    
	// load and create a texture
	// ------------------------


	unsigned int texture1, texture2;
	glGenTextures(1, &texture1);
	//bind the texture
	glBindTexture(GL_TEXTURE_2D, texture1);
	// set texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	
	
	int width, height, nrChannels;
	unsigned char *data = stbi_load("/Users/kishan/Desktop/mk/online-courses/LearnOpenGL/LearnOpenGL/LearnOpenGL/assets/wall.jpg", &width, &height, &nrChannels, 0);
	
	// Generating a texture
	if(data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	
	
	// bind texture 2.
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	// set texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	data = stbi_load("/Users/kishan/Desktop/mk/online-courses/LearnOpenGL/LearnOpenGL/LearnOpenGL/assets/awesomeface.png", &width, &height, &nrChannels, 0);
	
	// Generating a texture
	if(data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	
	ourShader.use();
	ourShader.setInt("texture1", 0);
	ourShader.setInt("texture2", 1);
	
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
		// bind texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		ourShader.use();
//        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
        glBindVertexArray(VAO);
//        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // using EBO
        // check polls and swap buffers
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
	//delete unwanted buffers
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
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
