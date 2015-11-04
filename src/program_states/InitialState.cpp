#include "InitialState.h"
#include <iostream>
using namespace std;

InitialState* InitialState::instance = 0;
InitialState::InitialState(){}
InitialState::~InitialState(){}
void InitialState::Pause(){}
void InitialState::Resume(){}
InitialState* InitialState::GetInstance()
{
    if(instance == 0) instance = new InitialState();
    return instance;
}

void PrintText(float x, float y, string text, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f))
{
    GlutProgram* mainProgram = GlutProgram::GetInstance();

    // Render text with fixed-function pipeline calls
    glUseProgram(0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, mainProgram->GetScreenWidth() - 1.0, 0.0, mainProgram->GetScreenHeight() - 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRasterPos2i(x,y);
    glColor3f(color.x, color.y, color.z);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)text.c_str());
}

void InitialState::Initialize(GlutProgram* program)
{
    // Grab the main program instance for use in the program state
    mainProgram = program;

    contextMenu = Menu::GetInstance();
    contextMenu->AddEntry("Start", MENU_START );
    contextMenu->AddEntry("Stop",  MENU_STOP  );
    contextMenu->AddEntry("Quit",  MENU_QUIT  );
    contextMenu->AddEntry("Pause", MENU_PAUSE );
    contextMenu->AttachToMouseRight();

}

void InitialState::Finalize()
{
    // Free Resources here
}

void InitialState::Mouse(int button, int state, int xPos, int yPos)
{
    // Handle Mouse input
}

void InitialState::Keyboard(unsigned char key, int xPos, int yPos)
{
    // Handle keyboard input
    if(key == 27) // ESC
    {
        mainProgram->Quit();
    }
}

void InitialState::Update()
{
    // Update logic
    switch(contextMenu->GetSelectedOption())
    {
        case MENU_START:
            break;
        case MENU_STOP:
            break;
        case MENU_QUIT:
            mainProgram->Quit();
            break;
        case MENU_PAUSE:
            break;
    }
}

void InitialState::Render()
{
    // Clear the screen
    glClearColor(0.0, 0.0, 0.2, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void InitialState::Reshape(int newWidth, int newHeight)
{
    // Prevent division by zero
    if(newHeight == 0) newHeight = 1;

    mainProgram->SetScreenWidth(newWidth);
    mainProgram->SetScreenHeight(newHeight);

    glViewport(0, 0, mainProgram->GetScreenWidth(), mainProgram->GetScreenHeight());

    //projectionMatrix = glm::perspective(45.0f, mainProgram->GetAspectRatio(), 0.01f, 100.0f);
}
