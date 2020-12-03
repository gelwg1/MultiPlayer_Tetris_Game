#include <iostream>
#include <SFML/Graphics.hpp>
#include "game.h"
#include "Menu.h"
#include "RoomList.h"

using namespace std;
using namespace sf;

int main()
{
    RenderWindow window(VideoMode(320, 480), "Tetris game");
    window.setFramerateLimit(50);
    Menu menu(window);
    if (menu.selectedItemIndex == 1)
        RoomList roomlist(window);
    Game run;
    while (window.isOpen())
    {
        run.ChayGame(window);
    }
    return 0;
}
