/*
 * Main.c
 *
 *  Created on: Mar 9, 2019
 *      Author: Roy Darnell and Shahar Eshed
 */
/*Libraries: */
#include <stdio.h>
#include <stdlib.h>

/* Global Variables: */
int* board; /* pseudo triple array -> single array, n*m*2 = rows * columns * [value,fixed- 1\0] playing board*/
int* guess_board; /*  single array, n*m*2 = rows * columns * [value,fixed- 1\0] playing board - used temporarily for guesses and hints*/
int* m; /*board's width*/
int* n; /* board's length*/
int* mark_errors; /*1 show errors (default), 0 don't show*/
struct Node* ctrl_z = NULL; /*list of player moves, starts and ends with "-2" cells, "-1" states reset board*/
struct Node* ctrl_z_current = NULL; /*pointer to current place in ctrl_z list*/
int* state; /* 0 => init, 1 => solve, 2 => edit */

int main(int argc, char* argv[]){
	toInit(board,guess_board,m,n,mark_errors,ctrl_z,ctrl_z_current,state);
	int user_command[4]; /*[command,x,y,z]*/
	while(1){
		userInput(board,m,n,state, user_command);
		execute(board, user_command, m, n, mark_errors,ctrl_z,state,ctrl_z_current);
		if (is_finished(n,m,board)){
			printf(WINNING);
			toInit();
		}else{
			printBoard(board);
		}
	}


	return 0;
}
