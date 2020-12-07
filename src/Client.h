#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#define MAX_NUMBER_OF_PLAYERS 5
using namespace std;
using namespace sf;

class Client
{
	public:
		Client(int PORT);
        void SendPoint(string mess);
		bool ReceiName(sf::RenderWindow &window);
		void InitiatePoint();
		void ReceiveScore();

		vector<sf::Text> PList;
		vector<sf::Text> PPoint;
		bool DoneWaiting = 0;
		bool ReceivedName = 0;
	private:
		sf::Font font;
		int index = 0;
		sf::Event e;
        IpAddress ip = IpAddress::getLocalAddress();
        TcpSocket socket;
        Packet packet;

		void takeOut(std::string mess);


};
