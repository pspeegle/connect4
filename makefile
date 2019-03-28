all: main
	
main: connect.c
	gcc connect.c -o connect
