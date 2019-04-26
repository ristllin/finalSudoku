/*
 * Commands.c
 *
 *  Created on: Mar 16, 2019
 *      Author: Roy Darnell and Shahar Eshed
 */
#include<stdio.h>
#include<stdlib.h>
#include "List.h"
#include "AuxFunctions.h"
#include "Constants.h"

void execute(int* board, int* user_command, char* user_path, int* m, int* n, int* mark_errors,int* state, struct Node* ctrl_z, struct Node* ctrl_z_current, int* guess_board){
	/*function description: activate correct command according to user command and pass relevant parameters (router).
	 * args: all variables that require memory release
	 * return: void
	 */
	int command = user_command[0];
	int x = user_command[1]; int y = user_command[2]; int z = user_command[3];
	switch(command){
		case 0:
			exitSudoku(board, user_command, m, n,  mark_errors, state, ctrl_z, ctrl_z_current, guess_board);
			break;
		case 1:
			set(n,m,x,y,z,board,ctrl_z,ctrl_z_current);
			break;
		case 2:
			autoFill(n,m,board,state);
			break;
		case 3:
			markErrors(x,mark_errors);
			break;
		case 4:
			numSolutions(n,m,board);
			break;
		case 5:
			generate(x,y,board);
			break;
		case 6:
			validate(board,state);
			break;
		case 7:
			guess(x,state,board);
			break;
		case 8:
			reset(n,m,board,ctrl_z,ctrl_z_current);
			break;
		case 9:
			guess_hint(x,state,board);
			break;
		case 10:
			hint(x,y,board,state);
			break;
		case 11:
			undo(n,m,board ,ctrl_z, ctrl_z_current);
			break;
		case 12:
			redo(n,m,board,ctrl_z, ctrl_z_current);
			break;
		case 13:
			save(x,board,state);
			break;
		case 14: /*There is no user init command, for debug purposes*/
			toInit(board,guess_board,m,n,mark_errors,ctrl_z, ctrl_z_current);
			break;
		case 15:
			toSolve(n,m,x,state,board,guess_board);
			break;
		case 16:
			toEdit(n,m,x,state,board);
			break;
		default:
			printf("%s",INVALIDCOMMANDERROR);
			break;
	}
}

void exitSudoku(int* board, int* user_command, int* m, int* n, int* mark_errors,int* state, struct Node* ctrl_z, struct Node* ctrl_z_current, int* guess_board){
	/*function description: Terminates the program.
	 * args: all variables that require memory release
	 * return: void
	 */
	/*free all variables that require memory release!*/
	free(board); free(user_command); free(m); free(n);
	free(mark_errors); free(state); free(ctrl_z); free(ctrl_z_current);
	exit(0);
}

int set(int n, int m, int x, int y, int z, int* board, struct Node* ctrl_z, struct Node* ctrl_z_current){
	/*function description: sets the value of cell <x,y> to z, user may empty a cell
	 * state: Edit, Solve (fixed cells are not updated)
	 * args: cell -> <x,y>
	 * return: 0 if failed, 1 if successful
	 */
	/*set*/
	/*check if user entered erroneous value*/
	/*update ctrl_z, delete the further steps after current one*/
	int location; const N = n*m; struct Node* temp;
	if (x > N || x < 1){printf("%s\n",FIRSTPARAMETERERROR); return 0;}
	if (y > N || y < 1){printf("%s\n",SECONDPARAMETERERROR); return 0;}
	if (z > N || z < 1){printf("%s\n",THIRDPARAMETERERROR); return 0;}
	location = (x+(y*N))*2;
	board[location] = z;
	temp = ctrl_z_current->next;
	RemoveFollowingNodes(temp); /*forget next moves if existing*/
	InsertAtTail(board[location],x,y,ctrl_z_current); /*add former data*/
	ctrl_z_current = ctrl_z_current->next; /*advance current ctrl-z to new node*/
	return 1;
}

