#include <iostream>
#include <sstream>
#include <fstream>

#include "Shader.hpp"

Shader::Shader(const std::string& vertShaderPath, const std::string& fragShaderPath) {

    std::string vertShaderSource = LoadShaderFromFile(vertShaderPath);
    std::string fragShaderSource = LoadShaderFromFile(fragShaderPath);

    GLuint vertShader = CompileShader(GL_VERTEX_SHADER, vertShaderSource);
    GLuint fragShader = CompileShader(GL_FRAGMENT_SHADER, fragShaderSource);

    mShaderProgram = LinkShaders(vertShader, fragShader);

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

}

std::string Shader::LoadShaderFromFile(const std::string& filename) {
    std::string result = "";
    std::string line = "";
    std::ifstream myFile(filename.c_str());

    if (myFile.is_open()) {
        while (std::getline(myFile, line)) {
            result += line + '\n';
        }
        myFile.close();
    }

    return result;
}

GLuint Shader::CompileShader(GLuint type, const std::string& source) {
    GLuint shaderObject;

    if (type == GL_VERTEX_SHADER) {
        shaderObject = glCreateShader(GL_VERTEX_SHADER);
    } else if (type == GL_FRAGMENT_SHADER) {
        shaderObject = glCreateShader(GL_FRAGMENT_SHADER);
    }

    const char* src = source.c_str();
    glShaderSource(shaderObject, 1, &src, nullptr);
    glCompileShader(shaderObject);

    /* ---======================================================--- */
    // REFACTOR :: Wrap Into a New Private Error Checking Function? //
    /* ---======================================================--- */
    // int success;
    // char infoLog[512];

    // if (!success && type == GL_VERTEX_SHADER) {
    //     glGetShaderInfoLog(shaderObject, 512, NULL, infoLog);
    //     // std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    // } else if (success && type == GL_VERTEX_SHADER){
    //     // std::cout << "Vertex Shader Compiled Successfully!" << std::endl;
    // }

    // if (!success && type == GL_FRAGMENT_SHADER) {
    //     glGetShaderInfoLog(shaderObject, 512, NULL, infoLog);
    //     // std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    // } else if (success && type == GL_FRAGMENT_SHADER) {
    //     // std::cout << "Fragment Shader Compiled Successfully!" << std::endl;
    // }

    return shaderObject;
}

GLuint Shader::LinkShaders(GLuint shader1, GLuint shader2) {
    GLuint programObject = glCreateProgram();

    glAttachShader(programObject, shader1);
    glAttachShader(programObject, shader2);
    glLinkProgram(programObject);

    /* ---======================================================--- */
    // REFACTOR :: Wrap Into a New Private Error Checking Function? //
    /* ---======================================================--- */
    // int success;
    // char infoLog[512];

    // glGetProgramiv(programObject, GL_LINK_STATUS, &success);

    // if (!success) {
    //     glGetProgramInfoLog(programObject, 512, NULL, infoLog);
    //     // std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    // } else {
    //     // std::cout << "Shaders Linked Successfully!" << std::endl;
    // }

    glValidateProgram(programObject);

    return programObject;
}
