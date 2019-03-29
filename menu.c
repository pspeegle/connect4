#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game.h"
#include "menu.h"

void initSettings(){
	clearFields();
	printf("************SETTINGS************\n\n");
	printf("       Select an Option Below:\n");
	printf("1 - Enable/Disable Animations\n");
	printf("2 - ");
}

void initMultiPlayer(){
	long int numRows = 0;
	long int numCols = 0;
	char p1[50];
	char p2[50];
	char *p1_n = (char*)malloc(50*sizeof(char));
	char *p2_n = (char*)malloc(50*sizeof(char));
	char *pEnd;
	bool o_turn = false;
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
	printf("Enter name of Player 1 (max 50 chars): ");
	fgets(p1, 50, stdin);
	p1_n = strtok(p1, "\n");
	printf("Enter name of Player 2 (max 50 chars): ");
	fgets(p2, 50, stdin);
	p2_n = strtok(p2, "\n");
	char **board = allocBoard(numCols,numRows);
	int **graph = allocGraph(numCols, numRows);
	clearFields();	
	graph = findOpenMoves(board, graph, numCols, numRows);
	printBoard(board, numCols, numRows);
	long int curCol = 0;
	char input[1000];
	while(1){
		if(o_turn == false){
			printf("%s, choose a column to place your piece (X) : ", p1);
			fgets(input, 1000, stdin);
			curCol = strtol(input, &pEnd, 10);
			printf("%ld", curCol);
			curCol--;
			if(insert(board,numCols,numRows, curCol, 'X') == 0) continue;
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
		}
		printf("%s, choose a column to place your piece (O) : ", p2);
		fgets(input, 1000, stdin);
		curCol = strtol(input, &pEnd, 10);
		printf("%ld", curCol);
		curCol--;
		if(insert(board,numCols,numRows, curCol, 'O') == 0){
			o_turn = true;
			continue;
		}
		o_turn = false;
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
	printf("Press enter to continue.");
	char buffer;
	scanf("%c", &buffer);
}

int dispMenu(){
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
	bool pressed_quit = false;
	while(1){
		switch(option){
			case '1':
				break;
			case '2':
				initMultiPlayer();
				break;
			case '3':
				printf("You chose option 3.\n");
				break;
			case '4':
				printf("You chose option 4.\n");
				break;
			case '5':
				printf("Hope to see you soon!\n");
				pressed_quit = true;
				break;
			default:
				break;
		}
		if(pressed_quit) return 1;
		return 0;
	}
	return 0;
}
