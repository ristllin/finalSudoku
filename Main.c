/*
 * Main.c
 *
 *  Created on: Mar 9, 2019
 *      Author: Roy Darnell and Shahar Eshed
 */
/*Libraries: */
#include <stdio.h>
#include <stdlib.h>
/*Modules*/
#include "Constants.h"
#include "UserInput.h"
#include "Commands.h"
#include "IOCommands.h"

/* Global Variables: */
int* board; /* pseudo triple array -> single array, n*m*2 = rows * columns * [value,fixed- 1\0] playing board*/
int* guess_board; /*  single array, n*m*2 = rows * columns * [value,fixed- 1\0] playing board - used temporarily for guesses and hints*/
int* m; /*board's width*/
int* n; /* board's length*/
int* mark_errors; /*1 show errors (default), 0 don't show*/
struct Node* ctrl_z = NULL; /*list of player moves, starts and ends with "-2" cells, "-1" states reset board*/
struct Node* ctrl_z_current = NULL; /*pointer to current place in ctrl_z list*/
int* state; /* 0 => init, 1 => solve, 2 => edit */
char* user_path;
float* user_threshold;

int main(int argc, char* argv[]){
	setvbuf(stdout, NULL, _IONBF, 0); /*debug mode*/
	toInit(board,guess_board,m,n,mark_errors,ctrl_z,ctrl_z_current,state);
	int user_command[4]; /*[command,x,y,z]*/
	while(1){
		userInput(board,m,n,state, user_command, user_path, user_threshold);
		execute(board, user_command, user_path, m, n, mark_errors, ctrl_z, state, ctrl_z_current, guess_board);
		if (isFinished(n,m,board)){
			printf("%s\n",WINNING);
			toInit(board, guess_board, m, n, mark_errors, ctrl_z, ctrl_z_current, state);
		}else{
			printBoard(board);
		}
	}


	return 0;
}
