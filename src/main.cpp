// Include Self-Authored Libraries
#include "App.hpp"
#include "Shader.hpp"
#include "Texture2D.hpp"

// Include Mesh3D Primitive Library (Includes Draw Functions)
#include "Mesh3DPrimitive.hpp"

// Include Self-Authored Libraries
#include "DrawLib.hpp"
#include "AnimateLib.hpp"

// Include C++ Std Libraries
#include <iostream>
#include <string>

// Include 3rd Party Libraries
#include "stb_image.h"

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



////////...
////...
// WINDOW & CAMERA SETUP -- Consider moving to a Settings Manager.
////...
////////...

Camera gCamera;

const GLuint SCR_WIDTH = 1600;
const GLuint SCR_HEIGHT = 1024;

GLfloat gDeltaTime = 0.0f;
GLfloat gLastFrame = 0.0f;
GLfloat gCurrentFrame = 0.0f;




int main() {
    App gApp(true, true, true);
    gApp.CreateWindow(SCR_WIDTH, SCR_HEIGHT, 0, 0);

    SDL_WarpMouseInWindow(gApp.mGraphicsApplicationWindow, SCR_WIDTH/2, SCR_HEIGHT/2);
    SDL_SetRelativeMouseMode(SDL_TRUE);

    glEnable(GL_DEPTH_TEST);

    Mesh3DPrimitive Triangle(MESH3D_TRIANGLE, true, true);
    Mesh3DPrimitive Quad(MESH3D_QUAD, true, true);
    Mesh3DPrimitive Pyramid(MESH3D_PYRAMID, true, true);
    Mesh3DPrimitive Cube(MESH3D_CUBE, true, true);

    Texture2D containerTexture("assets/textures/container.jpg");
    Texture2D wallTexture("assets/textures/wall.jpg");
    Texture2D awesomefaceTexture("assets/textures/awesomeface.png");

    Shader myShader("shaders/vert.glsl", "shaders/frag_mix.glsl");

    glUseProgram(myShader.mShaderProgram);
    glUniform1i(glGetUniformLocation(myShader.mShaderProgram, "texture1"), 0);
    glUniform1i(glGetUniformLocation(myShader.mShaderProgram, "texture2"), 1);

    mVertexSpecMesh3DPrimitive(&Triangle);
    mVertexSpecMesh3DPrimitive(&Quad);
    mVertexSpecMesh3DPrimitive(&Pyramid);
    mVertexSpecMesh3DPrimitive(&Cube);

    // Main Loop
    while(!gApp.mQuit) {

        Uint64 startTime = SDL_GetPerformanceCounter();

        gCurrentFrame = SDL_GetTicks64();
        gDeltaTime = gCurrentFrame - gLastFrame;
        gLastFrame = gCurrentFrame;

        gCamera.mPollControlInputs(SCR_WIDTH, SCR_HEIGHT, gDeltaTime);

        gApp.mPollToggleWireframe();
        gApp.mPollQuit();


        PreDraw();

        // CALCULATE TIME IN SECONDS
        float time = float(SDL_GetTicks64()) * 0.001f;

        ////////...
        ////...
        // GOING 3D
        ////...
        ////////...

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = gCamera.mGetViewMatrix();
        glm::mat4 projection = glm::mat4(1.0f);
        glm::mat4 transform = glm::mat4(1.0f);

        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 1.0f, 100.0f);

        GLuint modelLoc = glGetUniformLocation(myShader.mShaderProgram, "model");
        GLuint viewLoc = glGetUniformLocation(myShader.mShaderProgram, "view");
        GLuint projLoc = glGetUniformLocation(myShader.mShaderProgram, "projection");
        GLuint transformLoc = glGetUniformLocation(myShader.mShaderProgram, "transform");

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, &projection[0][0]);
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));


        ////////...
        ////...
        //... PREP & DRAW TRIANGLE, QUAD, PYRAMID & CUBE -- Optional For Visualizing
        //... SPEED OF ANIMATIONS -- Can be defined in the Animation 
        ////...
        ////////...

        // --- TRIANGLE

        wallTexture.mBindTexture(GL_TEXTURE0, GL_TEXTURE_2D);
        awesomefaceTexture.mBindTexture(GL_TEXTURE1, GL_TEXTURE_2D);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-3.0f, 0.0f, -3.0f)); 

        model = mSpin(model, time, 2.0f);
        model = mBob(model, time, 6.0f);
        model = mWobble(model, time, 0.1f, 5.0f);
        glBindVertexArray(Triangle.mVAO);
        
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        mDrawMesh3DPrimitive(&Triangle, myShader.mShaderProgram);

        // --- QUAD

        containerTexture.mBindTexture(GL_TEXTURE0, GL_TEXTURE_2D);
        awesomefaceTexture.mBindTexture(GL_TEXTURE1, GL_TEXTURE_2D);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -3.0f)); 

        model = mSpin(model, time, 3.0f);
        model = mBob(model, time, 7.0f);
        model = mWobble(model, time, 0.1f, 7.5f);
        glBindVertexArray(Quad.mVAO);
        
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        mDrawMesh3DPrimitive(&Quad, myShader.mShaderProgram);

        // --- PYRAMID

        wallTexture.mBindTexture(GL_TEXTURE0, GL_TEXTURE_2D);
        awesomefaceTexture.mBindTexture(GL_TEXTURE1, GL_TEXTURE_2D);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(1.0f, 0.0f, -3.0f)); 

        model = mSpin(model, time, 4.0f);
        model = mBob(model, time, 8.0f);
        model = mWobble(model, time, 0.1f, 10.0f);
        glBindVertexArray(Pyramid.mVAO);
        
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        mDrawMesh3DPrimitive(&Pyramid, myShader.mShaderProgram);

        // --- CUBE

        containerTexture.mBindTexture(GL_TEXTURE0, GL_TEXTURE_2D);
        awesomefaceTexture.mBindTexture(GL_TEXTURE1, GL_TEXTURE_2D);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(3.0f, 0.0f, -3.0f)); 

        model = mSpin(model, time, 5.0f);
        model = mBob(model, time, 9.0f);
        model = mWobble(model, time, 0.1f, 12.5f);
        glBindVertexArray(Cube.mVAO);
        
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        mDrawMesh3DPrimitive(&Cube, myShader.mShaderProgram);

        // -- TEST ANIMATION DECAY FUNCTIONS
        // // mTestDecay(1000.0f, 2.0f);
        // std::cout << "gCurrentFrame: " << gCurrentFrame << std::endl;
        // std::cout << "gDeltaTime: " << gDeltaTime << std::endl;
        // std::cout << "gLastFrame: " << gLastFrame << std::endl;
        // std::cout << "time: " << time << std::endl;

        SDL_GL_SwapWindow(gApp.mGraphicsApplicationWindow);

        gApp.mGetFPS(startTime);
    }

    return 0;
}
