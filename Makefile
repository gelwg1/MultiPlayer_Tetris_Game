all : main	clean

main: main.o	game.o	Menu.o	RoomList.o
	g++ main.o -o main RoomList.o -lsfml-network -lsfml-graphics -lsfml-window -lsfml-system game.o Menu.o 
main.o:	main.cpp
	g++ -c main.cpp
game.o:	game.cpp
	g++ -c game.cpp
Menu.o:	Menu.cpp
	g++ -c Menu.cpp
RoomList.o:	RoomList.cpp
	g++ -c RoomList.cpp -lsfml-network
clean:
	rm -f *.o *~
