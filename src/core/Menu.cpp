#include "Menu.h"

void CreateMenuCallback(int value){ Menu::GetInstance()->SetSelectedOption(value); }
Menu* Menu::instance = 0;
Menu::Menu()
{
    ID = glutCreateMenu(CreateMenuCallback);
}
Menu::~Menu(){}
Menu* Menu::GetInstance()
{
    if(instance == 0) instance = new Menu();
    return instance;
}


int Menu::GetSelectedOption()
{
    return selectedOption;
}

void Menu::SetSelectedOption(int value)
{
    selectedOption = value;
}

void Menu::AddEntry(std::string entryText, int entryValue)
{
    glutSetMenu(ID);
    glutAddMenuEntry(entryText.c_str(), entryValue);
}

void Menu::AttachToMouseLeft()
{
    glutAttachMenu(GLUT_LEFT_BUTTON);
}

void Menu::AttachToMouseMiddle()
{
    glutAttachMenu(GLUT_MIDDLE_BUTTON);
}

void Menu::AttachToMouseRight()
{
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}


