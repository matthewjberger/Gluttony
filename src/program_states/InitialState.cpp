#include "InitialState.h"
#include <iostream>
using namespace std;
InitialState* InitialState::instance = 0;
InitialState::InitialState(){}
InitialState::~InitialState(){}
void InitialState::Pause(){}
void InitialState::Resume(){}
InitialState* InitialState::GetInstance()
{ if(instance == 0) instance = new InitialState();
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

    prevX = program->GetScreenWidth()/2;
    prevY = program->GetScreenHeight()/2;

    glutWarpPointer(prevX, prevY);

    contextMenu = Menu::GetInstance();
    contextMenu->AddEntry("Start", MENU_START );
    contextMenu->AddEntry("Stop",  MENU_STOP  );
    contextMenu->AddEntry("Quit",  MENU_QUIT  );
    contextMenu->AddEntry("Pause", MENU_PAUSE );
    contextMenu->AddEntry("Raised View", MENU_RAISED_VIEW);
    contextMenu->AddEntry("Player View", MENU_PLAYER_VIEW);
    contextMenu->AttachToMouseRight();

    camera = new Camera();

    // Raised view
    camera->LookAt(glm::vec3(5.0f, 5.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0));

    shaderProgram.CreateProgram();
    shaderProgram.AddShaderFromFile("Shaders/modelVert.glsl", GL_VERTEX_SHADER);
    shaderProgram.AddShaderFromFile("Shaders/modelFrag.glsl", GL_FRAGMENT_SHADER);
    shaderProgram.LinkProgram();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    physicsManager = new PhysicsManager();

    // Table collision shapes
    btCollisionShape* bottom = new btStaticPlaneShape(btVector3( 0, 1,  0), 0.85);
    btCollisionShape* right  = new btStaticPlaneShape(btVector3( 0, 0,  1), -1.7);
    btCollisionShape* left   = new btStaticPlaneShape(btVector3( 0, 0, -1), -1.7);
    btCollisionShape* front  = new btStaticPlaneShape(btVector3(-1, 0,  0), -3.0);
    btCollisionShape* back   = new btStaticPlaneShape(btVector3( 1, 0,  0), -3.0);

    // Paddle and Puck collision shape
    btCollisionShape* cylinder  = new btCylinderShape(btVector3(0.2, 0.1, 0.2));

    // Add rigid bodies
    physicsManager->AddRigidBody(cylinder, btVector3(0.0, 0.0, 0.0), 2); // puck
    physicsManager->AddRigidBody(cylinder, btVector3(-2.0, 0.0, 0.0), 2); // paddle 1
    physicsManager->AddRigidBody(cylinder, btVector3(2.0, 0.0, 0.0), 2); // paddle 2
    physicsManager->AddRigidBody(bottom, btVector3(0, -1, 0));
    physicsManager->AddRigidBody(right,  btVector3(0, -1, 0));
    physicsManager->AddRigidBody(left,   btVector3(0, -1, 0));
    physicsManager->AddRigidBody(front,  btVector3(0, -1, 0));
    physicsManager->AddRigidBody(back,   btVector3(0, -1, 0));

    models[0] = new Model("Assets/hockey/table.obj",  "Assets/hockey/wood.jpg", true);
    models[1] = new Model("Assets/hockey/puck.obj",   "Assets/hockey/puck.jpg", true);
    models[2] = new Model("Assets/hockey/paddle.obj", "Assets/hockey/whiteplastic.jpg", true);

    models[1]->Rotate(M_PI, glm::vec3(1,0,0));

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

    models[0]->Free();
    models[1]->Free();
    models[2]->Free();

    delete camera;
    delete skybox;
    delete physicsManager;

    camera = NULL;
    skybox = NULL;
    physicsManager = NULL;
}

void InitialState::Mouse(int button, int state, int xPos, int yPos)
{
    // Handle Mouse input
}

void InitialState::MousePassive(int xPos, int yPos)
{
    GlutProgram* program = GlutProgram::GetInstance();
    float x = float(xPos) / float(program->GetScreenWidth()  - 0.5) * 2;
    float y = float(yPos) / float(program->GetScreenHeight() - 0.5) * 2;
    float xOffset = x - prevX;
    float yOffset = y - prevY;
    prevX = x;
    prevY = y;
    physicsManager->ApplyForceAtIndex(btVector3(xOffset * -0.01, 0.0, yOffset * -0.01), 2);
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

        case MENU_RAISED_VIEW:
            // Raised view
            camera->LookAt(glm::vec3(5.0f, 5.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0));

            break;

        case MENU_PLAYER_VIEW:
            // Player view
            camera->LookAt(glm::vec3(5.0f, 1.0f, 0.01f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0));
            break;

    }

    camera->Update();
    physicsManager->Update();
}

void InitialState::Render()
{
    GlutProgram* game = GlutProgram::GetInstance();

    // Clear the screen
    glClearColor(0.0, 0.0, 0.2, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    skybox->Draw(camera->projectionMatrix, camera->viewMatrix);

    shaderProgram.UseProgram();

    // Draw table
    shaderProgram.SetUniform("mvpMatrix", camera->GetMVP(models[0]->GetModelMatrix()));
    models[0]->Draw();

    // Draw puck
    shaderProgram.SetUniform("mvpMatrix", camera->GetMVP(physicsManager->GetModelMatrixAtIndex(0)));
    models[1]->Draw();

    // Draw paddles
    shaderProgram.SetUniform("mvpMatrix", camera->GetMVP(physicsManager->GetModelMatrixAtIndex(1)));
    models[2]->Draw();

    shaderProgram.SetUniform("mvpMatrix", camera->GetMVP(physicsManager->GetModelMatrixAtIndex(2)));
    models[2]->Draw();

    PrintText(0, 0,  "Player 1 Score: 0");
    PrintText(490, 0, "Player 2 Score: 0");
}

