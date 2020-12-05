#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <vector>
#include <memory>
using namespace std;
using namespace sf;
#define MAX_NUMBER_OF_PLAYERS 5

class Server
{
	public:
		Server(int PORT, sf::RenderWindow &window,std::string PName);
		void Waiting(sf::RenderWindow &window);
		bool DoneWaiting = 0;
		vector<sf::Text> PList;
	private:
		void Broadcast();
		Socket::Status status;
		Packet packet;
		int index=0;
		vector <unique_ptr<TcpSocket>> socket;
		void draw(sf::RenderWindow &window);
		void takeIn(std::string mess);
		string str;
		sf::Text takeOut(std::string mess);
		TcpListener listener;
		Event e;
		sf::Font font;

};
