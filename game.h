//header file for game.c
#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "structs.h"
char **allocBoard(int, int);
int **allocGraph(int, int);
void printBoard(char **, int, int);
void clearFields();
void freeBoard(char **, int);
void freeGraph(int **, int);
int insert(char **, int, int, int, char, bool);
bool checkBoard(char **, int, int);
bool checkBoardX(char **, int, int);	
bool checkBoardO(char **, int, int);
bool checkTies(char**, int, int);
int **findOpenMoves(char **, int**, int, int);
int miniMax(char **, int, int, int, int, bool);
move findBestMove(char **, int, int, int);

#endif
