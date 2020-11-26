#include <iostream>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <sstream>
#include <time.h>
using namespace std;
using namespace sf;

const int M = 20;
const int N = 10;

bool field[N][M] = {0};

struct Point
{int x,y;} Piece[4];
struct
{float x,y;} Center;
unsigned int Score=0;
void reset(struct Point Piece[4], bool field[N][M])
{
    int PieceType =  1 + (rand() % 7);
    switch (PieceType) {
	case 1: Piece[0].x = 4;  Piece[0].y = 0;
		Piece[1].x = 4;  Piece[1].y = 1;
		Piece[2].x = 4;  Piece[2].y = 2;
		Piece[3].x = 4;  Piece[3].y = 3;
		Center.x = 4.5;  Center.y = 1.5;
		break;
	case 2: Piece[0].x = 4;  Piece[0].y = 0;
		Piece[1].x = 4;  Piece[1].y = 1;
		Piece[2].x = 5;  Piece[2].y = 1;
		Piece[3].x = 5;  Piece[3].y = 2;
		Center.x = 5;  Center.y = 1;
		break;
	case 3: Piece[0].x = 5;  Piece[0].y = 0;
		Piece[1].x = 5;  Piece[1].y = 1;
		Piece[2].x = 4;  Piece[2].y = 1;
		Piece[3].x = 4;  Piece[3].y = 2;
		Center.x = 5;  Center.y = 1;
		break;
	case 4: Piece[0].x = 4;  Piece[0].y = 0;
		Piece[1].x = 4;  Piece[1].y = 1;
		Piece[2].x = 5;  Piece[2].y = 1;
		Piece[3].x = 4;  Piece[3].y = 2;
		Center.x = 4;	Center.y = 1;
		break;
	case 5: Piece[0].x = 4;  Piece[0].y = 0;
		Piece[1].x = 4;  Piece[1].y = 1;
		Piece[2].x = 5;  Piece[2].y = 0;
		Piece[3].x = 5;  Piece[3].y = 1;
		Center.x = 4.5;	Center.y = 0.5;
		break;
	case 6: Piece[0].x = 4;  Piece[0].y = 0;
		Piece[1].x = 5;  Piece[1].y = 0;
		Piece[2].x = 4;  Piece[2].y = 1;
		Piece[3].x = 4;  Piece[3].y = 2;
		Center.x = 4;	Center.y = 1;
		break;
	case 7: Piece[0].x = 4;  Piece[0].y = 0;
		Piece[1].x = 5;  Piece[1].y = 0;
		Piece[2].x = 5;  Piece[2].y = 1;
		Piece[3].x = 5;  Piece[3].y = 2;
		Center.x = 5;	Center.y = 1;
		break;
    }
    for (int i=0;i<4;i++)
	field[Piece[i].x][Piece[i].y] = 1;
}
bool check(int x, int y)
{
    for (int i=0; i<4; i++)
    {
	if ((Piece[i].x == x) && (Piece[i].y == y))
	    return 0;
    }
    return 1;
}
bool canMoveDown()
{

    for (int i=0;i<4;i++)
	if (((field[Piece[i].x][Piece[i].y+1]==1) && check(Piece[i].x,Piece[i].y+1))
		|| (Piece[i].y == M-1))
	    return 0;
    return 1;
}
void MoveDown(struct Point Piece[4], bool field[N][M])
{
    for (int i=0;i<4;i++)
    {
	field[Piece[i].x][Piece[i].y] = 0;
	Piece[i].y++;
    }
    for (int i=0;i<4;i++)
	field[Piece[i].x][Piece[i].y] = 1;
    Center.y++;
}
bool CanMoveLeft()
{
    for (int i=0;i<4;i++)
	if (((field[Piece[i].x-1][Piece[i].y]==1) && check(Piece[i].x-1,Piece[i].y))
		|| (Piece[i].x == 0))
	    return 0;
    return 1;
}
void MoveLeft(struct Point Piece[4], bool field[N][M])
{
    if(CanMoveLeft())
    {
	for (int i=0;i<4;i++)
	{
	    field[Piece[i].x][Piece[i].y] = 0;
	    Piece[i].x--;
	}
	for (int i=0;i<4;i++)
	    field[Piece[i].x][Piece[i].y] = 1;
	Center.x--;
    }
}
bool CanMoveRight()
{
    for (int i=0;i<4;i++)
	if (((field[Piece[i].x+1][Piece[i].y]==1) && check(Piece[i].x+1,Piece[i].y))
		|| (Piece[i].x == N-1))
	    return 0;
    return 1;
}
void MoveRight(struct Point Piece[4], bool field[N][M])
{
    if(CanMoveRight())
    {
	for (int i=0;i<4;i++)
	{
	    field[Piece[i].x][Piece[i].y] = 0;
	    Piece[i].x++;
	}
	for (int i=0;i<4;i++)
	    field[Piece[i].x][Piece[i].y] = 1;
	Center.x++;
    }
}
bool CanRotate()
{
    float posx, posy;
    for (int i=0; i<4; i++)
    {
	posx = Piece[i].x - Center.x;
	posy = Piece[i].y - Center.y;
	int a = (int)(Center.x - posy);
	int b = (int)(Center.y + posx);
	if ((field[a][b]==1 && check(a,b)) || !(a>=0 && b>=0 && a<N && b<M))
	    return 0;
    }
    return 1;
}
void Rotate(struct Point Piece[4], bool field[N][M])
{
    float posx, posy;
    if(CanRotate())
    {
	for (int i=0; i<4; i++)
	{
	    posx = Piece[i].x - Center.x;
	    posy = Piece[i].y - Center.y;
	    field[Piece[i].x][Piece[i].y] = 0;

	    Piece[i].x = (int)(Center.x - posy);
	    Piece[i].y = (int)(Center.y + posx);
	}
	for (int i=0;i<4;i++)
	    field[Piece[i].x][Piece[i].y] = 1;
    }
}
void MoveRows(int i, bool field[N][M])
{
    for(int j=i; j>0; j--)
	for(int q=0; q<N; q++)
	    field[q][j] = field[q][j-1];
    for (int q=0; q<N; q++)
	field[1][0] = 0;
}
int CountScore(int Point)
{
    switch (Point)
    {
	case 1 : return 40;
	case 2 : return 100;
	case 3 : return 300;
	case 4 : return 1200;
	default : return 0;
    }
}
void DeleteRow(bool field[N][M])
{
    bool a; int Point = 0;
    for (int i=0; i<M; i++)
    {
	a = true;
	for (int j=0 ; j<N; j++)
	    a = a && field[j][i]; 
	if (a)
	{
	    MoveRows(i, field); Point++;
	}
    }
    Score += CountScore(Point);
}
void DeathCheck()
{
    for (int i=0; i<4; i++)
	if (Piece[i].y==0 && Piece[i].x==4)
	{
	    cout<<"Final score: "<<Score<<endl;
	    exit(0);
	}
}
int main()
{
    srand(time(NULL));
    RenderWindow window(VideoMode(320, 480), "Tetris game");
    window.setFramerateLimit(50);

    Texture t1,t2;
    t1.loadFromFile("IMG/Pit.png");
    t2.loadFromFile("IMG/L.png");

    Sprite s(t2), background(t1);

    Font myFont;
    myFont.loadFromFile("IMG/simplistic_regular.ttf");

    Text score;
    score.setFont(myFont);
    score.setFillColor(Color::Red);
    score.setStyle(sf::Text::Regular);
    score.setString("Score");
    score.setCharacterSize(25);
    score.setPosition(220, 20);

    Text scoreCurrent;
    scoreCurrent.setFont(myFont);
    scoreCurrent.setFillColor(Color::Red);
    scoreCurrent.setStyle(Text::Regular);
    scoreCurrent.setCharacterSize(25);
    scoreCurrent.setPosition(240, 50);

    float timer=0,delay=0.4;
    Clock clock;
    reset(Piece, field);
    while (window.isOpen())
    {
	float time = clock.getElapsedTime().asSeconds();
	clock.restart();
	timer+=time;
	Event e;
	while (window.pollEvent(e))
	{
	    if (e.type == Event::Closed)
		window.close();

	    if (e.type == Event::KeyPressed)
		if (e.key.code==Keyboard::Up) Rotate(Piece, field);
		else if (e.key.code==Keyboard::Left) MoveLeft(Piece, field);
		else if (e.key.code==Keyboard::Right) MoveRight(Piece, field);
	}

	if (Keyboard::isKeyPressed(Keyboard::Down)) delay=0.05;
	else delay = 0.3;
	if (timer>delay)
	{
	    if (canMoveDown())
		MoveDown(Piece,field);
	    else
	    {
		DeathCheck();
		DeleteRow(field);
		reset(Piece, field);
	    }
	    timer=0;
	}
	window.clear();
	window.draw(background);
	/*---------DRAW TABLE---------*/
	for (int i=0;i<N;i++)
	    for (int j=0;j<M;j++)
		if (field[i][j]==1)
		{
		    s.setPosition(i*20+5,j*20+5);
		    window.draw(s);
		}
	stringstream s;
	s << Score;
	scoreCurrent.setString(s.str());

	window.draw(score);
	window.draw(scoreCurrent);
	window.display();
	usleep(20);
    }
    return 0;
}
