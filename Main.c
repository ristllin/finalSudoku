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
#include "List.h"
#include "AuxFunctions.h"

/* Global Variables: */
int** board; /* pseudo triple array -> single array, n*m*2 = rows * columns * [value,fixed- 1\0] playing board*/
int* temp;
int* m; /*board's width*/
int* n; /* board's length*/
int* mark_errors; /*1 show errors (default), 0 don't show*/
int* state; /* 0 => init, 1 => solve, 2 => edit */
float user_threshold[1];

int main(int argc, char* argv[]){
	struct Node* ctrl_z; /*list of player moves, starts and ends with "-2" cells, "-1" states reset board*/
	struct Node** ctrl_z_current; /*ctrl_z; pointer to current place in ctrl_z list */
	ctrl_z = GetNewNode(-2,0,0);
	ctrl_z_current = &ctrl_z;
	char user_path[MAXBUFFERSIZE];
	int user_command[4]; /*[command,x,y,z]*/
	int did_pass=1;
	if(PRODUCTION==0){setvbuf(stdout, NULL, _IONBF, 0);} /*debug mode*/
	temp = (int*)calloc(9*9*2,sizeof(int));
	board = &temp;
	/*Program Initialization*/
	printf("%s\n",OPENNING);
	toInit(board,m,n,mark_errors,ctrl_z,ctrl_z_current,state);
	/*Game Main Loop*/
	while(1){
		userInput(board,m,n,state, user_command, user_path, user_threshold);
		did_pass = execute(board, user_command, user_path, m, n, mark_errors, state, ctrl_z, ctrl_z_current, user_threshold[0]);
		printf("here 1\n");
		if (did_pass){
			if (isFinished(*n,*m,*board) == 1 && *state == 1){
				printBoard(*board,*n,*m,state,*mark_errors);
				printf("%s\n",WINNING);
				toInit(board,m,n,mark_errors,ctrl_z,ctrl_z_current,state);
			}else{
				printBoard(*board,*n,*m,state,*mark_errors);
			}
		} else if (*state == 1){
			printBoard(*board,*n,*m,state,*mark_errors);
		}
	}


	return 0;
}
