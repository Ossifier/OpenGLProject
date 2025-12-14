#include "Mesh3DPyramid.hpp"

Mesh3DPyramid::Mesh3DPyramid(bool isColored, bool isTextured) {

    mVertStrideLength = 3;
    // mShape = shapeType;

    if (isColored == true) { 
            mIsColored = true;
            mColorStrideLength = 3;
        };
    if (isTextured == true) {
            mIsTextured = true;
            mTextureCoordinateStrideLength = 2;
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
        mTextureCoordinates = {
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
        mVertices = mPopulateAdditionalVertexData(mVertices, mTextureCoordinates, mNumVerts, mFullVertStride, 2);
        mFullVertStride += 2;
    }

    // Vertex Specification
    std::vector<GLfloat> verts = mVertices;
    std::vector<GLuint> inds = mIndices;

    GLuint FullVSL  = mFullVertStride;
    GLuint VSL      = mVertStrideLength;
    GLuint CSL      = mColorStrideLength;
    GLuint TCSL     = mTextureCoordinateStrideLength;

    // Generate VAO, VBO, EBO
    glGenVertexArrays(1, &mVAO);
    glGenBuffers(1, &mVBO);
    glGenBuffers(1, &mEBO);

    // BIND OUR OBJECTS TOGETHER
    glBindVertexArray(mVAO);

    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(GLfloat), verts.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, inds.size() * sizeof(GLuint), inds.data(), GL_STATIC_DRAW);

    // Position attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, FullVSL * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color attributes
    if (mIsColored) {
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, FullVSL * sizeof(GLfloat), (void*)((VSL) * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);
    }
    // Texture coordinate attributes
    if (mIsTextured) {
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, mFullVertStride * sizeof(GLfloat), (void*)((VSL + CSL) * sizeof(GLfloat)));
        glEnableVertexAttribArray(2);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

std::vector<GLfloat> Mesh3DPyramid::mPopulateAdditionalVertexData(
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

void Mesh3DPyramid::mPrintVertexData() {
    std::cout << "\nFULL VERTEX DATA: " << "\n";
    for (int i = 0; i < mVertices.size(); i++) {
        std::cout << mVertices[i] << ", ";
        if ((i + 1) % (mFullVertStride) == 0) { std::cout << "\n"; }
    }
    std::cout << std::endl;

};

void Mesh3DPyramid::mPrintIndexData() {
    std::cout << "\nFULL INDEX DATA: " << "\n";
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

void Mesh3DPyramid::mDrawMesh3D(GLuint shader) {
    glUseProgram(shader);
    // glBindVertexArray(mesh->mVAO);
    glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
}