#include "InitialState.h"

InitialState* InitialState::instance = 0;

InitialState::InitialState()
{
}

InitialState::~InitialState()
{
}

void InitialState::Finalize()
{
}

InitialState* InitialState::GetInstance()
{
    if(instance == 0) instance = new InitialState();
    return instance;
}

void InitialState::Initialize(GlutProgram* program)
{
    printf("InitialState Initialize\n");
    // Grab the main program instance for use in the program state
    mainProgram = program;
}

void InitialState::Keyboard(unsigned char key, int xPos, int yPos)
{
    // Handle keyboard input
    if(key == 27) // ESC
    {
        mainProgram->Quit();
    }
}

void InitialState::Pause()
{
}

void InitialState::Render()
{
    // Clear the screen
    glClearColor(0.0, 0.0, 0.2, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 }

void InitialState::Reshape(int newWidth, int newHeight)
{
    if(newHeight == 0) newHeight = 1;

    mainProgram->SetScreenWidth(newWidth);
    mainProgram->SetScreenHeight(newHeight);

    int screenWidth  = mainProgram->GetScreenWidth();
    int screenHeight = mainProgram->GetScreenHeight();

    glViewport(0, 0, screenWidth, screenHeight);

    // NOTE: Update the projection matrix here if present
    // Something similar to the code below
    // glm::perspective(45.0f, float(screenWidth), float(screenHeight), 0.01f, 100.0f);
}

void InitialState::Resume()
{
}

void InitialState::Update()
{
}


