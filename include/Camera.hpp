#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <SDL2/SDL.h>
#include <glad/glad.h>

#include "glm/glm.hpp"


enum movState { MOV_FORWARD, MOV_BACK, MOV_LEFT, MOV_RIGHT };

class Camera {
    public:

        // Default Constructor
        Camera();

        glm::mat4 mGetViewMatrix() const;
        void mMouseLook(int mouseX, int mouseY);

        // Debugging Functions
        void mPrintDirection();
        void mPrintStrafeDirection();

        // Control Handler
        void mPollControlInputs(GLuint SCR_WIDTH, GLuint SCR_HEIGHT, GLfloat deltaTime);

        // WASD Movement (Free Camera)
        void mMoveForward(float speed);
        void mMoveBackward(float speed);
        void mMoveLeft(float speed);
        void mMoveRight(float speed);
        void mMoveUp(float speed);
        void mMoveDown(float speed);

        // Pitch Movement
        void mLookUp(float speed);
        void mLookDown(float speed);
        void mLookLeft(float speed);
        void mLookRight(float speed);

    private:
        glm::vec3 mPosition;
        glm::vec3 mViewDirection;
        glm::vec3 mUpVector;
        glm::vec3 mStrafeDirection;

        glm::vec2 mOldMousePosition;
};

#endif