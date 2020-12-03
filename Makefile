
CXX = g++
LDLIBS=-lsfml-network  -lsfml-graphics  -lsfml-window  -lsfml-system
CPPFLAGS= ./src/

SRCS = game.cpp	Menu.cpp	RoomList.cpp
OBJS = game.o Menu.o RoomList.o

all	:	main	clean

main:	main.o	${OBJS}
	g++ -o main main.o ${OBJS} ${LDLIBS}
main.o:	main.cpp
	g++ -c main.cpp
game.o: ${CPPFLAGS}game.cpp
	${CXX} -c ${CPPFLAGS}game.cpp
Menu.o: ${CPPFLAGS}Menu.cpp
	${CXX} -c ${CPPFLAGS}Menu.cpp
RoomList.o: ${CPPFLAGS}RoomList.cpp
	${CXX} -c ${CPPFLAGS}RoomList.cpp
clean:
	rm -f *.o *~
