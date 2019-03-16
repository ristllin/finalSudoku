/*
 * Main.c
 *
 *  Created on: Mar 9, 2019
 *      Author: Roy Darnell and Shahar Eshed
 */

#include <stdio.h>
#include <stdlib.h>
/* Global Variables: */

int* board; /* int[N][N]*/
int m; /*board's width*/
int n; /* board's length*/
int mark_errors;
int* ctrl_z;
int state; /* 0 => init, 1 => solve, 2 => solve */

int main(int argc, char* argv[]){
	int user_command[4];
	while(1){
		userInput(board,m,n,state, user_command);
		execute(board, user_command, m, n, mark_errors,ctrl_z,state);
		printBoard(board);
	}


	return 0;
}
