#include "DrawLib.hpp"
#include "Mesh3DFlex.hpp"

void PreDraw() {
    // glDisable(GL_DEPTH_TEST);
    // glDisable(GL_CULL_FACE);

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
};

//////////////...
///////////...
//... LOOSE SPEC & DRAW FUNCTIONS:
///////////...
//////////////...

void mVertexSpecMesh3D() {

    // std::vector<GLfloat> verts = mesh->mVertices;
    // std::vector<GLuint> inds = mesh->mIndices;

    // // if (inds.size() == 0) {
    // //     std::cout << "Indices = No" << std::endl;
    // // } else { 
    // //     std::cout << "Indices = Yes" << std::endl;
    // // }

    // GLuint FullVSL  = mesh->mFullVertStride;
    // GLuint VSL      = mesh->mVertStrideLength;
    // GLuint CSL      = mesh->mColorStrideLength;
    // GLuint TCSL     = mesh->mTexCoordStrideLength;

    // // std::cout << "mFullVertStride: " << FullVSL << std::endl;
    // // std::cout << "mVertStrideLength: " << VSL << std::endl;
    // // std::cout << "mColorStrideLength: " << CSL << std::endl;
    // // std::cout << "mTexCoordStrideLength: " << TCSL << std::endl;

    // // Generate VAO, VBO, EBO
    // glGenVertexArrays(1, &mesh->mVAO);
    // glGenBuffers(1, &mesh->mVBO);
    // glGenBuffers(1, &mesh->mEBO);

    // // BIND OUR OBJECTS TOGETHER
    // glBindVertexArray(mesh->mVAO);

    // glBindBuffer(GL_ARRAY_BUFFER, mesh->mVBO);
    // glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(GLfloat), verts.data(), GL_STATIC_DRAW);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->mEBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, inds.size() * sizeof(GLuint), inds.data(), GL_STATIC_DRAW);

    // // Position attributes
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, FullVSL * sizeof(float), (void*)0);
    // glEnableVertexAttribArray(0);

    // // Color attributes
    // if (mesh->mIsColored) {
    //     glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, FullVSL * sizeof(GLfloat), (void*)((VSL) * sizeof(GLfloat)));
    //     glEnableVertexAttribArray(1);
    // }
    // // Texture coord attributes
    // if (mesh->mIsTextured) {
    //     glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, mesh->mFullVertStride * sizeof(GLfloat), (void*)((VSL + CSL) * sizeof(GLfloat)));
    //     glEnableVertexAttribArray(2);
    // }

    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glBindVertexArray(0);
}

void mDrawMesh3D() {
    // glUseProgram(shader);

    // switch(mesh->mShape) {
    //     case MESH3D_TRIANGLE:
    //         glDrawArrays(GL_TRIANGLES, 0, 6);
    //         break;
    //     case MESH3D_QUAD:
    //         glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    //         break;
    //     case MESH3D_PYRAMID:
    //         glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
    //         break;
    //     case MESH3D_CUBE:
    //         glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //         break;
    // }
}
