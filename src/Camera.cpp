#include "Camera.hpp"

// C++ Std Lib Includes
#include <iostream>

// GLM Includes
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/rotate_vector.hpp"

// Camera Constructor :: Where Camera is Initially Placed in World
Camera::Camera() {
    // Assume we are placed at the origin.
    mPosition                  = glm::vec3(0.0f, 0.0f,  3.0f);
    // Assume we are looking out into the world along the negative Z-Axis.
    mViewDirection                = glm::vec3(0.0f, 0.0f, -1.0f);
    // Assume Up/Down is always perfectly aligned along the Y-Axis.
    mUpVector                   = glm::vec3(0.0f, 1.0f,  0.0f);
    // Assume strafing occurs along the X-Axis only.
    mStrafeDirection      = glm::vec3(1.0f,  0.0f, -1.0f);
}

glm::mat4 Camera::mGetViewMatrix() const{
    return glm::lookAt(mPosition, mPosition + mViewDirection, mUpVector);
}

void Camera::MouseLook(int mouseX, int mouseY) {
    glm::vec2 currentMouse = glm::vec2(mouseX, mouseY);
    static bool firstLook = true;
    if(firstLook){
        mOldMousePosition = currentMouse;
        firstLook=false;
    }

    // 0.1f Multiplication slows down is basically analagous to "Mouse Sensitivity"
    glm::vec2 mouseDelta = -((mOldMousePosition - currentMouse)*0.1f);

    // Handle Looking along the X-Axis, with free 360-degree rotation.
    mViewDirection = glm::rotateY(mViewDirection, glm::radians(mouseDelta.x));
    // Handle Looking along the Y-Axis, limit rotation to under 180-degrees up or down.
    if ((mViewDirection.y <= 0.95f && mouseDelta.y > 0.0f) || (mViewDirection.y >= -0.95f && mouseDelta.y < 0.0f)) {
        mViewDirection.y += mouseDelta.y * 0.01f;
    } 
    
    mOldMousePosition = currentMouse;
}

// Debugging Functions
void Camera::PrintDirection() {
    std::cout << "mViewDirection: " << 
        mViewDirection.x << ", " << 
        mViewDirection.y << ", " << 
        mViewDirection.z << ", " << std::endl; 
}

void Camera::PrintStrafeDirection() {
    std::cout << "mStrafeDirection: " << 
        mStrafeDirection.x << ", " << 
        mStrafeDirection.y << ", " << 
        mStrafeDirection.z << ", " << std::endl; 
}

// WASD Functions
void Camera::mMoveForward(float speed) {
    mPosition += (mViewDirection*speed);
}

void Camera::mMoveBackward(float speed) {
    mPosition -= (mViewDirection*speed);
}

void Camera::mMoveLeft(float speed) {
    // We just need to move along z as if we have turned 90 degrees...
    mStrafeDirection = glm::rotateY(mViewDirection, glm::radians(90.0f));
    mStrafeDirection.y = 0.0f;
    mPosition += (mStrafeDirection*speed);
}

void Camera::mMoveRight(float speed) {
    // We just need to move along z as if we have turned 90 degrees...
    mStrafeDirection = glm::rotateY(mViewDirection, glm::radians(90.0f));
    mStrafeDirection.y = 0.0f;
    mPosition -= (mStrafeDirection*speed);
}

void Camera::mMoveUp(float speed) {
    mPosition.y += speed;
}

void Camera::mMoveDown(float speed) {
    mPosition.y -= speed;
}

// Manual Look Functions
void Camera::mLookUp(float speed) {
    if (mViewDirection.y <= 0.95f) {
        mViewDirection.y += 0.01f;
    }
}
void Camera::mLookDown(float speed) {
    if (mViewDirection.y >= -0.95f) {
        mViewDirection.y -= 0.01f;
    }
}
void Camera::mLookLeft(float speed) {
    mViewDirection = glm::rotateY(mViewDirection, glm::radians(0.5f));
}
void Camera::mLookRight(float speed) {
    mViewDirection = glm::rotateY(mViewDirection, glm::radians(-0.5f));
}


    //////////...
    /////...
    //... DEPRICATED LOOK FUNCTION APPROACH -- PERHAPS APPROPRIATE FOR FLY-BY CAMERA?
    /////...
    //////////...


// // Manual Look Functions
// void Camera::mLookUp(float speed) {
//     mViewDirection = glm::rotateX(mViewDirection, glm::radians(0.5f));
// }
// void Camera::mLookDown(float speed) {
//     mViewDirection = glm::rotateX(mViewDirection, glm::radians(-0.5f));
// }
// void Camera::mLookLeft(float speed) {
//     mViewDirection = glm::rotateY(mViewDirection, glm::radians(0.5f));
// }
// void Camera::mLookRight(float speed) {
//     mViewDirection = glm::rotateY(mViewDirection, glm::radians(-0.5f));
// }
