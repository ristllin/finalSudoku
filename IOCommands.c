/*
 * IOCommands
 *
 *  Created on: Mar 16, 2019
 *      Author: Roy Darnell and Shahar Eshed
 */

/*modules:*/
#include <AuxFunctions.c>;
#include <Constants.c>;
/*libraries:*/
#include <stdio.h>
#include <stdlib.h>

void printBoard(int* board,int n, int m, int* state, int mark_errors){
	/*function description: print the board
	 * state: Solve, Edit
	 * args: mark_errors - whether to mark errors or not
	 * return: void
	 */
	int row; int col; int value; int fixed;
	int N = n * m;
	seperator(n,m);
	for (row = 0;row < N;row++){
		printf("|"); /*starting a new row*/
		for (col = 0;col < N;col++){
			value = board[(row*N+col)*2]; /*starting a new cell*/
			fixed = board[(row*N+col)*2 + 1];
			printf(" ");
			if (value == 0){
				printf("  ");
			}
			else {
				printf("%2d",value);
			}
			switch(fixed){
				case 0: /*unmarked*/
					printf(" ");
					break;
				case 1: /*fixed cell*/
					printf(".");
					break;
				case 2: /*erroneous value in cell*/
					if (mark_errors == 1){
						printf("*");
					}
					break;
			}
			if ((col+1) % m == 0){ /*creating m blocks*/
				printf("|");
			}
		}
		printf("\n");
		seperator(n,m);
		if ((row+1) % n == 0) {
			seperator(n,m);/*End of row*/
		}
	}
	printf("\n"); /*end of print*/
}

int readBoardFromFile(int* n, int* m, int* board,char* path){
	/*function description: loads file in correct format to a given soduko board variable
		 * args: n,m - size of board, path - file path
		 * return: 1 for fail, 0 for success
		 */
	/*printf("LoadBoard() called\n");*/
	FILE* file_pointer; int N; int num,c,location = 0;
	file_pointer = fopen(path, "r");
	if (file_pointer == NULL){ /*catch errors*/
		printf("%s\n",INVALIDFILEPATH);
		fclose(file_pointer);
		return 1;
	}
	while(c != '\n' && !(feof(file_pointer))){ /*get n,m*/
		c = fgetc(file_pointer);
		if (c != ' ' && c != '\n'){
			num = num * 10 + (c - 48); /*Accumulating number*/
		}
		if (c == ' '){
			*n = num;
			num = 0;
		}
		if (c == '\n'){
			*m = num;
			num = 0;
		}
	}
	N = (*n) * (*m);
	realloc(board,N*N*2,sizeof(int)); /* rows*XcolumnsX[value,type]* */
	while (1) { /*sets board according to n and m*/
		c = fgetc(file_pointer);
		if( feof(file_pointer) ) {
			break ;
		}
		if (c != '\n' && c!= ' ' && c!= '.'){ /*a number*/
			num = num * 10 + (c - 48);
		}else if (c != '\n'){ /*a sign skips new line*/
			board[location] = num;
			num = 0;
			location += 1;
			if (c == '.'){
				board[location] = 1;
			} else { /*c == ' '*/
				board[location] = 0;
			}
			location += 1;
		}
	}
	printf("EOF\n");
	fclose(file_pointer);
	return 0;
}

int writeBoardToFile(int n, int m, int* board,char* path){
	/*function description: saves soduko board to a file
		 * args: n,m - size of board, path - file path
		 * return: 1 for fail, 0 for success
		 */
	/*printf("saveBoard() Called\n");*/
	FILE* file_pointer; int row,col; int N = n*m;
	file_pointer = fopen(path, "w+");
	int value; int fixed; char* sign;
	if (file_pointer == NULL){
		printf("%s\n",INVALIDFILEPATH);
		fclose(file_pointer);
		return 1;
	}
	fprintf(file_pointer,"%d %d\n",n,m); //	The first line contains the block size m n. These are two integers, separated by a single space.
	for (row = 0; row < N; row++){ //	Each line contains a single row of the board.
		for (col = 0; col < N; col++){
			value = board[(row*N+col)*2]; /*starting a new cell*/
			fixed = board[(row*N+col)*2 + 1];
			printf("%d%d|",value,fixed);
			if (fixed == 1){
				sign = ".";
			} else if(fixed == 0){
				sign = " ";
			} else {
				printf("%s\n",ILLEGALSAVEERROR);
				fclose(file_pointer);
				return 1;
			}
			fprintf(file_pointer,"%d%s",value,sign);
		}
		fprintf(file_pointer,"\n");
	}
	fclose(file_pointer);
	return 0;
}

