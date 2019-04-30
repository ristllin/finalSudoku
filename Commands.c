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
#include "Commands.h"
#include "Algorithem.h"

//AuxFunctions

int chooseRandomOption(int* options,int length){
	//length gets the size of options, e.g. {0,1,2} -> length = 3/
	//if no options are available returns -1, otherwise return the value of Sudoko board;
	int i = 0;
	int random_option = -1;
	if (sumArray(options,length) > 0){
		random_option = (rand()%sumArray(options,length))+1;
		for (i=0;i<length;i++){ //go over options//
			if (options[i] == 1){ //count valid option//
				random_option -= 1;
			}
			if (options[i] == 1 && random_option <= 0){ //reached randomly chosen index
				return i+1;
			}
		}
	}
	return -1;
}

// truncate all values of array
void truncateArray(int* array, int length){
	int i;
	for (i=0;i<length;i++){array[i]=0;}
}

//Select shuffeled_list_length random unique numbers out of [0,range_list_length) range
//return 0 if shuffeled_list_length>range_list_length
int selectUniqueRandomValues(int* shuffeled_list, int shuffeled_list_length, int* range_list, int range_list_length){
	int i=0;
	if(shuffeled_list_length>range_list_length){
		return 0;
	}
	for (i = 0; i < range_list_length; i++) {
		range_list[i] = i;
	}
	for (i = 0; i < shuffeled_list_length; i++) {
			    int j = i + rand() % (range_list_length - i);
			    int temp = range_list[i];
			    range_list[i] = range_list[j];
			    range_list[j] = temp;
			    shuffeled_list[i] = range_list[i];
			}
	return 1;
}

//end of AuxFunctions

int execute(int** board, int* user_command, char* user_path, int* m, int* n, int* mark_errors,int* state, struct Node* ctrl_z, struct Node* ctrl_z_current, int* guess_board, float user_threshold){
	/*function description: activate correct command according to user command and pass relevant parameters (router).
	 * args: all variables that require memory release
	 * return: 1 - completed successful, 0 command completed unsuccessfully
	 */
	/*<<<>>>catch errors from functions*/
	int rslt = 1; int command = user_command[0]; int x = user_command[1]; int y = user_command[2]; int z = user_command[3];
//	printf("debug: execute() called\n");
//	printf("With params: board:%d, user_command[0]:%d, user_path:%s, m:%d, n:%d, mark_errors:%d, state: %d.\n",board,user_command[0],user_path,m,n,mark_errors,state);
	switch(command){
		case 0:
			exitSudoku(*board, user_command, m, n,  mark_errors, state, ctrl_z, ctrl_z_current, guess_board);
			break;
		case 1:
			rslt = set((int)*n,(int)*m,x,y,z,*board,ctrl_z,ctrl_z_current);
			return rslt;
			break;
		case 2:
			rslt = autoFill((int)n,(int)m,*board,state);
			return rslt;
			break;
		case 3:
			markErrors(x,mark_errors);
			break;
		case 4:
			rslt = numSolutions(n,m,*board);
			return rslt;
			break;
		case 5:
			rslt = generate(x,y,*board,(int)*n,(int)*m, ctrl_z,ctrl_z_current);
			return rslt;
			break;
		case 6:
			rslt = validate(n,m,*board,state);
			return rslt;
			break;
		case 7:
			rslt = guess((int)*n,(int)*m,user_threshold,*board, ctrl_z,ctrl_z_current);
			return rslt;
			break;
		case 8:
			reset(n,m,*board,ctrl_z,ctrl_z_current);
			break;
		case 9:
			rslt = guess_hint((int)*n,(int)*m,x-1,y-1,*board);
			return rslt;
			break;
		case 10:
			rslt = hint(n,m,x-1,y-1,*board);
			return rslt;
			break;
		case 11:
			undo(n,m,*board ,ctrl_z, ctrl_z_current);
			break;
		case 12:
			redo(n,m,*board,ctrl_z, ctrl_z_current);
			break;
		case 13:
			rslt = save(n,m,x,*board,state);
			return rslt;
			break;
		case 14: /*There is no user init command, for debug purposes*/
			toInit(board,guess_board,m,n,mark_errors,ctrl_z, ctrl_z_current,state);
			break;
		case 15:
//			printf("debug: toSolve called\n");//debug
			rslt = toSolve(n,m,user_path,state,board,guess_board,ctrl_z, ctrl_z_current);
			return rslt;
			break;
		case 16:
			rslt = toEdit(n,m,board,guess_board,mark_errors,ctrl_z, ctrl_z_current,state,user_path);
			return rslt;
			break;
		default:
			printf("%s",INVALIDCOMMANDERROR);
			break;
	}
	return 1;
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
	int location; const int N = n*m; struct Node* temp;
	board = *board;
	printf("debug set() called\n");
	printf("with: n:%d,m:%d,x:%d,y:%d,z:%d,board:%d\n",n,m,x,y,z,board);
	if (x > N || x < 1){printf("%s\n %d",FIRSTPARAMETERERROR,N); return 0;}
	if (y > N || y < 1){printf("%s\n %d",SECONDPARAMETERERROR,N); return 0;}
	if (z > N || z < 1){printf("%s\n %d",THIRDPARAMETERERROR,N); return 0;}
	x = x-1; y = y-1; //translate value to location
	location = (x+(y*N))*2;
	board[location] = z;
	temp = ctrl_z_current->next;
	RemoveFollowingNodes(temp); /*forget next moves if existing*/
	InsertAtTail(board[location],x,y,ctrl_z_current); /*add former data*/
	ctrl_z_current = ctrl_z_current->next; /*advance current ctrl-z to new node*/
	return 1;
}

