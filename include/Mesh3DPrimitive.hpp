#ifndef MESH3DPRIMITIVE_HPP
#define MESH3DPRIMITIVE_HPP

#include <glad/glad.h>

#include <iostream>
#include <vector>

enum Shape { MESH3D_TRIANGLE, MESH3D_QUAD, MESH3D_PYRAMID, MESH3D_CUBE };

struct Mesh3DPrimitive {
        Mesh3DPrimitive(Shape shapeType, bool isColored, bool isTextured);
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

        void mPrintVertexData();
        void mPrintIndexData();

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
};

void mVertexSpecMesh3DPrimitive(Mesh3DPrimitive* mesh);
void mDrawMesh3DPrimitive(Mesh3DPrimitive* mesh, GLuint shader);

#endif