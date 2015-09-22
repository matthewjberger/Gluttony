#ifndef __GLUT_PROGRAM_H
#define __GLUT_PROGRAM_H

#include "GlobalIncludes.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "VAO.h"
#include "VBO.h"
#include "Model.h"
#include "Menu.h"
#include <iostream>
#include <vector>

class ProgramState;
class GlutProgram
{
    public:

        static GlutProgram *GetInstance();
        void DestroyInstance();

        void Run();

        // Setup and Cleanup functions
        // Default flags set up a double buffered window with a depth buffer
        bool Initialize( int argc                = 0,
                         char **argv             = NULL,
                         int width               = 640,
                         int height              = 480,
                         int flags               = GLUT_DOUBLE | GLUT_DEPTH,
                         std::string windowTitle = "OpenGL Program");

        bool LoadContent(ProgramState* initialState);
        void Quit(std::string message = "");

        // GLUT callbacks
        void Mouse(int button, int state, int xPos, int yPos);
        void Keyboard(unsigned char key, int xPos, int yPos);
        void Reshape(int newWidth, int newHeight);
        void Update();
        void Render();

        // State machine functions
        void ChangeState(ProgramState *state);
        void PushState(ProgramState *state);
        void PopState();

        // Member accessors
        void  SetScreenWidth(int w);
        int   GetScreenWidth();
        void  SetScreenHeight(int h);
        int   GetScreenHeight();
        float GetAspectRatio();

        // Program States
        std::vector<ProgramState *> ProgramStates;

        // Internal Timer
        std::chrono::time_point<std::chrono::high_resolution_clock> previousTime, currentTime;
        float GetTimeDelta();

    private:
        static GlutProgram *instance;

        GlutProgram();
        ~GlutProgram();

        int screenWidth;
        int screenHeight;

        std::string title;

};

// Program state abstract class
class ProgramState
{
    public:
        virtual void Initialize(GlutProgram* program) = 0;
        virtual void Finalize() = 0;

        virtual void Pause() = 0;
        virtual void Resume()= 0;

        void ChangeState(ProgramState *state)
        {
            if(mainProgram == NULL)
            {
                printf("ERROR: No program is associated with this state!");
                return;
            }
            mainProgram->ChangeState(state);
        }

        // GLUT callbacks
        virtual void Mouse(int button, int state, int xPos, int yPos) = 0;
        virtual void Keyboard(unsigned char key, int xPos, int yPos) = 0;
        virtual void Reshape(int newWidth, int newHeight) = 0;
        virtual void Render() = 0;
        virtual void Update() = 0;

    private:
        GlutProgram* mainProgram;
};

#endif