int autoFill(int n, int m, int* board, int* state){
	/*function description: Automatically fill "obvious" values � cells which contain a single legal value.
	 * state: solve
	 * args: board - changes current board
	 * return:
	 */
	/*<<<<add special mark in redo\undo and refer in redo/undo and use set!>>>>*/
	int* temp_board,legal_options; int x,y,location;
	const int N = n*m;
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
	return 1;
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

int numSolutions(int n, int m, int* board){
	/*function description: Print the number of solutions for the current board, using Exhaustive backtracking algorithem
	 * state: Edit, Solve
	 * args:
	 * return:
	 */
	int rslt = 0;
	rslt = EBA(n,m,board);
	printf("Number of solutions found for current bard is:%d\n",rslt);
	return 1;
}

int generate(int x, int y, int* board, int n, int m, struct Node* ctrl_z, struct Node* ctrl_z_current){
	/* function description: Generates a puzzle by randomly filling X empty cells with legal values,
running ILP to solve the board, and then clearing all but Y random cells.
	 * state: Edit
	 * args: x --> number of cells to fill, y --> number of cells to clear
	 * return: 0 -> an error occurred, 1 -> board was generated successfully
	 */
	int* temp_board;
	int* random_empty_x_cells;
	int* list;
	int* random_y_cells;
	int empty_cells_cnt = 0;
	int x_temp,y_temp,location, legal;
	const int N = n*m;
	int locations_empty_cells[N*N];
	int list_of_all_cells[N*N];
	int legal_options[N];
	/* check number of empty cells, if X< print an error */
	for (x_temp=0;x_temp<N;x_temp++){
			for (y_temp=0;y_temp<N;y_temp++){
				location = (x_temp+y_temp*N)*2;
				if (board[location] == 0){ /*if cell is empty*/
					locations_empty_cells[empty_cells_cnt]=location;
					empty_cells_cnt++;
				}
			}
		}
	if(empty_cells_cnt<x){
		printf("EROOR: %s",XSIZEISTOOLARGE);
		return 0;
	}
	/* malloc space for temp board, list of empty cells and list of x cells */
	temp_board = (int*)calloc(N*N*2,sizeof(int));
	list = (int*)calloc(empty_cells_cnt,sizeof(int));
	random_empty_x_cells = (int*)calloc(x,sizeof(int));

	/* for (1000), break once the ILP is valid */
	for(int i=0; i<1000; i++){
	//truncate copied board
		deleteUnfixedFromPoint(n,m,temp_board,0);
	/*copy board from original */
		copyBoard(board,temp_board,N);
	/* fill x randomly selected cells with legal values */
		//truncate lists
		truncateArray(list,empty_cells_cnt);
		truncateArray(random_empty_x_cells,x);
		//Select X random unique numbers out of [0,empty_cells_cnt) range
		selectUniqueRandomValues(random_empty_x_cells,x,list,empty_cells_cnt);
		//fill it using optionsForLocation
		for (int i = 0; i < x; i++){
			int j =  random_empty_x_cells[i];
			location = locations_empty_cells[j];
			int y = yFromLocation(N,location);
			int x = xFromLocation(N, location);
			legal = optionsForLocation(n,m,x,y,temp_board,legal_options);
			//check if value is legal
			if(!legal){
				break;
				}
			int sumA = sumArray(legal_options,N);
			if(sumA ==0) {
				legal = 0;
				break;
				}
			//select random option
			int random_location = chooseRandomOption(legal_options,N);
			if(random_location == -1){
				legal = 0;
				break;
				}
			temp_board[location] = random_location;
		}
		//start another iteration if there are no legal values
		if(!legal){
			//printf("Debugging: no legal values, start another iteration");
			continue;
			}
	/*run ILP -> return 1= success, 0 = failure */
	legal = ILP(n,m,temp_board); //debug temp cancelled
	//legal = 1; //<<<debug mode>>>
	/* if there is no solution for board --> start another iteration */
	if(!legal){
		//printf("Debugging: no solution using ILP, start another iteration");
		continue;
			}
	/* if there is solution --> break*/
	if(legal){
		break;
		}
	}
	/* choose y random cells and clear it */
	random_y_cells = (int*)calloc(y,sizeof(int));
	selectUniqueRandomValues(random_y_cells,y,list_of_all_cells,N*N);
	for(int i= 0; i<y; i++){
		location = random_y_cells[i]*2;
		temp_board[location] = 0;
	}
	/* copy to original board using set for undo */
	int i = 0;
	for (i=0;i<(N*N*2);i++){
		int z = temp_board[i];
		int y = yFromLocation(N,i)+1;
		int x = xFromLocation(N, i)+1;
		legal =  set(n, m, x, y, z, board, ctrl_z, ctrl_z_current);
		if(!legal){
			printf("EROOR: %s\n", SETFAILED);
			return 0;
		}
	}
	/* free copied board */
	free(temp_board);
	free(random_empty_x_cells);
	free(list);
	free(random_y_cells);
	return 1;
}

int validate(int n, int m, int* board, int* state){
	/*function description:The command prints whether the board is found to be solvable, or not using ILP
	 * states: Solve, Edit - for sure the right state
	 * args:
	 * return: 0 --> command was not executed, 1 --> command was executed
	 */
	int legal;
	int* temp_board;
	int N= n*m;
	//check if board is erroneous
	legal = isFinished(n,m,board);
	if(!legal){
		printf("ERROR: %s",INVALIDBOARDERROR);
		return 0;
			}
	//check if board is found to be solvable, or not using ILP
	temp_board = (int*)calloc(N*N*2,sizeof(int));
	copyBoard(board,temp_board,N);
	//	legal = ILP(n,m,temp_board); //debug temp cancelled
	legal = 1; //<<<debug mode>>>
		/* if there is no solution for board --> start another iteration */
	if(!legal){
		printf("The board is not solvable");
		return 1;
			}
	printf("The board is solvable");
	free(temp_board);
	return 1;
	/*validate using ILP - return whther the board is */
	/*print*/
}

int guess(int n, int m, float x, int* board, struct Node* ctrl_z, struct Node* ctrl_z_current){
	/*function description: fills all cell values with a score of X or greater using LP. If several
   * values hold for the same cell, randomly choose one according to the score
	 * state: Solve
	 * args: x --> lower boundary of score
	 * return: 0 --> there is no solution to the board / an error occurred, 1 --> board has a solution
	 */
	//printf("Debugging: inside guess \n");
	int legal;
	//check if board is erroneous
	legal = isFinished(n,m,board);
	//printf("Debugging: Guess: isFinished value is %d \n", legal);
	if(!legal){
		printf("ERROR: %s",INVALIDBOARDERROR);
		return 0;
			}
	/* call LP_Solver: get board and solve it using LP If several
	values hold for the same cell, randomly choose one according to the score */
	legal = LPSolver(n,m,x, board, ctrl_z, ctrl_z_current);
	legal = 1; //<<<debug mode>>>
	if(!legal){
		printf("ERROR: %s \n", LPFAILED);
		return 0;
			}
	return 1;
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

int guess_hint(int n, int m, int x,  int y, int* board){
	/* function description: Show a guess to the user for a single cell X,Y using LP and print suggested value
	 * state: Solve
	 * args: x --> lower boundary of score
	 * return: void
	 */
	//printf("Debugging: inside guess hint, n = %d, m = %d, x = %d, y = %d, <1,1> is %d \n", n, m, x, y, board[0]);
	int legal, value_location, fixed_location, result, score;
	int* temp_board;
	float* legal_options;
	const int N = n*m;
	//check if board is erroneous
	legal = isFinished(n,m,board);
	legal = 2; //Debugging
	//printf("Debugging: inside guess hint, isFinished is = %d \n", legal);
	if(!legal){
		printf("ERROR: %s \n",INVALIDBOARDERROR);
		return 0;
			}
	// check if cell <X,Y> is fixed or cell <X,Y> already contains a value
	value_location = locationFromXY(N,x,y);
	//printf("Debugging: inside guess hint, value of location is %d\n", board[value_location] );
	fixed_location = value_location+1;
	if (board[fixed_location] == 1){ //cell is fixed
		printf("ERROR: %s\n",FIXEDCELLERROR);
		return 0;
		}
	if (board[value_location] != 0){ //cell has value
		printf("ERROR: %s \n",FILLEDCELLERROR);
		return 0;
		}
	/* run LP (copy board) */
	temp_board = (int*)calloc(N*N*2,sizeof(int));
	copyBoard(board,temp_board,N);
	legal_options = (float*)calloc(N*2,sizeof(float)); // 0->optional values, 1->score
	legal = LPSolveCell(value_location, n, m, temp_board, legal_options);
	if(!legal){
		printf("ERROR: %s", UNSOLVEDBOARD);
		return 0;
		}
	for(int i = 0; i<N; i++){
		result = i*2;
		score = i*2+1;
		if(legal_options[score]>0){
		printf("Hint: optional value of <%d,%d> is %d with score %f \n", x,y,(int)legal_options[result], legal_options[score]);
		}
	}
	free(temp_board);
	free(legal_options);
	return 1;
	/* print the value of specific location in board */
	/* free copied board */

}

int hint(int n, int m, int x, int y, int* board){
	/*function description: Give a hint to the user by showing the solution of a single cell X,Y
	 * and print the value of cell <X,Y> found by the ILP solution.
	 * check state: solve
	 * args: <x,y> cell location
	 * return:
	 */

	int legal, value_location, fixed_location, result;
			int* temp_board;
			const int N = n*m;
			//check if board is erroneous
			legal = isFinished(n,m,board);
			if(!legal){
				printf("ERROR: %s",INVALIDBOARDERROR);
				return 0;
					}
			// check if cell <X,Y> is fixed or cell <X,Y> already contains a value
			value_location = (x + y*N)*2;
			fixed_location = value_location+1;
			if (board[fixed_location] == 1){ //cell is fixed
				printf("ERROR: %s",FIXEDCELLERROR);
				return 0;
				}
			if (board[value_location] != 0){ //cell has value
				printf("ERROR: %s",FILLEDCELLERROR);
				return 0;
				}
			/* run ILP (copy board) */
			temp_board = (int*)calloc(N*N*2,sizeof(int));
			copyBoard(board,temp_board,N);
			legal = ILP(n,m,temp_board); //debug temp cancelled
			//legal = 1; //<<<debug mode>>>
					/* if there is no solution for board --> start another iteration */
			if(!legal){
				printf("ERROR: %s", UNSOLVEDBOARD);
				return 0;
				}
			result = temp_board[value_location];
			printf("Hint: the value of <%d,%d> is %d", x,y,result);
			free(temp_board);
			return 1;
			/* print the value of specific location in board */
			/* free copied board */
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
	/*if -1 run until -1*/
	int location = 0; const int N = n*m;
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
	/*<<<<if has -1 run until next -1>>>>*/
	int location = 0; const int N = n*m;
	if (ctrl_z_current->next == NULL){printf("%s\n",NOMOREMOVES);return 0;}
	ctrl_z_current = ctrl_z_current->next;
	location = (ctrl_z_current->x+(ctrl_z_current->y*N))*2;
	board[location] = ctrl_z_current->data;
	return 1;
}

int save(int n, int m, char* path, int* board, int* state){
	/*function description: Saves the current game board to the specified file
	 * states: Edit, Solve
	 * args: X --> file's path
	 * return: void
	 */
	int i = 0; const int N = n*m; int* temp_board;
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
			return 0;
		}
	}
	if (writeBoardToFile(n,m,temp_board,path) == 1){printf("%s\n",SAVINGFAILED);}
	free(temp_board);
	return 1;
}

