#ifndef TEXTURE2D_HPP
#define TEXTURE2D_HPP

// C++ Std Libs
#include <string>

// 3rd Party Includes
#include <glad/glad.h>

class Texture2D {
    public:
        // Constructor
        Texture2D(const std::string& file);

        void mBindTexture (GLenum unit, GLenum type);

        GLuint mTextureID;

    private:
        void mGenerateTexture(std::string& filetype, int width, int height, unsigned char *data);
};

#endif