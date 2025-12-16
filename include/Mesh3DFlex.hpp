#ifndef MESH3DFLEX_HPP
#define MESH3DFLEX_HPP

#include <glad/glad.h>

#include <iostream>
#include <vector>

enum Shape { MESH3D_TRIANGLE, MESH3D_QUAD, MESH3D_PYRAMID, MESH3D_CUBE };

struct Mesh3DFlex {

    Mesh3DFlex(Shape shapeType, bool isColored, bool isTextured);
    
    std::vector<GLfloat> mVertices{};
    std::vector<GLfloat> mColorCoords{};
    std::vector<GLfloat> mTexCoords{};

    std::vector<GLuint> mIndices{};

    std::vector<GLfloat> mPopulateAdditionalVertexData(
        std::vector<GLfloat> baseVec, 
        std::vector<GLfloat> addVec, 
        GLuint numVerts, 
        GLuint baseStride, 
        GLuint addStride);

    Shape mShape;

    bool mIsColored                   = false;
    bool mIsTextured                  = false;

    GLuint mNumVerts                  = 0;
    GLuint mNumFaces                  = 0;

    GLuint mVertStrideLength          = 0;
    GLuint mColorStrideLength         = 0;
    GLuint mTexCoordStrideLength      = 0;

    GLuint mFullVertStride            = 3;

    GLuint mVAO, mVBO, mEBO;

    // Debugging
    void mPrintVertexData();
    void mPrintIndexData();

    // Draw Functions
    void mDrawMesh3D(GLuint shader);
};

// void mVertexSpecMesh3DFlex(Mesh3DFlex* mesh);
// void mDrawMesh3DFlex(Mesh3DFlex* mesh, GLuint shader);

#endif