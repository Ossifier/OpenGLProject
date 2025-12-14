#ifndef MESH3DTRIANGLE_HPP
#define MESH3DTRIANGLE_HPP

// 3rd Party Includes
#include <glad/glad.h>

// C++ Std Libs
#include <string>
#include <iostream>
#include <vector>

#include <sstream>
#include <fstream>

#include "Shader.hpp"
#include "Texture2D.hpp"

struct Mesh3DTriangle {

    // Constructor & Destructor -- Triangle
    Mesh3DTriangle(bool isColored, bool isTextured);
    ~Mesh3DTriangle() {};

    std::vector<GLfloat> mVertices{
         0.0f,  1.0f,  0.0f,    // top
        -1.0f, -1.0f,  0.0f,    // bottom left
         1.0f, -1.0f,  0.0f     // bottom right
    };

    std::vector<GLfloat> mColorCoords{};
    std::vector<GLfloat> mTextureCoordinates{};
    std::vector<GLuint> mIndices{};

    std::vector<GLfloat> mPopulateAdditionalVertexData(
        std::vector<GLfloat> baseVec,
        std::vector<GLfloat> addVec,
        GLuint numVerts,
        GLuint baseStride,
        GLuint addStride);

    bool mIsColored                         = false;
    bool mIsTextured                        = false;

    GLuint mNumVerts                        = 3;
    GLuint mNumFaces                        = 1;

    GLuint mVertStrideLength                = 3;
    GLuint mColorStrideLength               = 0;
    GLuint mTextureCoordinateStrideLength   = 0;

    GLuint mFullVertStride                  = 3;

    GLuint mVAO, mVBO, mEBO;

    // Shader
    GLuint mShader;

    // Debugging
    void mPrintVertexData();
    void mPrintIndexData();

    void mDrawMesh3D(GLuint shader);
};

#endif