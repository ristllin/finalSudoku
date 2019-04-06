/*
 * Main.c
 *
 *  Created on: Mar 9, 2019
 *      Author: Roy Darnell and Shahar Eshed
 */

#include <stdio.h>
#include <stdlib.h>
/* Global Variables: */

int* board; /* int[N][N] playing board*/
int* guess_board; /* int[N][N] used temporarily for guesses and hints*/
int m; /*board's width*/
int n; /* board's length*/
int mark_errors;
int* ctrl_z; /*list of player moves, starts and ends with "-2" cells, "-1" states reset board*/
int* ctrl_z_current; /*pointer to current place in ctrl_z list*/
int state; /* 0 => init, 1 => solve, 2 => solve */

int main(int argc, char* argv[]){
	int user_command[4]; /*[command,x,y,z]*/
	while(1){
		userInput(board,m,n,state, user_command);
		execute(board, user_command, m, n, mark_errors,ctrl_z,state,ctrl_z_current);
		printBoard(board);
		/*last step? + validation*/
	}


	return 0;
}
