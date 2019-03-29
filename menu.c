#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game.h"
#include "menu.h"

void initSinglePlayer(){
	long int numRows = 0;
	long int numCols = 0;
	char *pEnd;
	clearFields();
	printf("How many rows would you like in the game? NOTE: Any character input will be ignored. Any size above 50 might cause odd formatting.\n");
	while(1){
		char input[100];
		fgets(input, 100, stdin);
		numRows = strtol(input, &pEnd, 10);
		if(numRows < 4){
			printf("Please choose a number that is 4 or greater.\n");
			continue;
		}
		break;
	}
	printf("How many columns would you like in the game?\n");
	while(1){
		char input[100];
		char *pEnd;
		fgets(input, 100, stdin);
		numCols = strtol(input, &pEnd, 10);
		if(numCols < 4){
			printf("Please choose a number that is 4 or greater.\n");
			continue;
		}
		break;
	}	
	char **board = allocBoard(numCols,numRows);
	int **graph = allocGraph(numCols, numRows);
	clearFields();	
	graph = findOpenMoves(board, graph, numCols, numRows);
	printBoard(board, numCols, numRows);
	while(1){
		insert(board,numCols,numRows,'X');
		clearFields();
		printBoard(board, numCols, numRows);
		graph = findOpenMoves(board, graph, numCols, numRows);
		if(checkBoard(board,numCols,numRows)){
			printf("Player one wins!\n");
			break;
		}
		if(checkTies(graph, numCols, numRows)){
			printf("It's a tie!\n");
			break;
		}
		insert(board,numCols,numRows,'O');
		clearFields();
		printBoard(board, numCols, numRows);
		graph = findOpenMoves(board, graph, numCols, numRows);
		if(checkBoard(board,numCols,numRows)){
			printf("Player two wins!\n");
			break;
		}
		if(checkTies(graph, numCols, numRows)){
			printf("It's a tie!\n");
			break;
		}
	}
	freeBoard(board, numRows+3);
	freeGraph(graph, numRows);
}

void dispMenu(){
	clearFields();
	printf("************WELCOME TO CONNECT FOUR IN A ROW************\n\n");
	printf("                 Select an Option Below:                \n");
	printf("1 - Single Player VS Computer                           \n");
	printf("2 - Multiplayer                                         \n");
	printf("3 - Settings                                            \n");
	printf("4 - How to Play                                         \n");
	printf("5 - Quit                                                \n");

	char option;
	scanf("%c", &option);

	switch(option){
		case '1':
			initSinglePlayer();
			break;
		case '2':
			printf("You chose option 2.\n");
			break;
		case '3':
			printf("You chose option 3.\n");
			break;
		case '4':
			printf("You chose option 4.\n");
			break;
		case '5':
			printf("You chose option 5.\n");
			break;
		default:
			printf("Invalid Option.\n");
			break;		
	}
}
