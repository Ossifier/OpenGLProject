#include "App.hpp"

// C++ Std Lib Includes
#include <iostream>
// Include GLAD Extensions for OpenGL Functionality
#include <glad/glad.h>

// App Constructor
App::App(bool DebugSubsystems, bool DebugWindowCreation, bool QueryGPU) {
    mDebugSubsystems = DebugSubsystems;
    mDebugWindowCreation = DebugWindowCreation;
    mQueryGPU = QueryGPU;

    mRetrieveSDLSubsystemChecks();

    // Set OpenGL Context Attributes
    // -----------------------------
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
}

// App Destructor
App::~App() {
    SDL_DestroyWindow(mGraphicsApplicationWindow);
    SDL_Quit();
}

// Create Window & OpenGL Context
void App::CreateWindow(GLint width, GLint height, GLint xPos, GLint yPos) {
    // Build Window and Set OpenGL Context
    // -----------------------------------
    mGraphicsApplicationWindow  = SDL_CreateWindow(
        "OpenGL Window - SDL2",
        xPos, yPos,
        width, height,
        SDL_WINDOW_OPENGL);
    mOpenGLContext              = SDL_GL_CreateContext(mGraphicsApplicationWindow);

    mRetrieveSDLWindowCreationChecks();
    mQuitOnError();

    mRetrieveGPUQuery();
}


/* ---========--- */
// PUBLIC METHODS //
/* ---========--- */
void App::mPollQuit() {
    SDL_Event e;
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if(e.type == SDL_QUIT || state[SDL_SCANCODE_ESCAPE]) {
        std::cout << "Application Process Terminated..." << std::endl;
        mQuit = true;
    }
}

void App::mPollToggleWireframe() {
    SDL_Event e;
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (mWireFrameMode && state[SDL_SCANCODE_1]) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        mWireFrameMode = false;
    } else if (!mWireFrameMode && state[SDL_SCANCODE_2]) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        mWireFrameMode = true;
    }
}

void App::mGetFPS(Uint64 startTime) {
    Uint64 endTime = SDL_GetPerformanceCounter();
    float elapsedTime = (endTime - startTime) / (float)SDL_GetPerformanceFrequency();
    std::cout << "Current FPS: " << std::to_string(1.0f / elapsedTime) << std::endl;
}

/* ---=========--- */
// PRIVATE METHODS //
/* ---=========--- */
void App::mQuitOnError() {
    // App Window Creating FailureVertex
    if (mGraphicsApplicationWindow == nullptr) {exit(1);}
    // OpenGL Context Failure
    if (mOpenGLContext == nullptr) {exit(1);}
    // GLAD Initialization Failure
    if(!gladLoadGLLoader(SDL_GL_GetProcAddress)) {exit(1);}
}

void App::mRetrieveGPUQuery() {
    if (mQueryGPU) {
        std::cout << "\nVendor: " << glGetString(GL_VENDOR) << "\n";
        std::cout << "Renderer: " << glGetString(GL_RENDERER) << "\n";
        std::cout << "Version: " << glGetString(GL_VERSION) << "\n";
        std::cout << "Shading Language: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n" << std::endl;

        GLint nrVertexAttributes;
        GLint nrFragmentAttributes;
        glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrVertexAttributes);
        glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &nrFragmentAttributes);

        std::cout << "Maximum # of Vertex Attributes Supported: " << nrVertexAttributes << "\n";
        std::cout << "Maximum # of Active Texture Image Units Supported: " << nrVertexAttributes << "\n" << std::endl;
    }
}

void App::mRetrieveSDLSubsystemChecks() {
    if (mDebugSubsystems) {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::cout << "SDL2 could not initialize video subsystem..." << std::endl;
        } else {std::cout << "SDL_VIDEO successfully initialized!" << std::endl;}

        if (SDL_Init(SDL_INIT_AUDIO) < 0) {
            std::cout << "SDL2 could not initialize audio subsystem..." << std::endl;
        } else {std::cout << "SDL_AUDIO successfully initialized!" << std::endl;}

        if (SDL_Init(SDL_INIT_EVENTS) < 0) {
            std::cout << "SDL2 could not initialize events subsystem..." << std::endl;
        } else {std::cout << "SDL_EVENTS successfully initialized!" << std::endl;}

        if (SDL_Init(SDL_INIT_TIMER) < 0) {
            std::cout << "SDL2 could not initialize timer subsystem..." << std::endl;
        } else {std::cout << "SDL_TIMER successfully initialized!" << std::endl;}

        if (SDL_Init(SDL_INIT_SENSOR) < 0) {
            std::cout << "SDL2 could not initialize sensor subsystem..." << std::endl;
        } else {std::cout << "SDL_SENSOR successfully initialized!" << std::endl;}

        if (SDL_Init(SDL_INIT_JOYSTICK) < 0) {
            std::cout << "SDL2 could not initialize joystick subsystem..." << std::endl;
        } else {std::cout << "SDL_JOYSTICK successfully initialized!" << std::endl;}

        if (SDL_Init(SDL_INIT_HAPTIC) < 0) {
            std::cout << "SDL2 could not initialize haptics subsystem..." << std::endl;
        } else {std::cout << "SDL_HAPTICS successfully initialized!" << std::endl;}
    }
}

void App::mRetrieveSDLWindowCreationChecks() {
    if (mDebugWindowCreation) {
        // Check for Errors
        if (mGraphicsApplicationWindow == nullptr) {
            std::cout << "\nSDL_Window was not able to be created..." << std::endl;
        } else {std::cout << "\nSDL_Window was created successfully!" << std::endl;}
        
        // Check for OpenGL Context
        if (mOpenGLContext == nullptr) {
            std::cout << "OpenGL Context not available..." << std::endl;
        } else {std::cout << "OpenGL Context successfully found!" << std::endl;}

        // Check for GLAD Library Initialization
        if(!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
            std::cout << "GLAD Library was not initialized..." << std::endl;
        } else {std::cout << "GLAD Library successfully found!" << std::endl;}
    }
}
