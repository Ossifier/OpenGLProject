#ifndef MESH3DPYRAMID_HPP
#define MESH3DPYRAMID_HPP

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

struct Mesh3DPyramid {

    // Constructor & Destructor -- Triangle
    Mesh3DPyramid(bool isColored, bool isTextured);
    ~Mesh3DPyramid() {};

    std::vector<GLfloat> mVertices{
        /* Bottom Face */
        -1.0f, -1.0f, -1.0f,       // top left 
         1.0f, -1.0f, -1.0f,       // top right
        -1.0f, -1.0f,  1.0f,       // bottom left
         1.0f, -1.0f,  1.0f,       // bottom right

        /* Back Triangle */
         0.0f,  1.0f,  0.0f,        // top
        -1.0f, -1.0f, -1.0f,        // bottom left
         1.0f, -1.0f, -1.0f,        // bottom right

        /* Left Triangle */
         0.0f,  1.0f,  0.0f,        // top
        -1.0f, -1.0f,  1.0f,        // bottom left
        -1.0f, -1.0f, -1.0f,        // bottom right

        /* Right Triangle */
         0.0f,  1.0f,  0.0f,        // top
         1.0f, -1.0f, -1.0f,        // bottom left
         1.0f, -1.0f,  1.0f,         // bottom right

        /* Front Triangle */
         0.0f,  1.0f,  0.0f,        // top
        -1.0f, -1.0f,  1.0f,        // bottom left
         1.0f, -1.0f,  1.0f,         // bottom right
    };

    std::vector<GLfloat> mColorCoords{};
    std::vector<GLfloat> mTextureCoordinates{};
    std::vector<GLuint> mIndices{
        // Base Quad
        0, 1, 3,
        3, 2, 0,

        // Face 2
        4, 5, 6,

        // Face 3
        7, 8, 9,

        // Face 4
        10, 11, 12,

        // Face 5
        13, 14, 15
    };

    std::vector<GLfloat> mPopulateAdditionalVertexData(
        std::vector<GLfloat> baseVec,
        std::vector<GLfloat> addVec,
        GLuint numVerts,
        GLuint baseStride,
        GLuint addStride);

    bool mIsColored                         = false;
    bool mIsTextured                        = false;

    GLuint mNumVerts                        = 16;
    GLuint mNumFaces                        = 5;

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