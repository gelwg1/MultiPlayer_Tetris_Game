
#pragma once
#include "SFML/Graphics.hpp"
#include <vector>

#define MAX_NUMBER_OF_PLAYERS 5

class GameRoom
{
public:
	GameRoom(sf::RenderWindow &window);
	std::string PName;
	void dienten(sf::RenderWindow &window);
	void vaophong(std::vector<sf::Text> PList ,sf::RenderWindow &window);
private:
	void draw(sf::RenderWindow &window);
	sf::Font font;
	sf::Text PList[MAX_NUMBER_OF_PLAYERS];

};
