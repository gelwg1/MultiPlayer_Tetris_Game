#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <unistd.h>
using namespace std;
using namespace sf;

bool is_port_open(IpAddress ip, int port)
{
    return (TcpSocket().connect(ip, port) == Socket::Done);
}

int main(int argc, char* argv[])
{
    IpAddress ip = IpAddress::getLocalAddress();
    TcpSocket socket;
    string mess;
    Packet packet;
    cout<<"Connecting" <<endl;
    // for (int i=6000; i<=7500; i++)
    // {
    //     if (is_port_open(ip, i))
    //         cout<<i<<" port detected"<<endl;
    // }
    socket.connect(ip, 7000);
    socket.setBlocking(false);
    cout<<"Connected" <<endl;

    RenderWindow window(VideoMode(320, 100), "Game Client");
    window.setFramerateLimit(50);
    Event e;

    while (window.isOpen())
    {
    	while (window.pollEvent(e))
    	{
    	    if (e.type == Event::Closed)
    		window.close();

            else if(e.type==Event::TextEntered)
        	{
                cout<<(char)(e.text.unicode);
                if (e.text.unicode == 13)
                {
                    packet<<mess;
                    socket.send(packet);
                    mess.clear();
                }
                else mess.push_back(e.text.unicode);
        	}
    	}
		if(socket.receive(packet) == Socket::Done)
		{
            packet>>mess;
            cout<<mess<<endl;
            mess.clear();
		}
        window.clear(Color::White);
        window.display();
    	usleep(200);
    }

	return 0;
}
