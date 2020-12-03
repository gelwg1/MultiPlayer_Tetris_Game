#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <vector>
#include <memory>
using namespace std;
using namespace sf;

class Server
{
	public:
		Server(int PORT);

	private:
		IpAddress ip = IpAddress::getLocalAddress();
		std::array<int, 7> rooms = {0};
		int NumberOfRooms = 0;
		bool is_port_open(IpAddress ip, int port);
		void ScanPort();
		void SetRooms(float height);
		void draw(sf::RenderWindow &window);
		void MoveUp();
		void MoveDown();
		sf::Font font;
		sf::Text roomList[7];
};
