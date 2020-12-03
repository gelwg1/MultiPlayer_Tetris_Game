#include "RoomList.h"

RoomList::RoomList(sf::RenderWindow &window)
{
	float width = window.getSize().x; float height = window.getSize().y;
	if (!font.loadFromFile("IMG/simplistic_regular.ttf"))
	{
		// handle error
	}

	Index = 1;
	bool men = 0;
	Clock clock;
	Event e;
	while (window.isOpen())
	{
		if(clock.getElapsedTime().asSeconds()>2)
		{
			clock.restart();
			ScanPort();
			SetRooms(height);
		}
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
			window.close();
			if (e.type == Event::KeyPressed)
			if (e.key.code==Keyboard::Up) MoveUp();
			else if (e.key.code==Keyboard::Down) MoveDown();
			else if (e.key.code==Keyboard::Enter) men =1;
		}
		window.clear();
		draw(window);
		window.display();
		sf::sleep(sf::milliseconds(20));
		if(men == 1) break;
	}
}

bool RoomList::is_port_open(IpAddress ip, int port)
{
    return (sf::TcpSocket().connect(ip, port) == sf::Socket::Done);
}

void RoomList::ScanPort()
{
	rooms.fill(0);
	int j=0;
	for (int i=5000; i<=8000; i++)
	{
		if (is_port_open(ip, i) && j<7)
		{
			rooms[j]=i; j++;
		}
	}
	NumberOfRooms = j;
}
void RoomList::SetRooms(float height)
{
	int j=0;
	for(int i=0; i<NumberOfRooms;i++)
	if (rooms[i]!=0)
	{
		roomList[j].setFont(font);
		roomList[j].setFillColor(sf::Color::Red);
		roomList[j].setString("room  "+ to_string(rooms[i]));
		roomList[j].setCharacterSize(15);
		roomList[j].setPosition(sf::Vector2f(50, height / (7 + 1) * j));
		j++;
	}
}
void RoomList::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < NumberOfRooms; i++)
	{
		window.draw(roomList[i]);
	}
}

void RoomList::MoveUp()
{
	if (Index > 1)
	{
		roomList[Index].setFillColor(sf::Color::White);
		Index--;
		roomList[Index].setFillColor(sf::Color::Red);
	}
}

void RoomList::MoveDown()
{
	if (Index < NumberOfRooms)
	{
		roomList[Index].setFillColor(sf::Color::White);
		Index++;
		roomList[Index].setFillColor(sf::Color::Red);
	}
}
