#include "core/GlutProgram.h"
#include "program_states/InitialState.h"

int main(int argc, char **argv)
{
    // Create the program
    GlutProgram* mainProgram = GlutProgram::GetInstance();

    if(mainProgram->Initialize(argc, argv) == false)
    {
        mainProgram->Quit("ERROR: Failed to initialize program!");
    }

    if(mainProgram->LoadContent(InitialState::GetInstance()) == false)
    {
        mainProgram->Quit("ERROR: Failed to load content!");
    }

    mainProgram->Run();

    return 0;
}
