
#include "src/game.h"
#include "src/Menu.h"
#include "src/RoomList.h"
//#include "GameRoom.h"
//#include "Server.h"
//#include "Client.h"

using namespace std;
using namespace sf;

int main()
{
    RenderWindow window(VideoMode(320, 480), "Tetris game");
    window.setFramerateLimit(50);
    Menu menu(window);
    if (menu.selectedItemIndex == 1)//--Become Guest-----
        RoomList roomlist(window);
    else if (menu.selectedItemIndex == 2)
    {//-----Become Server--------------------------------

    }
    Game run;
    while (window.isOpen())
    {
        run.ChayGame(window);
    }
    return 0;
}
