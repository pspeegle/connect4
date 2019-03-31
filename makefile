play: connect.o game.o menu.o
	gcc -std=c11 connect.o game.o menu.o -o play
connect.o: connect.c menu.h
	gcc -std=c11 -c connect.c
game.o: game.c game.h
	gcc -std=c11 -c game.c
menu.o: menu.c game.h menu.h
	gcc -std=c11 -c menu.c
clean:
	rm -f connect.o game.o menu.o ./play
