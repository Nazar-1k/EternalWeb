#include "Game.h"

#define _WIN32_WINNT 0x0500
#include <windows.h>

int main()
{
    //close console
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);
    srand(time(NULL));
    //Inite Game Engine
    Game game;
    
    //Game loop
    while (game.runing())
    {
        //Update
        game.update();
        //Render
        game.render();
    }
    return 0;
}