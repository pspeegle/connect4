//header file for game.c
#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

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
bool checkTies(int**, int, int);
int **findOpenMoves(char **, int **, int, int);
void findBestMove(char **, int **, int, int);

#endif
