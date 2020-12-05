#include "GameRoom.h"
#include <string>

GameRoom::GameRoom(sf::RenderWindow &window)
{
	font.loadFromFile("IMG/simplistic_regular.ttf");
	dienten(window); //Lay ten nguoi choi vao PName
	// menu[0].setFont(font);
	// menu[0].setFillColor(sf::Color::Red);
	// menu[0].setString("Play");
	// menu[0].setPosition(sf::Vector2f(50, height / (MAX_NUMBER_OF_PLAYERS + 1) * 1));
	//
	// menu[1].setFont(font);
	// menu[1].setFillColor(sf::Color::White);
	// menu[1].setString("Create Room");
	// menu[1].setPosition(sf::Vector2f(50, height / (MAX_NUMBER_OF_PLAYERS + 1) * 2));
	// Index = 0;
}


void GameRoom::dienten(sf::RenderWindow &window)
{
	sf::Text playerText;
	playerText.setFont(font);
	playerText.setFillColor(sf::Color::Red);
	playerText.setPosition(sf::Vector2f(50, 480 / (MAX_NUMBER_OF_PLAYERS + 1) * 2));

	sf::Text NterName;
	NterName.setFont(font);
	NterName.setFillColor(sf::Color::Red);
	NterName.setString("Enter your name");
	NterName.setPosition(sf::Vector2f(20, 480 / (MAX_NUMBER_OF_PLAYERS + 1) * 1));

	bool men = 0;
	sf::Event e;
	while (window.isOpen())
	{
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
			window.close();
			if (e.type == sf::Event::TextEntered)
			{
				if(e.text.unicode==13) {men = 1;break;}
				PName +=static_cast<char>(e.text.unicode);
			    playerText.setString(PName);
			}
		}
		window.clear();
		window.draw(NterName);
		window.draw(playerText);
		window.display();
		sf::sleep(sf::milliseconds(20));
		if(men == 1)
			break;
	}
}

// void PrinVector(std::vector<int> PList)
// {
//     for(auto const& value: PList) {
//         cout<<value<<std::endl;
//     }
// }

void GameRoom::vaophong(std::vector<sf::Text> PList , sf::RenderWindow &window)
{

	window.clear();
	for(auto const& value: PList) {
        window.draw(value);
    }
	window.display();
	sf::sleep(sf::milliseconds(20));
}

void GameRoom::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < MAX_NUMBER_OF_PLAYERS; i++)
	{
		window.draw(PList[i]);
	}
}
