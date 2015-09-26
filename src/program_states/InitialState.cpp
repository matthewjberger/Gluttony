#include "InitialState.h"

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

    model = new Model("untitled.obj");

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

}

void InitialState::Finalize()
{
    // Free Resources here
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
}

void InitialState::Render()
{
    // Clear the screen
    glClearColor(0.0, 0.0, 0.2, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shaderProgram.UseProgram();
    shaderProgram.SetUniform("mvpMatrix", &mvpMatrix);

    model->Draw(shaderProgram);
}

void InitialState::Reshape(int newWidth, int newHeight)
{
    // Prevent division by zero
    if(newHeight == 0) newHeight = 1;

    mainProgram->SetScreenWidth(newWidth);
    mainProgram->SetScreenHeight(newHeight);

    glViewport(0, 0, mainProgram->GetScreenWidth(), mainProgram->GetScreenHeight());

    // NOTE: Update the projection matrix here if present
    // Something similar to the code below
    projectionMatrix = glm::perspective(45.0f, mainProgram->GetAspectRatio(), 0.01f, 100.0f);
}
