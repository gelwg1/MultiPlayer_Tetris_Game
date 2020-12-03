
#pragma once
#include "SFML/Graphics.hpp"

#define MAX_NUMBER_OF_PLAYERS 5

class Menu
{
public:
	Menu(float width, float height);
	~Menu();
	int selectedItemIndex;


private:
	void draw(sf::RenderWindow &window);
	sf::Font font;
	sf::Text PList[MAX_NUMBER_OF_PLAYERS];

};
