play: connect.o game.o menu.o
	gcc connect.o game.o menu.o -o play
connect.o: connect.c menu.h
	gcc -c connect.c
game.o: game.c game.h
	gcc -c game.c
menu.o: menu.c game.h menu.h
	gcc -c menu.c
clean:
	rm -f connect.o game.o menu.o ./play