void autoFill(int n, int m, int* board, int* state){
	/*function description: Automatically fill "obvious" values � cells which contain a single legal value.
	 * state: solve
	 * args: board - changes current board
	 * return:
	 */
	int* temp_board,legal_options; int x,y,location;
	const N = n*m;
	temp_board = (int*)calloc(N*N*2,sizeof(int));
	legal_options = (int*)calloc(N,sizeof(int));
	copyBoard(board,temp_board,N);
	for (x=0;x<N;x++){
		for (y=0;y<N;y++){
			location = (x+y*N)*2;
			if (temp_board[location] == 0){ /*if cell is empty*/
				if (optionsForLocation(n,m,x,y,temp_board,legal_options) == 1){ /*"obvious" solution for cell*/
					if (singleOption(legal_options,N) != 0){
						board[location] = singleOption(legal_options,N)+1; /*returns index of cell, +1 to fix*/
					}
				}
			}
		}
	}
	//if cell has 1 option, change origin cell to
	free(legal_options);
	free(temp_board);
}

void markErrors(int x, int* mark_errors){
	/*function description: set the mark_errors flag to x value
	 * state: Solve
	 * args: x
	 * return: void
	 */
	if (x > 1 || x < 0){printf("%s\n",FIRSTPARAMETERERROR);}
	else {
		*mark_errors = x;
	}
}

void numSolutions(int n, int m, int* board){
	/*function description: Print the number of solutions for the current board, using Exhaustive backtracking algorithem
	 * state: Edit, Solve
	 * args:
	 * return:
	 */
	int rslt = 0;
	rslt = EBA(n,m,board);
	printf("Number of solutions found for current bard is:%d\n",rslt);
}

void generate(int x, int y, int* board){
	/* function description: Generates a puzzle by randomly filling X empty cells with legal values,
running ILP to solve the board, and then clearing all but Y random cells.
	 * state: Edit
	 * args: x --> number of cells to fill, y --> number of cells to clear
	 * return: void
	 */
	/* check number of empty cells */
	/* fill x randomly selected cells with legal values */
	/* if there is no legal value --> reset, and try up to 1000 rounds */
	/* choose y sells and clear it */
	/* if there is no legal value --> reset, and try up to 1000 rounds */

}

void validate(int* board, int* state){
	/*function description:The command prints whether the board is found to be solvable, or not using ILP
	 * states: Solve, Edit
	 * args:
	 * return:void
	 */
	/*check state*/
	/*validate using ILP*/
	/*print*/

}

void guess(float x, int* state, int* board){
	/*function description: fills all cell values with a score of X or greater usong LP. If several
   * values hold for the same cell, randomly choose one according to the score
	 * state: Solve
	 * args: x --> lower boundary of score
	 * return: void
	 */

}

void reset(int n, int m, int* board, struct Node* ctrl_z, struct Node* ctrl_z_current){
	/* function description: Undo all moves, reverting the board to its original loaded state
	 * state: Solve, Edit
	 * return: void
	 */
	while (ctrl_z_current != ctrl_z){
		undo(n,m,board ,ctrl_z, ctrl_z_current);
	}
}

void guess_hint(int x, int* state, int* board){
	/* function description: Show a guess to the user for a single cell X,Y using LP and print suggested value
	 * state: Solve
	 * args: x --> lower boundary of score
	 * return: void
	 */

}

void hint(int x, int y, int* board, int* state){
	/*function description: Give a hint to the user by showing the solution of a single cell X,Y
	 * and print the value of cell <X,Y> found by the ILP solution.
	 * state: solve
	 * args: <x,y> cell location
	 * return:
	 */

}

