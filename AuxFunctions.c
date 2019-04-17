/*
 * AuxFunctions.h
 *
 *  Created on: Mar 16, 2019
 *      Author: Roy Darnell
 */

int is_finished(int n, int m, int* board){
	/*function description: checks if board is full and legal, meaning the user won or not yet.
	 * args: board - sudoku board n*n
	 * return: 0 - didn't win, 1 - won.
	 */
	return 0;
}

void options_for_location(int x,int y, int n, int m, int* board, int* options){
	/*function description: returns an int array of length n with all of the legal options for a specific (x,y) slot in the board
	 * args: x,y, - location to check options in; n,m,board - sudoku board, options - array to fill with options
	 * return: options - int array, 0- not a legal option, 1- a legal option for the location
	 */
}

void seperator(int n,int m){
	int i;
	for (i = 0;i < 4*(n*m)+m+1;i++){
		printf("-");
	}
	printf("\n");
}
