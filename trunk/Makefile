sc-le: main.o board.o point.o misc.o holder.o opponent.o scoreboard.o
	g++ main.o board.o point.o misc.o holder.o opponent.o scoreboard.o -o sc-le -lncurses

main.o: main.cpp board.o opponent.o scoreboard.o
	g++ main.cpp -o main.o -c

board.o: board.h board.cpp point.o misc.o holder.o
	g++ board.cpp -o board.o -c

point.o: point.h point.cpp
	g++ point.cpp -o point.o -c

misc.o: misc.h misc.cpp
	g++ misc.cpp -o misc.o -c

holder.o: holder.h holder.cpp
	g++ holder.cpp -o holder.o -c

opponent.o: opponent.h opponent.cpp
	g++ opponent.cpp -o opponent.o -c

scoreboard.o: scoreboard.h scoreboard.cpp
	g++ scoreboard.cpp -o scoreboard.o -c

clear:
	rm -v *.o
