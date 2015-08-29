#include "GlutProgram.h"
#include "InitialState.h"

int main(int argc, char **argv)
{
    // Create the program
    GlutProgram* mainProgram = GlutProgram::GetInstance();

    if(mainProgram->Initialize(argc, argv) == false)
    {
        printf("ERROR: Failed to initialize program!");
    }

    if(mainProgram->LoadContent(InitialState::GetInstance()) == false)
    {
        printf("ERROR: Failed to load content!");
    }

    mainProgram->Run();

    return 0;
}
