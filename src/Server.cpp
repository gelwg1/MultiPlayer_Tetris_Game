#include "Server.h"


Server::Server(sf::RenderWindow &window, std::string PName)
{
    // TcpSocket socket[5];
    srand((unsigned) time(0));
    PORT = 7000 + (rand() % 1000);

    font.loadFromFile("IMG/simplistic_regular.ttf");
    socket.push_back(make_unique<TcpSocket>());
    cout<<"listening"<<endl;
    listener.listen(PORT);
    listener.setBlocking(false);
    takeIn(PName);
}
void Server::Broadcast()
{
    string mess;
    for (int j=index-1; j>=0; j--)
    {
        mess = PList[j].getString();
        packet<<mess;
    }
    for(auto const& value: socket) {
        value->send(packet);
    }
    packet.clear();
}
void Server::BroadcastOK()
{
    string mess = "OK";
    packet<<mess;
    for(auto const& value: socket) {
        value->send(packet);
    }
    packet.clear();
}

void Server::Waiting(sf::RenderWindow &window)
{
    while (window.pollEvent(e))
    {
        if (e.type == Event::Closed)
        window.close();
        if (e.type == Event::KeyPressed && e.key.code==Keyboard::Enter)
            DoneWaiting = 1;
        // else if(e.type==Event::TextEntered)
        // {
        //     if (e.text.unicode == 13 && index>0)
        //     {
        //         packet<<mess;
        //         for (int j=0; j<index; j++)
        //         {
        //     		socket[j]->send(packet);
        //             mess.clear();
        //         }
        //     }
        //     else mess.push_back(e.text.unicode);
        // }
    }
    if (listener.accept(*socket[index]) == Socket::Done)//Bug: Rec Scanner
    {

        socket[index]->setBlocking(false);
        socket[index]->receive(packet);//Read in PName
        packet>>str;
        if (str != "")
        {
            cout<<"Player : "+str<<endl;

            socket.push_back(make_unique<TcpSocket>());
            index++;
            takeIn(str);
            Broadcast();
        }
    }
    for (int j=0; j<index; j++)
    {
        status = socket[j]->receive(packet);
        if (status == Socket::Disconnected)
        {
            socket.erase (socket.begin()+j);
            PList.erase (PList.begin()+j);
            index--;
            Broadcast();
        }
    }
}

void Server::takeIn(std::string mess)
{
    PList.push_back(sf::Text());
    PList[index].setFont(font);
    PList[index].setFillColor(sf::Color::Red);
    PList[index].setString(mess);
    PList[index].setCharacterSize(20);
    PList[index].setPosition(sf::Vector2f(20, 480 / (MAX_NUMBER_OF_PLAYERS + 1) * (index+1)));
}

bool Server::RecScore()
{
    bool a=0;
    std::string buf;
    for (int j=0; j<index; j++)
    {
        if (socket[j]->receive(packet) == Socket::Done)
        {
            packet>>buf;
            cout<<buf<<endl;
            a=1;
        }
    }
    return a;
}
