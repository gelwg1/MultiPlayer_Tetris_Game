all : game	clean

game: main.o	Menu.o
	g++ main.o -o game -lsfml-graphics -lsfml-window -lsfml-system Menu.o
main.o:	main.cpp Menu.h
	g++ -c main.cpp Menu.h
Menu.o: Menu.cpp
	g++ -c Menu.cpp
clean:
	rm -f *.o *~
