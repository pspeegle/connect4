#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "game.h"

char **allocBoard(int cols, int rows){
	char **board = (char **)malloc((rows+3)*sizeof(char *));
	for(int i = 0; i < rows+3; i++){
		board[i] = (char *)malloc((cols+3)*sizeof(char));
	}
	for(int i = 0; i < rows+3; i++){
		for(int j = 0; j < cols+3; j++){
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
	printf("\n");
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
	printf(" ");
	for(int i = 1; i < cols +1; i++){
		if(i < 10) printf("| %d ", i);
		else if(i >= 10 && i < 100){
			printf("|%d ", i);
		}
		else{
			printf("|%d", i);
		}
	}
	printf("|\n ");
	for(int k = 0; k < cols; k++){
		printf("----");
	}
	printf("-\n");
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

int insert(char **board, int cols, int rows, int curCol, char c, bool animations_on){
	if(curCol >= 0 && curCol < cols){
		int i = rows-1;
		while(i >= 0 && (board[i][curCol] == 'X'|| board[i][curCol] == 'O')){
			i--;
		}
		if(i == -1){
			printf("This column is full!\n");
			return 0;
		}
		else{
			int j = 0;
			if(animations_on){
				while(j <= i){
					if(j > 0) board[j-1][curCol] = ' ';
					board[j][curCol] = c;
					clearFields();
					printBoard(board, cols, rows);
					clearFields();
					j++;
				}
			}
			else{
				board[i][curCol] = c;
			}
			return 1;
		}
	}
	
	else{
		printf("Invalid input!\n");
		return 0;
	}
	return 0;
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

bool checkTies(int **graph, int cols, int rows){
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			if(graph[i][j] == 1) return false;
		}
	}
	return true;
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
	/*
			DEBUG:
	   
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			printf("%d ", graph[i][j]);
		}
		printf("\n");
	}

	*/
	return graph;
}
void findBestMove(char **board, int **g, int cols, int rows){
	g = findOpenMoves(board, g, cols, rows);
		
}
