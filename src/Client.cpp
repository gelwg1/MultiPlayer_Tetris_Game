#include "Client.h"


Client::Client(int PORT)
{
    font.loadFromFile("IMG/simplistic_regular.ttf");
    socket.connect(ip, PORT);
    socket.setBlocking(false);

            // else if(e.type==Event::TextEntered)
        	// {
            //     cout<<(char)(e.text.unicode);
            //     if (e.text.unicode == 13)
            //     {
            //         packet<<mess;
            //         socket.send(packet);
            //         mess.clear();
            //     }
            //     else mess.push_back(e.text.unicode);
        	// }

}
void Client::SendPoint(string mess)
{
    packet<<mess;
    socket.send(packet);
    packet.clear();
}
bool Client::ReceiName(sf::RenderWindow &window)
{
    while (window.pollEvent(e))
    {
        if (e.type == Event::Closed)
        window.close();
    }
    if(socket.receive(packet) == Socket::Done)
    {
        string buf;
        while(1){
            packet>>buf;
            if (buf == "") break;
            takeOut(buf);
            index++;
        }
        return 1;
    }
    return 0;
}

void Client::takeOut(std::string mess)
{
    PList.push_back(sf::Text());
    PList[index].setFont(font);
    PList[index].setFillColor(sf::Color::Red);
    PList[index].setString(mess);
    PList[index].setCharacterSize(20);
    PList[index].setPosition(sf::Vector2f(20, 480 / (MAX_NUMBER_OF_PLAYERS + 1) * (index+1)));
}
