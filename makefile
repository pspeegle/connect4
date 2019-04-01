play: connect.o game.o menu.o
	gcc -std=c11 -Wall connect.o game.o menu.o -o play
connect.o: connect.c menu.h
	gcc -std=c11 -Wall -c connect.c
game.o: game.c game.h
	gcc -std=c11 -Wall -c game.c
menu.o: menu.c game.h menu.h
	gcc -std=c11 -Wall -c menu.c
clean:
	rm -f connect.o game.o menu.o ./play
