#ifndef MESH3DCUBE_HPP
#define MESH3DCUBE_HPP

// 3rd Party Includes
#include <glad/glad.h>

// C++ Std Libs
#include <string>
#include <iostream>
#include <vector>

#include <sstream>
#include <fstream>

struct Mesh3DCube {

    // Constructor & Destructor -- Triangle
    Mesh3DCube(bool isColored, bool isTextured);
    ~Mesh3DCube() {};

    std::vector<GLfloat> mVertices{
        /* Bottom Face */
        -1.0f, -1.0f,  1.0f,       // top left 
         1.0f, -1.0f,  1.0f,       // top right
        -1.0f, -1.0f, -1.0f,       // bottom left
         1.0f, -1.0f, -1.0f,       // bottom right

        /* Back Face */
         1.0f,  1.0f, -1.0f,       // top left 
        -1.0f,  1.0f, -1.0f,       // top right
         1.0f, -1.0f, -1.0f,       // bottom left
        -1.0f, -1.0f, -1.0f,       // bottom right

        /* Left Face */
        -1.0f,  1.0f, -1.0f,       // top left 
        -1.0f,  1.0f,  1.0f,       // top right
        -1.0f, -1.0f, -1.0f,       // bottom left
        -1.0f, -1.0f,  1.0f,       // bottom right

        /* Right Face */
         1.0f,  1.0f,  1.0f,       // top left 
         1.0f,  1.0f, -1.0f,       // top right
         1.0f, -1.0f,  1.0f,       // bottom left
         1.0f, -1.0f, -1.0f,       // bottom right

        /* Top Face */
        -1.0f,  1.0f, -1.0f,       // top left 
         1.0f,  1.0f, -1.0f,       // top right
        -1.0f,  1.0f,  1.0f,       // bottom left
         1.0f,  1.0f,  1.0f,       // bottom right

        /* Front Face */
        -1.0f,  1.0f,  1.0f,       // top left 
         1.0f,  1.0f,  1.0f,       // top right
        -1.0f, -1.0f,  1.0f,       // bottom left
         1.0f, -1.0f,  1.0f        // bottom right
    };

    std::vector<GLfloat> mColorCoords{};
    std::vector<GLfloat> mTextureCoordinates{};
    std::vector<GLuint> mIndices{
        /* Bottom Face */
        0, 1, 3,
        3, 2, 0,

        /* Back Face */
        4, 5, 7,
        7, 6, 4,

        /* Left Face */
        8, 9, 11,
        11, 10, 8,

        /* Right Face */
        12, 13, 15,
        15, 14, 12,

        /* Top Face */
        16, 17, 19,
        19, 18, 16,

        /* Front Face */
        20, 21, 23,
        23, 22, 20
    };

    std::vector<GLfloat> mPopulateAdditionalVertexData(
        std::vector<GLfloat> baseVec,
        std::vector<GLfloat> addVec,
        GLuint numVerts,
        GLuint baseStride,
        GLuint addStride);

    bool mIsColored                         = false;
    bool mIsTextured                        = false;

    GLuint mNumVerts                        = 24;
    GLuint mNumFaces                        = 6;

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

    // Draw Functions
    void mDrawMesh3D(GLuint shader);
};

#endif