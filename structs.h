#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

typedef struct Move{
	int row;
	int column;
} move;

typedef struct Settings{
	bool animation_on;
	bool depth_on;
} settings;

#endif

