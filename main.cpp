#include "src/game.h"
#include "src/Menu.h"
#include "src/RoomList.h"
#include "src/GameRoom.h"
#include "src/Server.h"
#include "src/Client.h"

using namespace std;
using namespace sf;

int main()
{
    int lop=0;
    RenderWindow window(VideoMode(320, 480), "Tetris game");
    window.setFramerateLimit(50);
    Menu menu(window);
    if (menu.selectedItemIndex == 2)//--Become Guest-----
    {
        RoomList roomlist(window);
        GameRoom gameroom(window);//Lay ten nguoi choi
        Client guest(roomlist.rooms[roomlist.Index]);//Connect to Sever
        guest.SendPoint(gameroom.PName);
        while (window.isOpen())
        {
            guest.ReceiName(window);
            gameroom.vaophong(guest.PList , window);
            // if (runn.changescore)
            // {
            //     guest.SendPoint(to_string(runn.Score));
            // }
        }
    }
    else if (menu.selectedItemIndex == 1)
    {//-----Become Server--------------------------------
        GameRoom gameroom(window);//Lay ten nguoi choi
        Server Ngoi(7200, window, gameroom.PName);
        while (window.isOpen())//Trong phong Game
        {
            if (Ngoi.DoneWaiting == 1)
            {
                Game run;
                run.ChayGame(window);
            }
            else
            {
                Ngoi.Waiting(window);
                gameroom.vaophong(Ngoi.PList , window);
            }
        }
    }
    else
    {
        Game run;
        while (window.isOpen())
        {
            run.ChayGame(window);
        }
    }
    return 0;
}
