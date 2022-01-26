//
//  Shader.h
//  LearnOpenGL
//
//  Created by Kishan on 17/01/22.
//

#ifndef Shader_H
#define Shader_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Shader
{
public:
    // Program ID
    unsigned int shaderProgramId;
    
    // constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragPath)
    {
        // 1. Retrieve the src from the file path
        std::string vertexCode;
        std::string fragmentCode;
        
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        // ensure ifstream throws exceptions.
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try {
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragPath);
            std::stringstream vShaderStream, fShaderStream;
            // read file's buffer contents to streams.
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // close file handlers
            vShaderFile.close();
            fShaderFile.close();
            // convert stream to str
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        } catch (std::ifstream::failure e) {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ"  << std::endl;
        }
        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();
        
        // 2. compile shaders
        unsigned int vertex, fragment;
        int success;
        char infoLog[512];
        
        //vertex Shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        //compile checks
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(vertex, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        
        }
        // fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        // compile checks
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(fragment, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        
        //shader program
		shaderProgramId = glCreateProgram();
        glAttachShader(shaderProgramId, vertex);
        glAttachShader(shaderProgramId, fragment);
        glLinkProgram(shaderProgramId);
        // linking check
        glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(shaderProgramId, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
        
        //delete unncecssary shaders
        glDeleteShader(vertex);
        glDeleteShader(fragment);
	};
    //use/ activate the shader
    void use()
    {
        glUseProgram(shaderProgramId);
    }
    // utility uniform functions.
    
    void setBool(const std::string &name, bool value) const
    {
        glUniform1i(glGetUniformLocation(shaderProgramId, name.c_str()), (int)value);
    }
    void setInt(const std::string &name, int value) const
    {
        glUniform1i(glGetUniformLocation(shaderProgramId, name.c_str()), value);
    }
    void setFloat(const std::string &name, float value) const
    {
        glUniform1f(glGetUniformLocation(shaderProgramId, name.c_str()), value);
    }
	
	void setMat4(const std::string &name, const glm::mat4 &mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(shaderProgramId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
};
#endif /* Shader_H */
