#ifndef SHADER_HPP
#define SHADER_HPP

// C++ Std Libs
#include <string>

// 3rd Party Includes
#include <glad/glad.h>

class Shader{

    public:
        // Constructor
        Shader(const std::string& vertShaderPath, const std::string& fragShaderPath);

        // Member Variables
        GLuint mShaderProgram;

    private:
        // Internal Member Functions
        std::string LoadShaderFromFile(const std::string& filename);
        GLuint CompileShader(GLuint type, const std::string& source);
        GLuint LinkShaders(GLuint shader1, GLuint shader2);
};

#endif
