#include "GlutProgram.h"
using namespace std;

// GLUT Callback handlers
void RenderCallback()
{
    GlutProgram::GetInstance()->Render();
}

void ReshapeCallback(int width, int height)
{
    GlutProgram::GetInstance()->Reshape(width, height);
}

void UpdateCallback()
{
    GlutProgram::GetInstance()->Update();
}

void MouseCallback(int button, int state, int xPos, int yPos)
{
    GlutProgram::GetInstance()->Mouse(button, state, xPos, yPos);
}

void KeyboardCallback(unsigned char key, int xPos, int yPos)
{
    GlutProgram::GetInstance()->Keyboard(key, xPos, yPos);
}

GlutProgram *GlutProgram::instance = 0;

GlutProgram::GlutProgram()
{
    // These will be set by the Initialize() function
    screenWidth  = 0;
    screenHeight = 0;
}

GlutProgram::~GlutProgram()
{
    DestroyInstance();
}

bool GlutProgram::Initialize( int argc, char **argv, int width, int height, int flags, std::string windowTitle )
{
    title = windowTitle;

    screenWidth  = width;
    screenHeight = height;

    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(flags);
    glutInitWindowSize(screenWidth, screenHeight);

    // Name and create the window
    glutCreateWindow(title.c_str());

    // Now that the window is created the GL context is fully set up
    // Because of that we can now initialize GLEW to prepare work with shaders
    GLenum status = glewInit();
    if( status != GLEW_OK)
    {
        std::cerr << "[F] GLEW NOT INITIALIZED: ";
        std::cerr << glewGetErrorString(status) << std::endl;
        return false;
    }

    // Setup GLUT callbacks
    glutDisplayFunc(RenderCallback);    // Called when its time to display
    glutReshapeFunc(ReshapeCallback);   // Called if the window is resized
    glutIdleFunc(UpdateCallback);       // Called if there is nothing else to do
    glutKeyboardFunc(KeyboardCallback); // Called if there is keyboard input
    glutMouseFunc(MouseCallback);       // Called if there is mouse input

    return true;
}

bool GlutProgram::LoadContent(ProgramState* initialState)
{
    if(initialState == NULL) return false;
    ChangeState(initialState);
    return true;
}

void GlutProgram::Quit(string message)
{
    if(message != "")
        std::cerr << message << std::endl;

    // Release program resources and close libraries
    if(!ProgramStates.empty())
    {
        ProgramStates.back()->Finalize();
        ProgramStates.pop_back();
    }

    glutLeaveMainLoop();
}

GlutProgram *GlutProgram::GetInstance()
{
    if(instance == 0) instance = new GlutProgram();
    return instance;
}

int GlutProgram::GetScreenHeight()
{
    return screenHeight;
}

int GlutProgram::GetScreenWidth()
{
    return screenWidth;
}

void GlutProgram::ChangeState(ProgramState *state)
{
    // If there is a state already on the stack,
    // clean it up and pop it off the stack
    if(!ProgramStates.empty())
    {
        ProgramStates.back()->Finalize();
        ProgramStates.pop_back();
    }

    // Push the new state onto the stack
    // and initialize it
    ProgramStates.push_back(state);
    ProgramStates.back()->Initialize(this);
}

void GlutProgram::DestroyInstance()
{
    delete instance;
    instance = 0;
}

void GlutProgram::Mouse(int button, int state, int xPos, int yPos)
{
    if(!ProgramStates.empty())
        ProgramStates.back()->Mouse(button, state, xPos, yPos);
}

void GlutProgram::Keyboard(unsigned char key, int xPos, int yPos)
{
    if(!ProgramStates.empty())
        ProgramStates.back()->Keyboard(key, xPos, yPos);
}

void GlutProgram::PopState()
{
    if(!ProgramStates.empty())
    {
        // If something is on the stack,
        // finish up the state and then pop it off
        ProgramStates.back()->Finalize();
        ProgramStates.pop_back();

        // If there is another state left on the stack, it will be paused
        // so it must be resumed
        if(!ProgramStates.empty()) ProgramStates.back()->Resume();
    }
}

void GlutProgram::PushState(ProgramState *state)
{
    // Pause the current state if there is one on the stack
    if(!ProgramStates.empty())
    {
        ProgramStates.back()->Pause();
    }

    // Push state onto the stack and initialize it
    ProgramStates.push_back(state);

    ProgramStates.back()->Initialize(this);
}

void GlutProgram::SetScreenHeight(int h)
{
    screenHeight = h;
}

void GlutProgram::SetScreenWidth(int w)
{
    screenWidth = w;
}

void GlutProgram::Update()
{
    if(!ProgramStates.empty())
        ProgramStates.back()->Update();

    // Call the render callback
    glutPostRedisplay();
}

void GlutProgram::Render()
{
    if(!ProgramStates.empty())
        ProgramStates.back()->Render();

    // Swap the buffers here for convenience
    glutSwapBuffers();
}

void GlutProgram::Reshape(int newWidth, int newHeight)
{
    if(!ProgramStates.empty())
        ProgramStates.back()->Reshape(newWidth, newHeight);
}

void GlutProgram::Run()
{
    previousTime = std::chrono::high_resolution_clock::now();
    glutMainLoop();
}

float GlutProgram::GetAspectRatio()
{
    // Prevent division by 0
    float adjustedScreenHeight = screenHeight;
    if(screenHeight == 0) adjustedScreenHeight = 1;
    return (float(screenWidth)/float(adjustedScreenHeight));
}

float GlutProgram::GetTimeDelta()
{
    currentTime        = std::chrono::high_resolution_clock::now();
    float returnValue = std::chrono::duration_cast< std::chrono::duration<float> >(currentTime - previousTime).count();
    previousTime         = std::chrono::high_resolution_clock::now();

    return returnValue;
}

