#include "Mesh3DPrimitive.hpp"

///////...
// Programmatic Constructor (Based on supplied Shape ENUM)
///////...
Mesh3DPrimitive::Mesh3DPrimitive(Shape shapeType, bool isColored, bool isTextured) {

    mVertStrideLength = 3;
    mShape = shapeType;

    if (isColored == true) { 
            mIsColored = true;
            mColorStrideLength = 3;
        };
    if (isTextured == true) {
            mIsTextured = true;
            mTexCoordStrideLength = 2;
        };

    switch(shapeType) 
    {
        case MESH3D_TRIANGLE:
            mNumVerts = 3;
            mNumFaces = 1;
            mVertices = { 
                 0.0f,  0.5f,  0.0f,    // top
                -0.5f, -0.5f,  0.0f,    // bottom left
                 0.5f, -0.5f,  0.0f     // bottom right
            };

            if (isColored) {
                mColorCoords = {
                    1.0f, 0.0f, 0.0f,   // top
                    0.0f, 1.0f, 0.0f,   // bottom left
                    0.0f, 0.0f, 1.0f    // bottom right
                };

                mVertices = mPopulateAdditionalVertexData(mVertices, mColorCoords, mNumVerts, mFullVertStride, 3);
                mFullVertStride += 3;
            }

            if (isTextured) {
                mTexCoords = {
                    0.5f, 1.0f, // top
                    0.0f, 0.0f, // bottom left
                    1.0f, 0.0f  // bottom right
                };

                mVertices = mPopulateAdditionalVertexData(mVertices, mTexCoords, mNumVerts, mFullVertStride, 2);
                mFullVertStride += 2;
            }

            break;

        case MESH3D_QUAD:

            mNumVerts = 4;
            mNumFaces = 1;
            mVertices = { 
                -0.5f,  0.5f,  0.0f,    // top left
                 0.5f,  0.5f,  0.0f,    // top right
                -0.5f, -0.5f,  0.0f,    // bottom left
                 0.5f, -0.5f,  0.0f     // bottom right
            };

            mIndices = {
                0, 1, 3,
                3, 2, 0
            };

            if (isColored) {
                mColorCoords = {
                    1.0f, 1.0f, 0.0f,   // top left
                    1.0f, 0.0f, 0.0f,   // top right
                    0.0f, 1.0f, 0.0f,   // bottom left
                    0.0f, 0.0f, 1.0f    // bottom right
            };

                mVertices = mPopulateAdditionalVertexData(mVertices, mColorCoords, mNumVerts, mFullVertStride, 3);
                mFullVertStride += 3;
            }

            if (isTextured) {
                mTexCoords = {
                    0.0f, 1.0f, // top left
                    1.0f, 1.0f, // top right
                    0.0f, 0.0f, // bottom left
                    1.0f, 0.0f  // bottom right
                };

                mVertices = mPopulateAdditionalVertexData(mVertices, mTexCoords, mNumVerts, mFullVertStride, 2);
                mFullVertStride += 2;
            }

            break;

        case MESH3D_CUBE:
        
            mNumVerts = 24;
            mNumFaces = 6;
            mVertices = { 
                /* Bottom Face */
                -0.5f, -0.5f,  0.5f,       // top left 
                 0.5f, -0.5f,  0.5f,       // top right
                -0.5f, -0.5f, -0.5f,       // bottom left
                 0.5f, -0.5f, -0.5f,       // bottom right

                /* Back Face */
                 0.5f,  0.5f, -0.5f,       // top left 
                -0.5f,  0.5f, -0.5f,       // top right
                 0.5f, -0.5f, -0.5f,       // bottom left
                -0.5f, -0.5f, -0.5f,       // bottom right

                /* Left Face */
                -0.5f,  0.5f, -0.5f,       // top left 
                -0.5f,  0.5f,  0.5f,       // top right
                -0.5f, -0.5f, -0.5f,       // bottom left
                -0.5f, -0.5f,  0.5f,       // bottom right

                /* Right Face */
                0.5f,  0.5f,  0.5f,       // top left 
                0.5f,  0.5f, -0.5f,       // top right
                0.5f, -0.5f,  0.5f,       // bottom left
                0.5f, -0.5f, -0.5f,       // bottom right

                /* Top Face */
                -0.5f,  0.5f, -0.5f,       // top left 
                 0.5f,  0.5f, -0.5f,       // top right
                -0.5f,  0.5f,  0.5f,       // bottom left
                 0.5f,  0.5f,  0.5f,       // bottom right

                /* Front Face */
                -0.5f,  0.5f,  0.5f,       // top left 
                 0.5f,  0.5f,  0.5f,       // top right
                -0.5f, -0.5f,  0.5f,       // bottom left
                 0.5f, -0.5f,  0.5f        // bottom right
            };

            mIndices = {
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

            if (isColored) {
                mColorCoords = {
                    /* Bottom Face */
                    0.0f, 0.0f, 1.0f,   // top left
                    1.0f, 1.0f, 0.0f,   // top right
                    0.0f, 1.0f, 0.0f,   // bottom left
                    1.0f, 0.0f, 0.0f,   // bottom right

                    /* Back Face */
                    0.0f, 0.0f, 1.0f,   // top left
                    1.0f, 1.0f, 0.0f,   // top right
                    1.0f, 0.0f, 0.0f,   // bottom left
                    0.0f, 1.0f, 0.0f,   // bottom right

                    /* Left Face */
                    1.0f, 1.0f, 0.0f,   // top left
                    1.0f, 0.0f, 0.0f,   // top right
                    0.0f, 1.0f, 0.0f,   // bottom left
                    0.0f, 0.0f, 1.0f,   // bottom right
                
                    /* Right Face */
                    0.0f, 1.0f, 0.0f,   // top left
                    0.0f, 0.0f, 1.0f,   // top right
                    1.0f, 1.0f, 0.0f,   // bottom left
                    1.0f, 0.0f, 0.0f,   // bottom right
               
                    /* Top Face */
                    1.0f, 1.0f, 0.0f,   // top left
                    0.0f, 0.0f, 1.0f,   // top right
                    1.0f, 0.0f, 0.0f,   // bottom left
                    0.0f, 1.0f, 0.0f,   // bottom right
               
                    /* Front Face */
                    1.0f, 0.0f, 0.0f,   // top left
                    0.0f, 1.0f, 0.0f,   // top right
                    0.0f, 0.0f, 1.0f,   // bottom left
                    1.0f, 1.0f, 0.0f,   // bottom right
            };

                mVertices = mPopulateAdditionalVertexData(mVertices, mColorCoords, mNumVerts, mFullVertStride, 3);
                mFullVertStride += 3;
            }

            if (isTextured) {
                mTexCoords = {
                    0.0f, 1.0f, // top left
                    1.0f, 1.0f, // top right
                    0.0f, 0.0f, // bottom left
                    1.0f, 0.0f, // bottom right
                
                    0.0f, 1.0f, // top left
                    1.0f, 1.0f, // top right
                    0.0f, 0.0f, // bottom left
                    1.0f, 0.0f, // bottom right
                
                    0.0f, 1.0f, // top left
                    1.0f, 1.0f, // top right
                    0.0f, 0.0f, // bottom left
                    1.0f, 0.0f, // bottom right
                
                    0.0f, 1.0f, // top left
                    1.0f, 1.0f, // top right
                    0.0f, 0.0f, // bottom left
                    1.0f, 0.0f, // bottom right
                
                    0.0f, 1.0f, // top left
                    1.0f, 1.0f, // top right
                    0.0f, 0.0f, // bottom left
                    1.0f, 0.0f, // bottom right
                
                    0.0f, 1.0f, // top left
                    1.0f, 1.0f, // top right
                    0.0f, 0.0f, // bottom left
                    1.0f, 0.0f  // bottom right
                };

                mVertices = mPopulateAdditionalVertexData(mVertices, mTexCoords, mNumVerts, mFullVertStride, 2);
                mFullVertStride += 2;
            }
            
            break;

        case MESH3D_PYRAMID:
 
            mNumVerts = 16;
            mNumFaces = 5;
            mVertices = { 
                /* Bottom Face */
                -0.5f, -0.5f, -0.5f,       // top left 
                 0.5f, -0.5f, -0.5f,       // top right
                -0.5f, -0.5f,  0.5f,       // bottom left
                 0.5f, -0.5f,  0.5f,       // bottom right

                /* Back Triangle */
                 0.0f,  0.5f,  0.0f,        // top
                -0.5f, -0.5f, -0.5f,        // bottom left
                 0.5f, -0.5f, -0.5f,        // bottom right

                /* Left Triangle */
                 0.0f,  0.5f,  0.0f,        // top
                -0.5f, -0.5f,  0.5f,        // bottom left
                -0.5f, -0.5f, -0.5f,        // bottom right

                /* Right Triangle */
                 0.0f,  0.5f,  0.0f,        // top
                 0.5f, -0.5f, -0.5f,        // bottom left
                 0.5f, -0.5f,  0.5f,         // bottom right

                /* Front Triangle */
                 0.0f,  0.5f,  0.0f,        // top
                -0.5f, -0.5f,  0.5f,        // bottom left
                 0.5f, -0.5f,  0.5f,         // bottom right
            };

            mIndices = {
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

            if (isColored) {
                mColorCoords = {
                    1.0f, 0.0f, 1.0f,   // top left
                    1.0f, 0.0f, 0.0f,   // top right
                    0.0f, 1.0f, 0.0f,   // bottom left
                    0.0f, 0.0f, 1.0f,   // bottom right

                    1.0f, 1.0f, 0.0f,   // top
                    1.0f, 0.0f, 1.0f,   // bottom left
                    1.0f, 0.0f, 0.0f,   // bottom right

                    1.0f, 1.0f, 0.0f,   // top
                    0.0f, 1.0f, 0.0f,   // bottom left
                    1.0f, 0.0f, 1.0f,   // bottom right

                    1.0f, 1.0f, 0.0f,   // top
                    1.0f, 0.0f, 0.0f,   // bottom left
                    0.0f, 0.0f, 1.0f,   // bottom right

                    1.0f, 1.0f, 0.0f,   // top
                    0.0f, 1.0f, 0.0f,   // bottom left
                    0.0f, 0.0f, 1.0f    // bottom right
            };

                mVertices = mPopulateAdditionalVertexData(mVertices, mColorCoords, mNumVerts, mFullVertStride, 3);
                mFullVertStride += 3;
            }

            if (isTextured) {
                mTexCoords = {
                    0.0f, 1.0f, // top left
                    1.0f, 1.0f, // top right
                    0.0f, 0.0f, // bottom left
                    1.0f, 0.0f, // bottom right

                    0.5f, 1.0f, // top
                    0.0f, 0.0f, // bottom left
                    1.0f, 0.0f,  // bottom right

                    0.5f, 1.0f, // top
                    0.0f, 0.0f, // bottom left
                    1.0f, 0.0f,  // bottom right

                    0.5f, 1.0f, // top
                    0.0f, 0.0f, // bottom left
                    1.0f, 0.0f,  // bottom right

                    0.5f, 1.0f, // top
                    0.0f, 0.0f, // bottom left
                    1.0f, 0.0f  // bottom right      
                };

                mVertices = mPopulateAdditionalVertexData(mVertices, mTexCoords, mNumVerts, mFullVertStride, 2);
                mFullVertStride += 2;
            }
    }
}

std::vector<GLfloat> Mesh3DPrimitive::mPopulateAdditionalVertexData(
    std::vector<GLfloat> baseVec, 
    std::vector<GLfloat> addVec, 
    GLuint numVerts, 
    GLuint baseStride, 
    GLuint addStride) {
        for (int i = 0; i < numVerts; i++) {
            for (int j = 0; j < addStride; j++) {
                baseVec.insert(baseVec.begin() + (baseStride + j) + (i * (baseStride + addStride)),
                addVec[j + (i * addStride)]);
        }
    }

    return baseVec;
};

void Mesh3DPrimitive::mPrintVertexData() {
    std::cout << "\nFULL VERTEX DATA: " << std::endl;
    for (int i = 0; i < mVertices.size(); i++) {
        std::cout << mVertices[i] << ", ";
        if ((i + 1) % (mFullVertStride) == 0) { std::cout << "\n"; }
    }
    std::cout << std::endl;

};

void Mesh3DPrimitive::mPrintIndexData() {
    std::cout << "\nFULL INDEX DATA: " << std::endl;
    for (int i = 0; i < mIndices.size(); i++) {
        std::cout << mIndices[i] << ", ";
        if ((i + 1) % (3) == 0) { std::cout << "\n"; }
    }
    std::cout << std::endl;
}


//////////////...
///////////...
//... LOOSE SPEC & DRAW FUNCTIONS:
///////////...
//////////////...
void mVertexSpecMesh3DPrimitive(Mesh3DPrimitive* mesh) {

    std::vector<GLfloat> verts = mesh->mVertices;
    std::vector<GLuint> inds = mesh->mIndices;

    // if (inds.size() == 0) {
    //     std::cout << "Indices = No" << std::endl;
    // } else { 
    //     std::cout << "Indices = Yes" << std::endl;
    // }

    GLuint FullVSL  = mesh->mFullVertStride;
    GLuint VSL      = mesh->mVertStrideLength;
    GLuint CSL      = mesh->mColorStrideLength;
    GLuint TCSL     = mesh->mTexCoordStrideLength;

    // std::cout << "mFullVertStride: " << FullVSL << std::endl;
    // std::cout << "mVertStrideLength: " << VSL << std::endl;
    // std::cout << "mColorStrideLength: " << CSL << std::endl;
    // std::cout << "mTexCoordStrideLength: " << TCSL << std::endl;

    // Generate VAO, VBO, EBO
    glGenVertexArrays(1, &mesh->mVAO);
    glGenBuffers(1, &mesh->mVBO);
    glGenBuffers(1, &mesh->mEBO);

    // BIND OUR OBJECTS TOGETHER
    glBindVertexArray(mesh->mVAO);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->mVBO);
    glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(GLfloat), verts.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->mEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, inds.size() * sizeof(GLuint), inds.data(), GL_STATIC_DRAW);

    // Position attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, FullVSL * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color attributes
    if (mesh->mIsColored) {
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, FullVSL * sizeof(GLfloat), (void*)((VSL) * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);
    }
    // Texture coord attributes
    if (mesh->mIsTextured) {
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, mesh->mFullVertStride * sizeof(GLfloat), (void*)((VSL + CSL) * sizeof(GLfloat)));
        glEnableVertexAttribArray(2);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void mDrawMesh3DPrimitive(Mesh3DPrimitive* mesh, GLuint shader) {
    glUseProgram(shader);
    // glBindVertexArray(mesh->mVAO);

    switch(mesh->mShape) {
        case MESH3D_TRIANGLE:
            glDrawArrays(GL_TRIANGLES, 0, 6);
            break;
        case MESH3D_QUAD:
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            break;
        case MESH3D_PYRAMID:
            glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
            break;
        case MESH3D_CUBE:
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
            break;
    }
}
