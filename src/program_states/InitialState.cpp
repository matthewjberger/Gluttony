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

void InitialState::Reshape(int newWidth, int newHeight)
{
    // Prevent division by zero
    if(newHeight == 0) newHeight = 1;

    mainProgram->SetScreenWidth(newWidth);
    mainProgram->SetScreenHeight(newHeight);

    glViewport(0, 0, mainProgram->GetScreenWidth(), mainProgram->GetScreenHeight());
}
void PrintText(float x, float y, string text, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f))
{
    GlutProgram* mainProgram = GlutProgram::GetInstance();

    // Render text with fixed-function pipeline calls
    glUseProgram(0);
    glDisable(GL_TEXTURE_2D);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, mainProgram->GetScreenWidth() - 1.0, 0.0, mainProgram->GetScreenHeight() - 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRasterPos2i(x,y);
    glColor3f(color.x, color.y, color.z);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)text.c_str());
    glEnable(GL_TEXTURE_2D);
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

    camera = new Camera();
    camera->SetPosition(glm::vec3(0.0f, 10.0f, 0.0f), 0, -1.55 );

    shaderProgram.CreateProgram();
    shaderProgram.AddShaderFromFile("Shaders/modelVert.glsl", GL_VERTEX_SHADER);
    shaderProgram.AddShaderFromFile("Shaders/modelFrag.glsl", GL_FRAGMENT_SHADER);
    shaderProgram.LinkProgram();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    //physicsManager = new PhysicsManager();

    model = new Model("Assets/hockey/Table.obj", "Assets/hockey/wood.jpg", true);

    skybox = new Skybox("Assets/skybox/right.jpg",
            "Assets/skybox/left.jpg",
            "Assets/skybox/top.jpg",
            "Assets/skybox/bottom.jpg",
            "Assets/skybox/back.jpg",
            "Assets/skybox/front.jpg");

}

void InitialState::Finalize()
{
    // Free Resources here
    shaderProgram.DeleteProgram();

    model->Free();

    delete camera;
    delete skybox;
    //delete physicsManager;

    camera = NULL;
    skybox = NULL;
    //physicsManager = NULL;
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

    camera->Update();
    //physicsManager->Update();
}

void InitialState::Render()
{
    GlutProgram* game = GlutProgram::GetInstance();

    // Clear the screen
    glClearColor(0.0, 0.0, 0.2, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    skybox->Draw(camera->projectionMatrix, camera->viewMatrix);

    shaderProgram.UseProgram();
    shaderProgram.SetUniform("mvpMatrix", camera->GetMVP(model->GetModelMatrix()));
    model->Draw();

    PrintText(0, 0,  "Player 1 Score: 0");
    PrintText(490, 0, "Player 2 Score: 0");
}

