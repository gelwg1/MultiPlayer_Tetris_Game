#include "src/game.h"
#include "src/Menu.h"
#include "src/RoomList.h"
#include "src/GameRoom.h"
#include "src/Server.h"
#include "src/Client.h"
#include "src/MultiGame.h"

using namespace std;
using namespace sf;

int main()
{
    int lop=0;
    RenderWindow window(VideoMode(320, 480), "Tetris game");
    window.setFramerateLimit(50);
    Menu menu(window);
    if (menu.selectedItemIndex == 2)//--Become Guest----------------------
    {
        RoomList roomlist(window);
        GameRoom gameroom(window);//Lay ten nguoi choi
        Client guest(roomlist.rooms[roomlist.Index]);//Connect to Sever
        guest.SendPoint(gameroom.PName);
        while (window.isOpen())
        {
            guest.ReceiName(window);
            gameroom.vaophong(guest.PList , window);
            if (guest.DoneWaiting == 1)
            {
                //cout<<"11"<<endl;
                guest.InitiatePoint();
                //cout<<"22"<<endl;
                break;
            }
        }
        MultiGame run;
        while (window.isOpen())//Vao Game
        {
            run.ChayGame(window);
            run.PrintVector(window, guest.PList, guest.PPoint);
            window.display();
            if (run.changescore == 1)
            {
                guest.SendPoint(to_string(run.Score));
            }
        }
    }
    else if (menu.selectedItemIndex == 1)
    {//-----Become Server--------------------------------
        GameRoom gameroom(window);//Lay ten nguoi choi
        Server Ngoi(window, gameroom.PName);
        while (window.isOpen())//Trong phong Game
        {
            if (Ngoi.DoneWaiting == 1)
            {
                Ngoi.BroadcastOK();
                break;
            }
            else
            {
                Ngoi.Waiting(window);
                gameroom.vaophong(Ngoi.PList , window);
            }
        }
        Game run;
        while (window.isOpen())//Vao Game
        {
            run.ChayGame(window);
            Ngoi.RecScore();
        }
    }
    else//----------Single Player---------------
    {
        Game run;
        while (window.isOpen())
        {
            run.ChayGame(window);
        }
    }
    return 0;
}
