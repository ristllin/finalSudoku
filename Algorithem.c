/*
 * Algorithem.c
 *
 *  Created on: Mar 16, 2019
 *      Author: Roy Darnell
 */
#include "AuxFunctions.h"

int EBA(int n,int m,int* board){
	int rslt = -1;
	/* EBA - exhaustive backtracking algorithm, runs over every legal value for every empty cell (by index)
	 *  args: current board
	 *  return: number of correct solutions from current state (doesn't change given board)
	 * */
	int *temp_board; const N = n*m; int i;
	temp_board = calloc(N*N*2,sizeof(int));
	copyBoard(board,temp_board,N); /*copy board to temp_board*/
	for (i=0;i<N*N;i++){ /*each existing value in board, fix in temp_board*/
		if (board[i*2] != 0){
			temp_board[i*2+1] = 1;
		}
	}
	rslt = recursiveEBA(n,m,temp_board,0); /*send to recursive EBA starting from 0*/
	free(temp_board);
	return rslt;
}

int recursiveEBA(int n, int m, int* board, int starting_point){
	/* EBA - exhaustive backtracking algorithm, runs over every legal value for every empty cell (by index)
	 *  args: current board, starting point - actual place (including fixed\unfixed cells) on board
	 *  return: number of correct solutions from current state (doesn't change given board)
	 * */
	const N = n*m; int board_state,fixed = -1; int* legal_options; int rslt,i,value = 0;
	legal_options = calloc(N,sizeof(int));
	/*if board is legaly finished return 1*/
	board_state = isFinished(n,m,board);
	switch(board_state){
		case(0):
			free(legal_options);
			return 0; /*if board has illegal cell - return 0*/
			break;
		case(1):
			free(legal_options);
			return 1; /*if board is finished - return 1*/
			break;
	}
	/*board isn't finished*/
	deleteUnfixedFromPoint(n,m,board,starting_point);
	fixed = board[starting_point + 1];
	while (fixed != 0 && starting_point < N*N*2){ /*find next unfixed cell and set starting point to it*/
		starting_point += 2;
		fixed = board[starting_point + 1];
	}
	if (optionsForLocation(n,m,xFromLocation(N,starting_point),yFromLocation(N,starting_point),board,legal_options) == 0){return 0;}//check next unfixed cell's options
	for (i=0;i<N;i++){/*for each option fill cell with one of the values and call recuresively*/
		if (legal_options[i] == 1){
			rslt += recursiveEBA(n, m, board, starting_point+2);/*add to rslt variable all options that returned with value*/
		}
	}
	free(legal_options);
	return rslt;
}

int ILP(int* board){
	/* ILP - Integer Linear Programming, used by validate, generate and hint functions, uses gorubi to solve the board
	*  args: soduko board
	*  return: soduko board (changes given board), 0 -> no solution, 1 -> there is solution
	* */
}

int LP(float threshold, int* board, int* guess_board){
	/* Linear programming algorithm, Used by guess and guessHint functions. solves using gorubi solver module
	*  args: gets board to solve, doesn't change it, builds solution on guess board
	*  return: edits guess_board, 0 -> no solution to guess_board, 1 -> there is solution
	* */
}

void boardToMatrix(int* board, int* matrix){
	/* gets board, translates into a matrix that gorubi can solve
		*  args: soduko board
		*  return: gorubi n*n*n matrix
		* */

}
