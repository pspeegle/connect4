#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "game.h"
#define max(x, y) (((x) > (y)) ? (x) : (y))
#define min(x, y) (((x) < (y)) ? (x) : (y))
//allocates enough space for the board
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
	for(int j = 0; j < cols+3; j++){
		board[rows][j] = '+';
	}
	return board;
}
//prints the board and formats it
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
//clears the screen
void clearFields(){
	system("clear");
}
//avoiding memory leaks
void freeBoard(char **board, int rows){
	for(int i = 0; i < rows; i++){
		free(board[i]);
	}
	free(board);
}
//inserts at a given position
int insert(char **board, int cols, int rows, int curCol, char c, bool animations_on){
	if(curCol >= 0 && curCol < cols){
		int i = rows-1;
		while(i >= 0 && (board[i][curCol] == 'X'|| board[i][curCol] == 'O')){
			i--;
		}
		//if i goes through the entire board without finding an empty slot
		if(i == -1){
			printf("This column is full!\n");
			return 0;
		}
		else{
			int j = 0;
			printf("\e[?25l");
			if(animations_on){
				while(j <= i){
					if(j > 0) board[j-1][curCol] = ' ';
					board[j][curCol] = c;
					clearFields();
					printBoard(board, cols, rows);
					clearFields();
					j++;
				}
				printf("\e[?25h");
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
//probably could have made this more concise with the below functions but wanted to reduce coupling
bool checkBoard(char **board, int cols, int rows){
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
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
//looks at a win for X
bool checkBoardX(char **board, int cols, int rows){
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			if(board[i][j] == 'X' && board[i][j+1] == 'X' && board[i][j+2] == 'X' && board[i][j+3] == 'X') return true;
			if(board[i][j] == 'X' && board[i+1][j] == 'X' && board[i+2][j] == 'X' && board[i+3][j] == 'X') return true;
			if(board[i][j] == 'X' && board[i+1][j+1] == 'X' && board[i+2][j+2] == 'X' && board[i+3][j+3] == 'X') return true;
			if(board[i+3][j] == 'X' && board[i+2][j+1] == 'X' && board[i+1][j+2] == 'X' && board[i][j+3] == 'X') return true;
		}
	}
	return false;
}	
//looks at a win for O
bool checkBoardO(char **board, int cols, int rows){
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			if(board[i][j] == 'O' && board[i][j+1] == 'O' && board[i][j+2] == 'O' && board[i][j+3] == 'O') return true;
			if(board[i][j] == 'O' && board[i+1][j] == 'O' && board[i+2][j] == 'O' && board[i+3][j] == 'O') return true;
			if(board[i][j] == 'O' && board[i+1][j+1] == 'O' && board[i+2][j+2] == 'O' && board[i+3][j+3] == 'O') return true;
			if(board[i+3][j] == 'O' && board[i+2][j+1] == 'O' && board[i+1][j+2] == 'O' && board[i][j+3] == 'O') return true;
		}
	}
	return false;
}
//checks for ties
bool checkTies(char **board, int cols, int rows){
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			if(board[i][j] == ' ') return false;
		}
	}
	return true;
}
//function just checks the endpoint and assigns a score
int scorePosition(char **board, int cols, int rows){
	if(checkBoardO(board, cols, rows)) return 1000;
	if(checkBoardX(board, cols, rows)) return -1000;
	return 0;
}
//minimax - a recursive algorithm assigning a score to a move
int miniMax(char **board, int depth, int difficulty, int cols, int rows, bool isMove){
	//limit controls how much depth the algorithm goes into - higher difficulties imply higher limits
	int limit;
	if(difficulty == 1) limit = 2;
	if(difficulty == 2) limit = 4;
	if(difficulty == 3){
		if(cols + rows == 8) limit = 8;
		else if(cols + rows < 11) limit = 6;
		else{
			limit = 4;
		}
	}
	int score = scorePosition(board, cols, rows);
	//the more in depth a win is, the worse it is scored
	if(score == 1000){
		return score - depth;
	}
	if(score == -1000){
		return score + depth;
	}
	if(checkTies(board, cols, rows)){
		return 0;
	}
	//if it is the computer's move, find the maximum scoring move
	if(isMove){
		int best = -1000000;
		for(int i = rows-1; i >= 0; i--){
			for(int j = cols-1; j >= 0; j--){
				if(board[i][j] == ' ' && (board[i+1][j] == 'X' || board[i+1][j] == 'O' || board[i+1][j] == '+') && depth < limit){
					board[i][j] = 'O';
					//max is defined in the heading, same with min
					best = max(best, miniMax(board, depth+1, difficulty, cols, rows, !isMove));
					board[i][j] = ' ';	
				}
			}
		}
		return best;
	}
	//if it is the human's move, find the move that is best for the human
	else{
		int best = 1000000;
		for(int i = rows-1; i >= 0; i--){
			for(int j = cols-1; j >=0; j--){
				if(board[i][j] == ' ' && (board[i+1][j] == 'X' || board[i+1][j] == 'O' || board[i+1][j] == '+') && depth < limit){
					board[i][j] = 'X';
					best = min(best, miniMax(board, depth+1, difficulty, cols, rows, !isMove));
					board[i][j] = ' ';
				}
			}
		}
		return best;
	}
}
//uses minimax to find the best move
move findBestMove(char **board, int cols, int rows, int difficulty){
	int bestVal = -1000000;
	move bestMove;
	bestMove.row = -1;
	bestMove.column = -1;
	//optimization: if there is a win in one move, computer looks for it first, except if the difficulty is on trivially easy
	if(difficulty > 1){
		for(int i = 0; i < rows; i++){
			for(int j = 0; j < cols; j++){
				if(board[i][j] == ' ' && (board[i+1][j] == 'X' || board[i+1][j] == 'O' || board[i+1][j] == '+')){
					board[i][j] = 'O';
					if(checkBoardO(board, cols, rows)){
						bestMove.row = i;
						bestMove.column = j;
						board[i][j] = ' ';
						return bestMove;
					}
					board[i][j] = ' ';
				}
			}
		}
		for(int i = 0; i < rows; i++){
			for(int j = 0; j < cols; j++){
				if(board[i][j] == ' ' && (board[i+1][j] == 'X' || board[i+1][j] == 'O' || board[i+1][j] == '+')){
					board[i][j] = 'X';
					if(checkBoardX(board, cols, rows)){
						bestMove.row = i;
						bestMove.column = j;
						board[i][j] = ' ';
						return bestMove;
					}
					board[i][j] = ' ';
				}
			}
		}
	}
	//if there isn't a win in one move, use minimax to find the best move
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			if(board[i][j] == ' ' && (board[i+1][j] == 'X' || board[i+1][j] == 'O' || board[i+1][j] == '+')){
				board[i][j] = 'O';
				int moveVal = miniMax(board, 0, difficulty, cols, rows, false);
				board[i][j] = ' ';
				if(moveVal > bestVal){
					bestMove.row = i;
					bestMove.column = j;
					bestVal = moveVal;
				}
			}
		}
	}
	return bestMove;
}
