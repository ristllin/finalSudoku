/*
 * Algorithem.c
 *
 *  Created on: Mar 16, 2019
 *      Author: Roy Darnell
 */

int EBA(int* board){
	int rslt = -1;
	/* EBA - exhaustive backtracking algorithm, runs over every legal value for every empty cell (by index)
	 *  args: current board
	 *  return: number of correct solutions from current state (doesn't change given board)
	 * */
	return rslt;
}

void ILP(int* board){
	/* ILP - Integer Linear Programming, used by validate, generate and hint functions, uses gorubi to solve the board
	*  args: soduko board
	*  return: soduko board (changes given board)
	* */
}

void LP(float threshold, int* board, int* guess_board){
	/* Linear programming algorithm, Used by guess and guessHint functions. solves using gorubi solver module
	*  args: gets board to solve, doesn't change it, builds solution on guess board
	*  return: edits guess_board
	* */
}

void boardToMatrix(int* board, int* matrix){
	/* gets board, translates into a matrix that gorubi can solve
		*  args: soduko board
		*  return: gorubi n*n*n matrix
		* */

}
