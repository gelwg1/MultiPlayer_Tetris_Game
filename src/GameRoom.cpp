#include "GameRoom.h"


Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("IMG/simplistic_regular.ttf"))
	{
		// handle error
	}

	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Play");
	menu[0].setPosition(sf::Vector2f(50, height / (MAX_NUMBER_OF_PLAYERS + 1) * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Create Room");
	menu[1].setPosition(sf::Vector2f(50, height / (MAX_NUMBER_OF_PLAYERS + 1) * 2));

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Joint Room");
	menu[2].setPosition(sf::Vector2f(50, height / (MAX_NUMBER_OF_PLAYERS + 1) * 3));

	selectedItemIndex = 0;
}


void Menu::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < MAX_NUMBER_OF_PLAYERS; i++)
	{
		window.draw(menu[i]);
	}
}
