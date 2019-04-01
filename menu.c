#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game.h"
#include "menu.h"

bool initSettings(bool animation_on){
	char input;
	clearFields();
	printf("************SETTINGS************\n\n");
	printf("       Select an Option Below:\n");
	printf("1 - Enable/Disable Animations\n");
	printf("2 - Quit\n");
	scanf(" %c", &input);
	if(input == '1') animation_on = !animation_on;
	return animation_on;
}

void initSinglePlayer(double score1, double score2, int rows, int cols, int d, char *play1, bool already_played, bool animation_on){
	long int numRows = rows;
	long int numCols = cols;
	int difficulty = d;
	char* p1 = play1;
	bool setting = animation_on;
	bool o_turn = false;
	char *pEnd;
	clearFields();
	printf("\e[?25h");
	if(already_played){
		getchar();
	}
	if(!already_played){
		printf("How many rows would you like in the game? NOTE: Any character input will be ignored. Any size above 50 might cause odd formatting. Any size above 10 makes for weird animations.\n");
		printf("\e[?25h");
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
		scanf("%s", p1);
		getchar();
		printf("Choose difficulty: (1 - Trivially Easy, 2 - Pretty Easy, 3 - Normal)");
		while(1){
			char input[100];
			char *pEnd;
			fgets(input, 100, stdin);
			difficulty = strtol(input, &pEnd, 10);
			if(difficulty < 1 || difficulty > 3){
				printf("Please choose one of the options.\n");
				continue;
			}
			break;
		}
	}
	char **board = allocBoard(numCols,numRows);
	clearFields();	
	printBoard(board, numCols, numRows);
	long int curCol = 0;
	char input[1000];
	bool bad_input = false;
	move bestMove = {-1, -1};
	//getchar();
	while(1){
		if(!bad_input) printf("NOTE: Disable animations in SETTINGS. SCORES: %s : %.1f ; Computer : %.1f\n\n\n", p1, score1, score2);
		if(!o_turn){
			printf("Choose a column to place your piece (X) : ");
			fgets(input, 1000, stdin);
			curCol = strtol(input, &pEnd, 10);
			curCol--;
			if(insert(board,numCols,numRows, curCol, 'X', setting) == 0){ 
				bad_input = true;
				continue;
			}
			clearFields();
			printBoard(board, numCols, numRows);
			if(checkBoard(board,numCols,numRows)){
				printf("Player one wins!\n");
				score1++;
				break;
			}
			if(checkTies(board, numCols, numRows)){
				printf("It's a tie!\n");
				score1 += 0.5;
				score2 += 0.5;
				break;
			}
			o_turn = true;
			bad_input = false;
			continue;
		}
		if(o_turn){
			bestMove = findBestMove(board, numCols, numRows, difficulty);
			if(bestMove.column == -1){
				//this should never happen, means the computer could not find a single move
				insert(board, numCols, numRows, 1, 'O', setting);
			}
			else{
				insert(board, numCols, numRows, bestMove.column, 'O', setting);
			}
			clearFields();
			printBoard(board, numCols, numRows);
			if(checkBoard(board,numCols,numRows)){
				printf("Player two wins!\n");
				score2++;
				break;
			}
			if(checkTies(board, numCols, numRows)){
				printf("It's a tie!\n");
				score1 += 0.5;
				score2 += 0.5;
				break;
			}
			o_turn = false;
		}
	}	
	freeBoard(board, numRows+3);
	already_played = true;
	printf("Press any key to exit, or 1 to play again.");
	char buffer;
	scanf("%c", &buffer);
	o_turn = false;
	if(buffer == '1'){
		initSinglePlayer(score1, score2, numRows, numCols, difficulty, p1, true, setting);
	}
}
void initMultiPlayer(double score1, double score2, int rows, int cols, char *play1, char *play2, bool already_played, bool animation_on){
	long int numRows = rows;
	long int numCols = cols;
	bool setting = animation_on;
	char *p1;
	p1 = play1;
	char *p2;
	p2 = play2;
	char *pEnd;
	bool o_turn = false;
	clearFields();
	if(!already_played){
		printf("How many rows would you like in the game? NOTE: Any character input will be ignored. Any size above 50 might cause odd formatting. Any size above 10 makes for weird animations.\n");
		printf("\e[?25h");
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
		scanf("%s", p1);
		printf("Enter name of Player 2 (max 50 chars): ");
		scanf("%s", p2);
	}
	printf("\e[?25l");
	char **board = allocBoard(numCols,numRows);
	clearFields();	
	printBoard(board, numCols, numRows);
	long int curCol = 0;
	char input[1000];
	bool bad_input = false;
	getchar();
	while(1){
		if(!bad_input) printf("NOTE: Disable animations in SETTINGS. SCORES: %s : %.1f ; %s : %.1f\n\n\n", p1, score1, p2, score2);
		if(o_turn == false){
			printf("%s, choose a column to place your piece (X) : ", p1);
			fgets(input, 1000, stdin);
			curCol = strtol(input, &pEnd, 10);
			curCol--;
			if(insert(board,numCols,numRows, curCol, 'X', setting) == 0){ 
				bad_input = true;
				continue;
			}
			clearFields();
			printBoard(board, numCols, numRows);
			if(checkBoard(board,numCols,numRows)){
				printf("Player one wins!\n");
				score1++;
				break;
			}
			if(checkTies(board, numCols, numRows)){
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
		if(insert(board,numCols,numRows, curCol, 'O', setting) == 0){
			o_turn = true;
			bad_input = true;
			continue;
		}
		o_turn = false;
		bad_input = false;
		clearFields();
		printBoard(board, numCols, numRows);
		if(checkBoard(board,numCols,numRows)){
			printf("Player two wins!\n");
			score2++;
			break;
		}
		if(checkTies(board, numCols, numRows)){
			printf("It's a tie!\n");
			score1 += 0.5;
			score2 += 0.5;
			break;
		}
	}
	freeBoard(board, numRows+3);
	already_played = true;
	printf("Press any key to exit, or 1 to play again.");
	char buffer;
	scanf("%c", &buffer);
	o_turn = false;
	if(buffer == '1'){
		initMultiPlayer(score1, score2, numRows, numCols, p1, p2, true, setting);
	}
}

int dispMenu(bool s){
	bool animation_on = s;
	clearFields();
	printf("************WELCOME TO CONNECT FOUR IN A ROW************\n\n");
	printf("                 Select an Option Below:                \n");
	printf("1 - Single Player VS Computer                           \n");
	printf("2 - Multiplayer                                         \n");
	printf("3 - Settings                                            \n");
	printf("4 - How to Play / Tutorial                              \n");
	printf("5 - Quit                                                \n");
	if(animation_on)printf("\nANIMATIONS ARE ON. Select an option above: \n");
	else{
		printf("\nANIMATIONS ARE OFF. Select an option above: \n");
	}
	printf("\e[?25h");
	char *p1 = (char*)malloc(50*sizeof(char*));
	char *p2 = (char*)malloc(50*sizeof(char*));
	char *pEnd;
	char input[1000];
	fgets(input, 1000, stdin);
	long int option = strtol(input, &pEnd, 10);
	switch(option){
		case 1:
			initSinglePlayer(0, 0, 0, 0, 1, p1, false, animation_on);
			break;
		case 2:
			initMultiPlayer(0, 0, 0, 0, p1, p2, false, animation_on);
			printf("\e[?25l");
			break;
		case 3:
			animation_on = initSettings(animation_on);
			free(p1);
			free(p2);
			if(animation_on) return 1;
			if(!animation_on) return 2;
		case 4:
			clearFields();
			printf("Welcome to connect 4! Two players take turns placing pieces on an arbitrary-sized board until they have connected four of their pieces in a row.\n");
			printf("Let's see some examples.\n\n");
			printf("Press any button + enter to continue.");
			char buf;
			scanf("%c", &buf);
			char **b_tutorial = allocBoard(5,5);
			b_tutorial[4][4] = 'X';
			b_tutorial[4][3] = 'X';
			b_tutorial[3][3] = 'O';
			b_tutorial[2][3] = 'O';
			b_tutorial[3][4] = 'X';
			b_tutorial[4][1] = 'O';
			b_tutorial[3][1] = 'O';
			b_tutorial[4][0] = 'X';
			printBoard(b_tutorial, 5, 5);
			printf("Here is an example of a board with pieces already set on the board. X now makes a move: (press any button + enter to continue)\n");
			getchar();
			scanf("%c", &buf);
			insert(b_tutorial, 5, 5, 4, 'X', true);
			printBoard(b_tutorial, 5, 5);
			printf("X makes a powerful move that allows him to win if you don't do something about it! See if you can find the saving move for O.\n");
			printf("Choose the number of the column to place your piece: ");
			getchar();
			char input[1000];
			long int curCol = 0;
			char *pEnd;
			while(1){
				fgets(input, 1000, stdin);
				curCol = strtol(input, &pEnd, 10);
				if(curCol == 1 || curCol == 2 || curCol == 3 || curCol == 4){
					printf("While this is a legal move, notice that after this move, X can insert a piece in the fourth column and win!\n");
					printf("Choose the number of the column to place your piece: ");
				}
				else if(curCol == 5){
					insert(b_tutorial, 5, 5, 4, 'O', true);
					printBoard(b_tutorial, 5, 5);
					printf("Yes! Great move! You have successfully stopped X's attack (press any button + enter to continue)");
					scanf("%c", &buf);
					break;
				}
				else{
					printf("Bro, that's not even a legal move! Try again.\n");
					printf("Choose the number of the column to place your piece: ");
				}
			}
			insert(b_tutorial, 5, 5, 2, 'X', true);
			printBoard(b_tutorial, 5, 5);
			printf("\nX made a mistake! Punish it with your next move!\n");
			printf("Choose the number of the column to place your piece: ");
			getchar();
			while(1){
				fgets(input, 1000, stdin);
				curCol = strtol(input, &pEnd, 10);
				if(curCol == 1 || curCol == 2 || curCol == 4 || curCol == 5){
					printf("While this move is legal, there is an even better one.. Try finding where O can win!\n");
					printf("Choose the number of the column to place your piece: ");
				}
				else if(curCol == 3){
					insert(b_tutorial, 5, 5, 2, 'O', true);
					printBoard(b_tutorial, 5, 5);
					printf("Yes! Great move! You took advantage of Xs mistake!\n");
					printf("Press any button + enter to continue: ");
					scanf("%c", &buf);
					break;
				}
				else{
					printf("Bro, that's not even a legal move! Try again.\n");
					printf("Choose the number of the column to place your piece: ");
				}
			}
			printf("I think you're now ready to take on the computer in single player or face your friends in multiplayer.\n");
			getchar();
			printf("Press any button + enter to continue: ");
			scanf("%c", &buf);
			freeBoard(b_tutorial, 8);
			break;
		case 5:
			printf("Hope to see you soon!\n");
			free(p1);
			free(p2);
			return -1;
		default:
			break;
	}
	free(p1);
	free(p2);
	return 0;
}