int undo(int n, int m, int* board, struct Node* ctrl_z, struct Node* ctrl_z_current){
	/*function description: Undo previous moves done by the user
	 * states: Edit, Solve
	 * args:
	 * return:
	 */
	/* set to board to previous state */
	/* set pointer in the list */
	/* no moves to undo --> error */
	/* print change */
	int location = 0; const N = n*m;
	if (ctrl_z_current->prev == NULL){printf("%s\n",NOMOREMOVES);return 0;}
	ctrl_z_current = ctrl_z_current->prev;
	location = (ctrl_z_current->x+(ctrl_z_current->y*N))*2;
	board[location] = ctrl_z_current->data;
}

int redo(int n, int m, int* board, struct Node* ctrl_z, struct Node* ctrl_z_current){
	/*function description: Redo a move previously undone by the user.
	 * states: Edit, Solve
	 * args:
	 * return: 0 if failed, 1 if successful
	 */
	/* set to board to next state */
	/* set pointer in the list */
	/* no moves to redo --> error */
	/* print change */
	int location = 0; const N = n*m;
	if (ctrl_z_current->next == NULL){printf("%s\n",NOMOREMOVES);return 0;}
	ctrl_z_current = ctrl_z_current->next;
	location = (ctrl_z_current->x+(ctrl_z_current->y*N))*2;
	board[location] = ctrl_z_current->data;
}

void save(int n, int m, char* path, int* board, int* state){
	/*function description: Saves the current game board to the specified file
	 * states: Edit, Solve
	 * args: X --> file's path
	 * return: void
	 */
	int i = 0; const N = n*m; int* temp_board;
	temp_board = calloc(N*N*2,sizeof(int));
	copyBoard(board,temp_board,N);
	if (state == 1){ /* edit - mark cells containing values as fixed */
		for (i=0;i<N*N;i++){ /*each existing value in board, fix in temp_board*/
			if (temp_board[i*2] != 0){
				temp_board[i*2+1] = 1;
			}
		}
		if (EBA(n,m,board)<1){/* edit - do not save erroneous files and boards without solution*/
			printf("%s/n",ILLEGALSAVEERROR);
			free(temp_board);
			return;
		}
	}
	if (writeBoardToFile(n,m,temp_board,path) == 1){printf("%s\n",SAVINGFAILED);}
	free(temp_board);
}

void toInit(int* board, int* guess_board,int* m, int* n,int* mark_errors, struct Node* ctrl_z, struct Node* ctrl_z_current,int* state){
	/*function description: change state to 'init' mode, sets all global parameters to default.
	 * args: all global parameters
	 * return: void
	 */
	/*n,m to 9, state to 0, boards to empty*/
	free(board);
	free(guess_board);
	n = 9; m = 9; state = 0; mark_errors = 1;
	const N = (int)n*(int)m;
	board = calloc(N*N*2,sizeof(int));
	guess_board = calloc(N*N*2,sizeof(int));
	ctrl_z_current = ctrl_z;
	RemoveFollowingNodes(ctrl_z);
}

void toSolve(int* n, int* m, char* path, int* state, int* board, int* guess_board){
	/*function description: change state to 'Solve' mode, and set board from file
	 * args: x --> file path
	 * return: void
	 */
	int* temp_board, tempn, tempm; const N = (*n)*(*m);
	state = 1;
	if (readBoardFromFile( tempn, tempm, temp_board, path) == 1){printf("%s/n",READINGFAILED);}
	else{ /*reading successful*/
		free(board);
		free(guess_board);
		board = temp_board;
		n = tempn;
		m = tempm;
		guess_board = calloc(N*N*2,sizeof(int));
	}
}

void toEdit(int* n, int* m, char* path, int* state, int* board){
	/*function description: change state to 'Edit' mode, and set board from file or to empty board if the file path is empty
	 * args: x --> file path
	 * return: void
	 */
	int* temp_board, tempn, tempm; const N = (*n)*(*m);
	state = 1;
	if (readBoardFromFile( tempn, tempm, temp_board, path) == 1){printf("%s/n",READINGFAILED);}
	else{
		free(board);
		board = temp_board;
		n = tempn;
		m = tempm;
	}
}

