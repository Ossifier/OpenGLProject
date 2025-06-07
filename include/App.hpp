#ifndef APP_HPP
#define APP_HPP

// Include SDL For OpenGL Context
#include <SDL2/SDL.h>
// Include OpenGL Libs For Inputs
#include <glad/glad.h>

class App{
    public:
        App(bool DebugSubsystems, bool DebugWindowCreation, bool QueryGPU);
        ~App();

        void CreateWindow(int width, int height, int xPos, int yPos);

        // Member Functions -- Handling Unputs [[[REFACTOR -- Consider Enums?]]]
        void PollQuit();
        void PollToggleWireframe();
        void GetFPS(Uint64 start);

        int mScreenWidth;
        int mScreenHeight;
        SDL_Window* mGraphicsApplicationWindow  = nullptr;

        // Runtime Operation Flags
        bool mQuit                              = false; // If true, we quit the app.
        bool mWireFrameMode                     = false; // It true, we toggle wireframe rendering.

    private:
        SDL_GLContext mOpenGLContext            = nullptr;

        bool mDebugSubsystems                   = false; // If true, we return print statements for initializing SDL subsystems.
        bool mDebugWindowCreation               = false; // If true, we return print statements for launching the App.
        bool mQueryGPU                          = false; // If true, we return print statements for returning GPU vendor info.

        float mCurrentFrameTime                 = 0;
        float mLastFrameTime                    = 0;
        float mDeltaTime                        = 0;

        void QuitOnError();

        void RetrieveGPUQuery();
        void RetrieveSDLSubsystemChecks();
        void RetrieveSDLWindowCreationChecks();
};

#endif