void toInit(int* board, int* guess_board,int* m, int* n,int* mark_errors, struct Node* ctrl_z, struct Node* ctrl_z_current,int* state){
	/*function description: change state to 'init' mode, sets all global parameters to default.
	 * args: all global parameters
	 * return: void
	 */
	/*n,m to 9, state to 0, boards to empty*/
	int N;
	free(board);
	free(guess_board);
	n = 3; m = 3; state = 0; mark_errors = 1;
	N = (int)n*(int)m;
	board = calloc(N*N*2,sizeof(int));
	guess_board = calloc(N*N*2,sizeof(int));
	ctrl_z_current = ctrl_z;
	RemoveFollowingNodes(ctrl_z);
}

int toSolve(int* n, int* m, char* path, int* state, int** board, int* guess_board,struct Node* ctrl_z, struct Node* ctrl_z_current){
	/*function description: change state to 'Solve' mode, and set board from file
	 * args: x --> file path
	 * return: 1 - successful, 0 unsuccessful
	 */
	int* temp_board, tempn, tempm; int fail = 0; int N;
	int i; //debug
//	printf("debug: toSolve(2) called\n");
//	printf("with: n:%d,m:%d,path:%s,board:%d,state:%d\n",n,m,path,board,state);
//	printf("debug: state:%d,state*:%d\n",state,*state);
	*state = 1;
	fail = readBoardFromFile(&tempn, &tempm, &temp_board, path);
//	printf("debug: tosolve(0) tn:%d,tm:%d,fail:%d\n",tempn,tempm,fail);
	if (fail == 1){printf("%s\n",READINGFAILED); return 0;}
	else{ /*reading successful*/
//		free(board); /*<<<<need to free!!!>>>>*/
		free(*guess_board);
		*board = temp_board;
//		printf("debug: board:%d,guess board:%d\n",board,guess_board);
		*n = tempn;
		*m = tempm;
		N = (int)n*(int)m;
//		printf("debug: tosolve(1) n:%d,*n:%d,tempn:%d\n",n,*n,tempn);
//		printf("board:"); //debug
//		for (i = 0;i<N*N*2;i++){ //debug
//			printf("%d|",temp_board[i]); //debug
//		} //debug
//		printf("\n"); //debug
//		printBoard(*board,*n,*m,2,1);//debug
		guess_board = calloc(N*N*2,sizeof(int));
	}
	return 1;
}

int toEdit(int* board, int* guess_board,int* m, int* n,int* mark_errors, int* state, char* user_path,struct Node* ctrl_z, struct Node* ctrl_z_current){
	/*function description: change state to 'Edit' mode, and set board from file or to empty board if the file path is empty
	 * args: x --> file path
	 * return: void
	 */
	int* temp_board, tempn, tempm; const int N = (*n)*(*m);
	*state = 2;
	if (strlen(user_path) == 0){
		toInit(board, guess_board, m, n,mark_errors, ctrl_z, ctrl_z_current,state);
	}
	if (readBoardFromFile(tempn, tempm, temp_board, user_path) == 1){printf("%s/n",READINGFAILED);}
	else{
		free(board);
		board = temp_board;
		n = tempn;
		m = tempm;
	}
	return 1;
}

