#include "Client.h"


Client::Client(int PORT)
{
    font.loadFromFile("IMG/simplistic_regular.ttf");
    socket.connect(ip, PORT);
    socket.setBlocking(false);
}
void Client::SendPoint(string mess)
{
    packet.clear();
    packet<<mess;
    socket.send(packet);
}
bool Client::ReceiName(sf::RenderWindow &window)
{
    packet.clear();
    string buf;
    while (window.pollEvent(e))
    {
        if (e.type == Event::Closed)
        window.close();
    }
    if(socket.receive(packet) == Socket::Done)
    {
        if (ReceivedName != true)
        while(1){
            packet>>buf;
            if (buf == "") break;
            else if(buf == "OK") {DoneWaiting = 1;break;}
            takeOut(buf);
        }
        else
        for(int i =0; i<=index;i++){
            packet>>buf;
            if (i==index) {takeOut(buf); break;}
            else if(buf == "OK") {DoneWaiting = 1;break;}
        }
        ReceivedName = true;
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
    index++;
}

void Client::InitiatePoint()
{
    for (int i=0; i<PList.size(); i++)
    {
        PList[i].setPosition(sf::Vector2f(220, 480 / (MAX_NUMBER_OF_PLAYERS + 1) * (i+1)));
        PPoint.push_back(sf::Text());
        PPoint[i].setFont(font);
        PPoint[i].setFillColor(sf::Color::Red);
        PPoint[i].setString("0");
        PPoint[i].setCharacterSize(20);
        PPoint[i].setPosition(sf::Vector2f(250, 20+480 /(MAX_NUMBER_OF_PLAYERS + 1) * (i+1)));
    }
}
void Client::ReceiveScore()
{
    packet.clear();
    if(socket.receive(packet) == Socket::Done)
    {
        string mess[3];
        for(int i=0; i<3; i++){
            packet>>mess[i];
        }
        packet.clear();
		if (mess[2]==""){
            mess[2] = mess[1];
            mess[1] = mess[0];
        }
        if (mess[1]=="death") {
            PList[stoi(mess[2])].setFillColor(sf::Color::Yellow);
            PPoint[stoi(mess[2])].setFillColor(sf::Color::Yellow);
        }
        else if (mess[1]=="TheGameIsOver"){
          IsGameOver = 1;
        }
        else  PPoint[stoi(mess[2])].setString(mess[1]);
    }
}
// void swap(int *a, int*b){
// 	int *c = a;
// 	a = b;
// 	b = c;
// }
void Client::calculatePoint(){
      std::vector<int> sss;
      int i= 0 ;
      for(auto const& value: PPoint) {
          sss.push_back(stoi(value.getString().toAnsiString()));
          thu_tu.push_back(i);
          i++;
      }
      for(int counterrrs=i-1; counterrrs>=0; counterrrs--){
    		for (int j = 0; j < counterrrs; j++) {
    			if (sss[j]<sss[j+1]){
    				swap(sss[j],sss[j+1]);
            swap(thu_tu[j],thu_tu[j+1]);
    			}
    		}
    	}
      i=0;
      for(auto const& value: thu_tu)
      {
          PList[i].setPosition(sf::Vector2f(120, (480 / 7) * (value+1)));
          PPoint[i].setPosition(sf::Vector2f(150, ((20+480) /7) * (value+1)));
          i++;
      }
    }
