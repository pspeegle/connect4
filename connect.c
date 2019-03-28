#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ncurses.h>

char **allocBoard(int cols, int rows){
	char **board = (char **)malloc((rows+3)*sizeof(char *));
	for(int i = 0; i < rows+3; i++){
		board[i] = (char *)malloc((cols+3)*sizeof(char));
	}
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			board[i][j] = ' ';
		}
	}
	return board;
}

int **allocGraph(int cols, int rows){
	int **graph = (int **)malloc(rows*sizeof(int *));
	for(int i = 0; i < rows; i++){
		graph[i] = (int *)malloc(cols*sizeof(int *));
	}
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			graph[i][j] = 0;
		}
	}
	return graph;
}

void printBoard(char **board, int cols, int rows){
	printf(" ");
	for(int k = 0; k < cols; k++){
		printf("----");
	}
	printf("-\n");
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			printf(" | %c", board[i][j]);
		}
		printf(" |\n ");
		for(int k = 0; k < cols; k++){
			printf("----");
		}
		printf("-");
	printf("\n");
	}
}

void clearFields(){
	system("clear");
}

void freeBoard(char **board, int rows){
	for(int i = 0; i < rows; i++){
		free(board[i]);
	}
	free(board);
}

void freeGraph(int **graph, int rows){
	for(int i = 0; i < rows; i++){
		free(graph[i]);
	}
	free(graph);
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
			printf("You chose single player.\n");
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

void insert(char **board, int cols, int rows, char c){
	int curCol = 0;
	while(1){
		char input;
		scanf("%c", &input);
		if((input == 'd' || input == 'D') && curCol < cols - 1) curCol++;
		if((input == 'a' || input == 'A') && curCol > 0) curCol--;
		if(input == 'p' || input == 'P'){
			int i = rows-1;
			while(i >= 0 && (board[i][curCol] == 'X'|| board[i][curCol] == 'O')){
				i--;
			}
			if(i == -1) continue;
			else{
				board[i][curCol] = c;
				break;
			}
		}
	}
}

bool checkBoard(char **board, int cols, int rows){
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			if(board[i][j] == 'X' && board[i][j] == 'O') continue;
			if(board[i][j] == 'X' && board[i][j+1] == 'X' && board[i][j+2] == 'X' && board[i][j+3] == 'X') return true;
			if(board[i][j] == 'O' && board[i][j+1] == 'O' && board[i][j+2] == 'O' && board[i][j+3] == 'O') return true;
			if(board[i][j] == 'X' && board[i+1][j] == 'X' && board[i+2][j] == 'X' && board[i+3][j] == 'X') return true;
			if(board[i][j] == 'O' && board[i+1][j] == 'O' && board[i+2][j] == 'O' && board[i+3][j] == 'O') return true;
			if(board[i][j] == 'X' && board[i+1][j+1] == 'X' && board[i+2][j+2] == 'X' && board[i+3][j+3] == 'X') return true;
			if(board[i][j] == 'O' && board[i+1][j+1] == 'O' && board[i+2][j+2] == 'O' && board[i+3][j+3] == 'O') return true;
			if(board[i+3][j] == 'X' && board[i+2][j+1] == 'X' && board[i+1][j+2] == 'X' && board[i][j+3] == 'X') return true;
			if(board[i+3][j] == 'O' && board[i+2][j+1] == 'O' && board[i+1][j+2] == 'O' && board[i][j+3] == 'O') return true;
		}
	}
	return false;
}

bool checkBoardX(char **board, int cols, int rows){
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			if(board[i][j] == 'X' && board[i][j] == 'O') continue;
			if(board[i][j] == 'X' && board[i][j+1] == 'X' && board[i][j+2] == 'X' && board[i][j+3] == 'X') return true;
			if(board[i][j] == 'X' && board[i+1][j] == 'X' && board[i+2][j] == 'X' && board[i+3][j] == 'X') return true;
			if(board[i][j] == 'X' && board[i+1][j+1] == 'X' && board[i+2][j+2] == 'X' && board[i+3][j+3] == 'X') return true;
			if(board[i+3][j] == 'X' && board[i+2][j+1] == 'X' && board[i+1][j+2] == 'X' && board[i][j+3] == 'X') return true;
		}
	}
	return false;
}	

bool checkBoardO(char **board, int cols, int rows){
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			if(board[i][j] == 'X' && board[i][j] == 'O') continue;
			if(board[i][j] == 'O' && board[i][j+1] == 'O' && board[i][j+2] == 'O' && board[i][j+3] == 'O') return true;
			if(board[i][j] == 'O' && board[i+1][j] == 'O' && board[i+2][j] == 'O' && board[i+3][j] == 'O') return true;
			if(board[i][j] == 'O' && board[i+1][j+1] == 'O' && board[i+2][j+2] == 'O' && board[i+3][j+3] == 'O') return true;
			if(board[i+3][j] == 'O' && board[i+2][j+1] == 'O' && board[i+1][j+2] == 'O' && board[i][j+3] == 'O') return true;
		}
	}
	return false;
}	


int **findOpenMoves(char **board, int **graph, int cols, int rows){
	for(int j = 0; j < cols; j++){
		int i = rows-1;
		while(i >= 0 && (board[i][j] == 'X'|| board[i][j] == 'O')){
			graph[i][j] = 0;
			i--;
		}
		if(i == -1) continue;
		else{
			graph[i][j] = 1;
		}
	}
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			printf("%d ", graph[i][j]);
		}
		printf("\n");
	}
	return graph;
}
void findBestMove(char **board, int **g, int cols, int rows){
	g = findOpenMoves(board, g, cols, rows);
		
}

int main(void){
	dispMenu();
	int numRows = 0;
	int numCols = 0;
	printf("How many rows would you like in the game?\n");
	while(1){
		if(!scanf("%d", &numRows)){
			printf("You didn't even enter in a number!\n");
			printf("Try again.");
		}
		if(numRows < 4){
			printf("Please choose a number greater than 4.\n");
			continue;
		}
		break;
	}
	printf("How many columns would you like in the game?\n");
	while(1){
		if(!scanf("%d", &numCols)){
			printf("You didn't even enter in a number!\n");
			printf("Try again.");
			scanf("%d", &numRows);
		}
		if(numCols < 4){
			printf("Please choose a number greater than 4.\n");
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
		insert(board,numCols,numRows,'O');
		clearFields();
		printBoard(board, numCols, numRows);
		graph = findOpenMoves(board, graph, numCols, numRows);
		if(checkBoard(board,numCols,numRows)){
			printf("Player two wins!\n");
			break;
		}
	}
	freeBoard(board, numRows);
	freeGraph(graph, numRows);
}
