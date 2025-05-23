// Include Self-Authored Libraries
#include "App.hpp"
#include "DrawLib.hpp"
#include "Shader.hpp"
#include "Texture2D.hpp"

// Include Mesh3D Primitive Library (Includes Draw Functions)
#include "Mesh3DPrimitive.hpp"

// Include C++ Std Libraries
#include <iostream>
#include <string>

// Include 3rd Party Libraries
#include "stb_image.h"

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

glm::vec3 cameraPos     = glm::vec3(0.0f, 0.0f,  3.0f);
glm::vec3 cameraFront   = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp      = glm::vec3(0.0f, 1.0f,  0.0f);


// CAMERA IMPLEMENTATION TO DO:
//  1. Implement Delta/Time.
void ProcessInput() {
    SDL_Event e;
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    const float cameraSpeed = 0.05f; // Adjust as needed
    if (state[SDL_SCANCODE_W]) {
        std::cout << "UP Pressed" << std::endl;
        cameraPos += cameraSpeed * cameraFront;
    }
    if(state[SDL_SCANCODE_S]) {
        std::cout << "DOWN Pressed" << std::endl;
        cameraPos -= cameraSpeed * cameraFront;
    }
    if(state[SDL_SCANCODE_A]) {
        std::cout << "LEFT Pressed" << std::endl;
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }    
    if(state[SDL_SCANCODE_D]) {
        std::cout << "RIGHT Pressed" << std::endl;
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
}

float deltaTime = 0.0f;
float lastFrame = 0.0f;


int main() {
    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;

    App gApp(false, false, false);
    gApp.CreateWindow(SCR_WIDTH, SCR_HEIGHT, 0, 0);

    glEnable(GL_DEPTH_TEST);

    Mesh3DPrimitive Primitive(MESH3D_PYRAMID, true, true);
    mVertexSpecMesh3DPrimitive(&Primitive);

    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f  ),
        glm::vec3( 2.0f,  5.0f, -15.0f ),
        glm::vec3(-1.5f, -2.2f, -2.5f  ),
        glm::vec3(-3.8f, -2.0f, -12.3f ),
        glm::vec3( 2.4f, -0.4f, -3.5f  ),
        glm::vec3(-1.7f,  3.0f, -7.5f  ),
        glm::vec3( 1.3f, -2.0f, -2.5f  ),
        glm::vec3( 1.5f,  2.0f, -2.5f  ),
        glm::vec3( 1.5f,  0.2f, -1.5f  ),
        glm::vec3(-1.3f,  1.0f, -1.5f  )
    };

    /* ---=======================================================--- */
    // REFACTOR :: Wrap into Mesh Objects? Maybe Wrap Conditionally? //
    /* ---=======================================================--- */
    Texture2D wallTexture("assets/textures/wall.jpg");
    Texture2D containerTexture("assets/textures/container.jpg");
    Texture2D awesomefaceTexture("assets/textures/awesomeface.png");

    /* ---============================================--- */
    // REFACTOR :: Wrap Shader logic into Texture2D? How? //
    /* ---============================================--- */
    Shader myShader("shaders/vert.glsl", "shaders/frag.glsl");

    glUseProgram(myShader.mShaderProgram);
    glUniform1i(glGetUniformLocation(myShader.mShaderProgram, "texture1"), 0);
    glUniform1i(glGetUniformLocation(myShader.mShaderProgram, "texture2"), 1);

    // Main Loop
    while(!gApp.mQuit) {

        Uint64 start = SDL_GetPerformanceCounter();

        gApp.PollQuit();
        gApp.PollToggleWireframe();

        PreDraw();
        ProcessInput();

        wallTexture.mBindTexture(GL_TEXTURE0, GL_TEXTURE_2D);
        // containerTexture.mBindTexture(GL_TEXTURE0, GL_TEXTURE_2D);
        // awesomefaceTexture.mBindTexture(GL_TEXTURE1, GL_TEXTURE_2D);

        /* ---====================================--- */
        // REFACTOR :: Wrap This into the App Object? //
        /* ---====================================--- */

        // CALCULATE TIME IN SECONDS
        float time = float(SDL_GetTicks64()) * 0.001f;

        /* ---==========================================--- */
        // REFACTOR :: Wrap This Into the General Draw Lib? //
        /* ---==========================================--- */
        // GOING 3D
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        glm::mat4 transform = glm::mat4(1.0f);

        // model = glm::rotate(model, glm::radians(-0.0f), glm::vec3(0.5f, 0.55f, 0.0f));
        model = glm::translate(model, glm::vec3(0.0, (sin(time*2)/10)-0.0f, 0.0f));  // Just play with values here!
        // view = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f));
        // view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 1.0f, 100.0f);
        // transform = glm::rotate(transform, time*8, glm::vec3(0.0f, 0.5f, 0.5f));
        // transform = glm::rotate(transform, sin(time*4)/6, glm::vec3(0.0f, 0.0f, 1.0f));     // Just play with values here!
        // transform = glm::rotate(transform, (time*4)/6, glm::vec3(0.0f, 0.0f, 1.0f));     // Just play with values here!

        // model = glm::rotate(model, time, glm::vec3(0.5f, 1.0f, 0.0f));

        GLuint modelLoc = glGetUniformLocation(myShader.mShaderProgram, "model");
        GLuint viewLoc = glGetUniformLocation(myShader.mShaderProgram, "view");
        GLuint projLoc = glGetUniformLocation(myShader.mShaderProgram, "projection");
        GLuint transformLoc = glGetUniformLocation(myShader.mShaderProgram, "transform");

        // glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, &projection[0][0]);
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

        // /* ---================--- */
        // // CAMERA 1.7. :: LOGIC 1 //
        // /* ---================--- */
        // camera/view transformation
        // glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        float radius = 10.0f;
        float camX = static_cast<float>(sin(time) * radius);
        float camZ = static_cast<float>(cos(time) * radius);
        // view = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        // ourShader.setMat4("view", view);

        GLuint cameraLoc = glGetUniformLocation(myShader.mShaderProgram, "view");
        // glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
        glUniformMatrix4fv(cameraLoc, 1, GL_FALSE, &view[0][0]);


        glUseProgram(myShader.mShaderProgram);
        glBindVertexArray(Primitive.mVAO);

        // Set Up Crate Field
        for (unsigned int i = 0; i < 10; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);

            /* ---============--- */
            // ANIMATION 1 :: BOB //
            /* ---============--- */
            model = glm::translate(model, glm::vec3(0.0, (sin(time * (i + 1))/10), 0.0f));  // Just play with values here!

            /* ---=============--- */
            // ANIMATION 2 :: SPIN //
            /* ---=============--- */
            model = glm::rotate(model, (time * (i + 1)), glm::vec3(0.0f, 1.0f, 0.0f));            
            
            /* ---===============--- */
            // ANIMATION 3 :: WOBBLE //
            /* ---===============--- */
            model = glm::rotate(model, (sin(time * (i + 5))) * 0.1f, glm::vec3(0.0f, 0.0f, 1.0f));

            // Apply transformations to current object draw
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

            mDrawMesh3DPrimitive(&Primitive, myShader.mShaderProgram);
        }

        // std::cout << "Time: " << time << std::endl;
        // std::cout << "lastFrame: " << lastFrame << std::endl;
        // std::cout << "currentFrame: " << currentFrame << std::endl;
        // std::cout << "deltaTime: " << deltaTime << std::endl;

        // std::cout << std::endl;

        // Update Window
        SDL_GL_SwapWindow(gApp.mGraphicsApplicationWindow);

        // Uint64 end = SDL_GetPerformanceCounter();
        // float elapsed = (end - start) / (float)SDL_GetPerformanceFrequency();
        // std::cout << "Current FPS: " << std::to_string(1.0f / elapsed) << std::endl;
        gApp.GetFPS(start);
    }

    return 0;
}
