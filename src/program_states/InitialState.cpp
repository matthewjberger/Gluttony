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

void InitialState::Initialize(GlutProgram* program)
{
    // Grab the main program instance for use in the program state
    mainProgram = program;

    model = new Model("Assets/house.obj");

    shaderProgram.CreateProgram();
    shaderProgram.AddShaderFromFile("Shaders/vShader.glsl", GL_VERTEX_SHADER);
    shaderProgram.AddShaderFromFile("Shaders/fShader.glsl", GL_FRAGMENT_SHADER);
    shaderProgram.LinkProgram();
    viewMatrix =  glm::lookAt( glm::vec3(0.0, 8.0, -16.0), // Eye Position
                               glm::vec3(0.0, 0.0, 0.0),         // Focus point
                               glm::vec3(0.0, 1.0, 0.0));        // Positive Y is up

    projectionMatrix = glm::perspective( 45.0f,                   // The FoV typically 90 degrees is good which is what this is set to
            mainProgram->GetAspectRatio(), // Aspect Ratio, so Circles stay Circular
            0.01f,                         // Distance to the near plane, normally a small value like this
            100.0f);                       // Distance to the far plane,

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    model->LoadTexture("Assets/houseTexture.jpg", true);

}

void InitialState::Finalize()
{
    // Free Resources here
    model->Free();
    shaderProgram.DeleteProgram();
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
    static float angle = 0.0f;

    angle += mainProgram->GetTimeDelta() * M_PI/2;

    // Update logic
    modelMatrix = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(1.0f, 1.0f, 1.0f));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f, 0.2f, 0.2f));
    mvpMatrix   =  projectionMatrix * viewMatrix * modelMatrix;
}

void InitialState::Render()
{
    // Clear the screen
    glClearColor(0.0, 0.0, 0.2, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shaderProgram.UseProgram();
    shaderProgram.SetUniform("mvpMatrix", &mvpMatrix);
    shaderProgram.SetUniform("sampler2D", 0);

    model->Draw();
}

void InitialState::Reshape(int newWidth, int newHeight)
{
    // Prevent division by zero
    if(newHeight == 0) newHeight = 1;

    mainProgram->SetScreenWidth(newWidth);
    mainProgram->SetScreenHeight(newHeight);

    glViewport(0, 0, mainProgram->GetScreenWidth(), mainProgram->GetScreenHeight());

    projectionMatrix = glm::perspective(45.0f, mainProgram->GetAspectRatio(), 0.01f, 100.0f);
}
