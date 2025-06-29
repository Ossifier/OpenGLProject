#ifndef APP_HPP
#define APP_HPP

// Include SDL For OpenGL Context
#include <SDL2/SDL.h>
// Include OpenGL Libs For Inputs
#include <glad/glad.h>

#include "Camera.hpp"

class App{
    public:
        App(bool DebugSubsystems, bool DebugWindowCreation, bool QueryGPU);
        ~App();

        void CreateWindow(GLint width, GLint height, GLint xPos, GLint yPos);

        // Member Functions -- Handling Unputs [[[REFACTOR -- Consider Enums?]]]
        void mPollQuit();
        void mPollToggleWireframe();

        void mGetFPS(Uint64 start);

        GLint mScreenWidth;
        GLint mScreenHeight;
        SDL_Window* mGraphicsApplicationWindow  = nullptr;

        // Runtime Operation Flags
        bool mQuit                              = false; // If true, we quit the app.
        bool mWireFrameMode                     = false; // It true, we toggle wireframe rendering.

    private:
        SDL_GLContext mOpenGLContext            = nullptr;

        bool mDebugSubsystems                   = false; // If true, we return print statements for initializing SDL subsystems.
        bool mDebugWindowCreation               = false; // If true, we return print statements for launching the App.
        bool mQueryGPU                          = false; // If true, we return print statements for returning GPU vendor info.

        GLfloat mCurrentFrameTime                 = 0;
        GLfloat mLastFrameTime                    = 0;
        GLfloat mDeltaTime                        = 0;

        void mQuitOnError();

        void mRetrieveGPUQuery();
        void mRetrieveSDLSubsystemChecks();
        void mRetrieveSDLWindowCreationChecks();
};

#endif
