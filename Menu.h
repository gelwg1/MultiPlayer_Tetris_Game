
#pragma once
#include "SFML/Graphics.hpp"

#define MAX_NUMBER_OF_ITEMS 3

class Menu
{
public:
	Menu(float width, float height);
	~Menu();
	int selectedItemIndex;
	void draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();

private:

	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];

};
