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
	int x,y,location = 0;
	const N = n * m;
	for (x=0;x<N;x++){
		for (y=0;y<N;y++){
			location = (x + y*N)*2;
			if (!isLegal(n,m,x,y,board[location] || board[location] == 0)){return 0;} /*not legal or empty*/
		}
	}
	return 1;
}

int optionsForLocation(int n, int m, int x, int y, int* board, int* legal_options){
	/*function description: returns which options are legal for cell (x,y) {starting from 0} in the given board.
	 * using N integers in an array, stating with 1\0, according to their place, whether or not a number is legal to that position.
	 * args: legal options, an N long array, "calloced" in advance!
	 * return: 1 current value in position is legal, 0 if illegal (and legal options is not valid). returns legal if empty.
	 */
	int i,j,location,tmpx,tmpy; int N = n*m; int* temp_legal;
	temp_legal = (int*)calloc(N,sizeof(int));
	for (i=0;i<N;i++){ /*zero out N variables in options list*/
		legal_options[i] = 1;
		temp_legal[i] = 1;
	}
	if (x > N || y > N){printf("<<<isLegal() assertion - illegal parameters x or y>>>\n"); return 0;} /*assertion*/
	for (i=0;i<N;i++){ /*check row*/
		location = ((y*N)+i)*2; /*y*N*2 - starting row location on board*/
		if (i == x || board[location] == 0){continue;} /*skip x,y cell and 0s*/
		if (temp_legal[board[location]-1] == 0){return 0;} /*double value -1 because temp_legal counts from 0*/
		temp_legal[board[location]-1] = 0;
		legal_options[board[location]-1] = 0;
	}
	for (i=0;i<=N;i++){temp_legal[i] = 1;} /*zero temp board*/
	for (i=0;i<N;i++){ /*check column*/
		location = ((i*N)+x)*2; /*i*N*2+x - starting row location on board*/
		if (i == y || board[location] == 0){continue;} /*skip x,y cell and 0s*/
		if (temp_legal[board[location]-1] == 0){return 0;} /*double value - -1 because temp_legal counts from 0*/
		temp_legal[board[location]-1] = 0;
		legal_options[board[location]-1] = 0;
	}
	for (i=0;i<N;i++){temp_legal[i] = 1;} /*zero temp board*/
	for (i=0;i<N;i++){ /*check box*/
		tmpx = (x/n)*n+i%n;
		tmpy = (y/m)*m+i/n;
		location = (tmpx+tmpy*N)*2;
		if ((tmpx == x && tmpy == y) || board[location] == 0){continue;} /*skip x,y cell and 0s*/
		if (temp_legal[board[location]-1] == 0){return 0;}
		temp_legal[board[location]-1] = 0;
		legal_options[board[location]-1] = 0;
	}
	free(temp_legal);
	return 1; /*finished successfully*/
}

int is_legal(int n, int m, int x, int y, int* board){
	/*function description: Uses optionForLocation. checks if current value in cell is legal.
	 * args:
	 * return: 1 if current value in cell is legal; 0 if not or if illegal state found in row\column\box of the cell. returns legal (1) for empty cell.
	 */
	int* legal_options; int rslt,location; const N = n*m;
	legal_options = calloc(N,sizeof(int));
	location = (x+y*N)*2;
	if (board[location] == 0){return 1;} /*empty cell*/
	rslt = optionForLocation(n,m,x,y,board,legal_options);
	if (rslt == 0){return 0;}
	if (legal_options[board[location]-1] == 0){return 0;} /*illegal option for cell*/
	free(legal_options);
	return 1; /*valid option*/
}

void seperator(int n,int m){
	int i;
	for (i = 0;i < 4*(n*m)+m+1;i++){
		printf("-");
	}
	printf("\n");
}

void copyBoard(int* origin, int* target, int N){
	/*function description: copies board of length N to target board
	 * args:origin - board to copy from, target - board to copy to. N = m*n
	 * return:
	 */
	int i = 0; for (i=0;i<(N*N*2);i++){target[i] = origin[i];}
}

int singleOption(int* options,int N){
	/*function description: checks if only 1 value in the given array is 1.
	 * args: N size of array
	 * return: 0 if more than one cell size is 1 (and not 0) or no cells with value, otherwise, returns index of single cell with value.
	 */
	int rslt,i = 0;
	for (i=0;i<N;i++){
		if (options[i] != 0) {
			if (rslt != 0) { /*more than single cell with value*/
				return 0;
			} else { /*first cell with value*/
				rslt = i;
			}
		}
	}
	return rslt;
}
