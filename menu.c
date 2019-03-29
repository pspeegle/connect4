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

void initMultiPlayer(double score1, double score2, int rows, int cols, char *play1, char *play2, bool already_played){
	long int numRows = rows;
	long int numCols = cols;
	char *p1;
	p1 = play1;
	char *p2;
	p2 = play2;
	char *p1_n = (char*)malloc(50*sizeof(char));
	char *p2_n = (char*)malloc(50*sizeof(char));
	char *pEnd;
	bool o_turn = false;
	clearFields();
	if(!already_played){
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
	}
	char **board = allocBoard(numCols,numRows);
	int **graph = allocGraph(numCols, numRows);
	clearFields();	
	graph = findOpenMoves(board, graph, numCols, numRows);
	printBoard(board, numCols, numRows);
	long int curCol = 0;
	char input[1000];
	bool bad_input = false;
	while(1){
		if(!bad_input) printf("SCORES: %s : %.1f ; %s : %.1f\n\n\n", p1, score1, p2, score2);
		if(o_turn == false){
			printf("%s, choose a column to place your piece (X) : ", p1);
			fgets(input, 1000, stdin);
			curCol = strtol(input, &pEnd, 10);
			curCol--;
			if(insert(board,numCols,numRows, curCol, 'X') == 0){ 
				bad_input = true;
				continue;
			}
			clearFields();
			printBoard(board, numCols, numRows);
			graph = findOpenMoves(board, graph, numCols, numRows);
			if(checkBoard(board,numCols,numRows)){
				printf("Player one wins!\n");
				score1++;
				break;
			}
			if(checkTies(graph, numCols, numRows)){
				printf("It's a tie!\n");
				score1 += 0.5;
				score2 += 0.5;
				break;
			}
			o_turn = true;
			bad_input = false;
			continue;
		}
		printf("%s, choose a column to place your piece (O) : ", p2);
		fgets(input, 1000, stdin);
		curCol = strtol(input, &pEnd, 10);
		curCol--;
		if(insert(board,numCols,numRows, curCol, 'O') == 0){
			o_turn = true;
			bad_input = true;
			continue;
		}
		o_turn = false;
		bad_input = false;
		clearFields();
		printBoard(board, numCols, numRows);
		graph = findOpenMoves(board, graph, numCols, numRows);
		if(checkBoard(board,numCols,numRows)){
			printf("Player two wins!\n");
			score2++;
			break;
		}
		if(checkTies(graph, numCols, numRows)){
			printf("It's a tie!\n");
			score1 += 0.5;
			score2 += 0.5;
			break;
		}
	}
	freeBoard(board, numRows+3);
	freeGraph(graph, numRows);
	already_played = true;
	printf("Press any key to exit, or 1 to play again.");
	char buffer;
	scanf("%c", &buffer);
	o_turn = false;
	if(buffer == '1'){
		initMultiPlayer(score1, score2, numRows, numCols, p1, p2, true);
	}
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
	char *p1 = (char*)malloc(50*sizeof(char*));
	char *p2 = (char*)malloc(50*sizeof(char*));
	char option;
	scanf("%c", &option);
	bool pressed_quit = false;
	while(1){
		switch(option){
			case '1':
				break;
			case '2':
				initMultiPlayer(0, 0, 0, 0, p1, p2, false);
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
