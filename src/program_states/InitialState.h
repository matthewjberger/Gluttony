#include "../core/GlutProgram.h"

class InitialState : public ProgramState
{
    public:
        void Initialize(GlutProgram* program);
        void Finalize();

        void Pause();
        void Resume();

        void Reshape(int newWidth, int newHeight);
        void Render();
        void Keyboard(unsigned char key, int xPos, int yPos);
        void Update();

        static InitialState* GetInstance();

    private:
        InitialState();
        ~InitialState();

        static InitialState* instance;

        GlutProgram* mainProgram;

        /**************************/
        /* Place state items here */
        /**************************/

};
