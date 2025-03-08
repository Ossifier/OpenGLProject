#include <iostream>
#include <sstream>
#include <fstream>

// 3rd Party Includes
#include "stb_image.h"

// Header Includes
#include "Texture2D.hpp"

// Constructor
Texture2D::Texture2D(const std::string& filepath) {

    std::string delimiter = ".";
    std::size_t found = filepath.find(delimiter);
    std::string filetype = filepath.substr(found, filepath.size());

    // Process Textures
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);

    // Generate & Bind Textures
    glGenTextures(1, &mTextureID);
    glBindTexture(GL_TEXTURE_2D, mTextureID);

    // Set Texture Wrapping Parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set Texture Filtering Parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char *data = stbi_load(filepath.c_str(), &width, &height, &nrChannels, 0);

    mGenerateTexture(filetype, width, height, data);

    stbi_image_free(data);
};

void Texture2D::mGenerateTexture(std::string& filetype, int width, int height, unsigned char *data) {
    if (filetype == ".jpg" && data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        // std::cout << ".JPG Loaded." << std::endl;
    }    
    else if (filetype == ".png" && data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        // std::cout << ".PNG Loaded." << std::endl;
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
}

void Texture2D::mBindTexture(GLenum unit, GLenum type) {
    glActiveTexture(unit);
    glBindTexture(type, mTextureID);
}