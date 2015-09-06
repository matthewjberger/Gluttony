#ifndef __MENU_H
#define __MENU_H

#include "GlobalIncludes.h"

class Menu
{
    public:
        static Menu* GetInstance();

        int  GetSelectedOption();
        void SetSelectedOption(int value);

        void AttachToMouseRight();
        void AttachToMouseLeft();
        void AttachToMouseMiddle();

        void AddEntry(std::string entryText, int entryValue);

    private:
        Menu();
        ~Menu();

        static Menu* instance;
        int selectedOption;
        int ID;
};

#endif
