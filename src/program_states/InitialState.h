#include "../core/GlutProgram.h"
#include "../core/Model.h"
#include "../core/Texture.h"
#include "../core/Menu.h"
#include "../core/PhysicsManager.h"
#include "../core/Camera.h"
#include "../core/Skybox.h"

enum
{
    MENU_START = 0,
    MENU_STOP  = 1,
    MENU_QUIT  = 2,
    MENU_PAUSE = 3,
    MENU_RAISED_VIEW = 4,
    MENU_PLAYER_VIEW = 5
};

class InitialState : public ProgramState
{
    public:
        void Initialize(GlutProgram* program);
        void Finalize();

        void Pause();
        void Resume();

        void Mouse(int button, int state, int xPos, int yPos);
        void MousePassive(int xPos, int yPos);
        void Keyboard(unsigned char key, int xPos, int yPos);
        void Reshape(int newWidth, int newHeight);
        void Render();
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

        Menu* contextMenu;
        PhysicsManager* physicsManager;
        Camera* camera;
        ShaderProgram shaderProgram;

        Model* models[3];
        Skybox* skybox;

        int prevX, prevY;

};
