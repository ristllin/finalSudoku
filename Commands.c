/*
 * Commands.c
 *
 *  Created on: Mar 16, 2019
 *      Author: shahare
 */

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

void execute(int* board, int* user_command, char* user_path, int m, int n, int* mark_errors,int* ctrl_z,int* state, int* ctrl_z_current){

}

void exit(){
	/*function description: Terminates the program.
	 * args:
	 * return:
	 */

}

void set(int x, int y, int z, int* state, int* ctrl_z, int* ctrl_z_current){
	/*function description: sets the value of cell <x,y> to z, user may empty a cell
	 * satet: Edit, Solve (fixed cells are not updated)
	 * args: cell -> <x,y>
	 * return:
	 */
	/*set*/
	/*check if user entered erroneous value*/
	/*update ctrl_z, delete the further steps after current one*/

}

void autoFill(int* board, int* state){
	/*function description: Automatically fill "obvious" values – cells which contain a single legal value.
	 * state: solve
	 * args:
	 * return:
	 */

}

void markErrors(int x, int* mark_errors, int* state){
	/*function description: set the mark_errors flag to x value
	 * state: Solve
	 * args: x
	 * return: void
	 */

}

void numSolutions(int* board, int* state){
	/*function description: Print the number of solutions for the current board
	 * state: Edit, Solve
	 * args:
	 * return:
	 */

}

int generate(int x, int y, int* board, int n, int m){
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
	const N = n*m;
	int locations_empty_cells[N*N];
	int list_of_all_cells[N*N];
	int legal_options[N];
	/* check number of empty cells, if X< print an error */
	for (x_temp=0;x_temp<N;x_temp++){
			for (y_temp=0;y_temp<N;y_temp++){
				location = (x_temp+y_temp*N)*2;
				if (temp_board[location] == 0){ /*if cell is empty*/
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
			printf("Debugging: no legal values, start another iteration");
			continue;
			}
	/*run ILP -> return 1= success, 0 = failure */
	legal = ILP(temp_board);
	/* if there is no solution for board --> start another iteration */
	if(!legal){
		printf("Debugging: no solution using ILP, start another iteration");
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
	/* copy to original board */
	copyBoard(temp_board,board,N);
	/* free copied board */
	free(random_empty_x_cells);
	free(list);
	free(random_y_cells);
}

void validate(int* board, int* state){
	/*function description:The command prints whether the board is found to be solvable, or not using ILP
	 * states: Solve, Edit - for sure the right state
	 * args:
	 * return:void
	 */

	/*validate using ILP - return whther the board is */
	/*print*/

}

void guess(float x, int* state, int* board){
	/*function description: fills all cell values with a score of X or greater usong LP. If several
values hold for the same cell, randomly choose one according to the score 	 *
	 * state: Solve
	 * args: x --> lower boundary of score
	 * return: void
	 */

}

void reset(int* state, int* board, int* ctrl_z, int* ctrl_z_current){
	/* function description: Undo all moves, reverting the board to its original loaded state
	 * state: Solve, Edit
	 * args:
	 * return: void
	 */

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
	 * check state: solve
	 * args: <x,y> cell location
	 * return:
	 */
	/* malloc space for new board */
	/* copy board */
	/* run ILP */
	/* print the value of specific location in board */
	/* free copied board */

}

void undo(int* board, int* state){
	/*function description: Undo previous moves done by the user
	 * states: Edit, Solve
	 * args:
	 * return:
	 */
	/* set to board to previous state */
	/* set pointer in the list */
	/* no moves to undo --> error */
	/* print change */

}

void redo(int* board, int* state){
	/*function description: Redo a move previously undone by the user.
	 * states: Edit, Solve
	 * args:
	 * return: void
	 */
	/* set to board to next state */
	/* set pointer in the list */
	/* no moves to redo --> error */
	/* print change */

}

void save(char* X, int* board, int* state){
	/*function description: Saves the current game board to the specified file
	 * states: Edit, Solve
	 * args: X --> file's path
	 * return:
	 */

	/*check mode*/
	/* edit - do not save erroneous files and boards without solution*/
	/* edit - mark cells containing values as fixed */

}

void toInit(){
	/*function description:
	 * args:
	 * return:
	 */

}

void toSolve(char* x, int* state, int* board){
	/*function description: change state to 'Solve' mode, and set board from file
	 * args: x --> file path
	 * return: void
	 */

}

void toEdit(char* x, int* state, int* board){
	/*function description: change state to 'Edit' mode, and set board from file or to empty board if the file path is empty
	 * args: x --> file path
	 * return: void
	 */

}

