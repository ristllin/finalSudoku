/*
 * IOCommands
 *
 *  Created on: Mar 16, 2019
 *      Author: Roy Darnell and Shahar Eshed
 */

/*modules:*/
#include "Constants.h"
#include "AuxFunctions.h"
/*libraries:*/
#include <stdio.h>
#include <stdlib.h>

void printBoard(int* board,int n, int m, int* state, int mark_errors){
	/*function description: print the board
	 * state: Solve, Edit
	 * args: mark_errors - whether to mark errors or not
	 * return: void
	 */
//	printf("debug: printBoard() called\n");
//	printf("with: n:%d,m:%d,board:%d\n",n,m,board);

	int row; int col; int value; int fixed;
	int N = n * m;
	if (n == 0 || m == 0){return;}
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
		if ((row+1) % n == 0 && row+1 != N) {
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
	FILE* file_pointer; int N; int num,c,location = 0;
	int* new_board;
//	path = "D:/9board.txt"; //debug!!!! <<<<must remove >>>>>
//	printf("debug: LoadBoard() called with path:%s \n",path);
	file_pointer = fopen(path, "r");
	if (file_pointer == NULL){ /*catch errors*/
		printf("%s: %s \n",INVALIDFILEPATH,path);
		fclose(file_pointer);
		return 1;
	}
	num = 0;
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
	if (*n > 5 || *m > 5){printf("%s \n",CURRUPTFILEFORMAT);return 1;}
	N = (int)*n * (int)*m;
//	printf("debug: reallocating with N:%d\n",N);
	new_board = (int*)calloc(board,N*N*2*sizeof(int)); /* rows X columns X [value,type] */
//	free(board); //<<<need to happen to avoid memory leak!>>>
//	printf("debug: reallocation successful\n");
	while (1) { /*sets board according to n and m*/
		c = fgetc(file_pointer);
//		printf("%c|",c);
		if( feof(file_pointer) ) {
			break ;
		}
		if (c != '\n' && c!= ' ' && c!= '.'){ /*a number*/
			num = num * 10 + (c - 48);
		}else if (c != '\n'){ /*a sign skips new line*/
			new_board[location] = num;
			num = 0;
			location += 1;
			if (c == '.'){
				new_board[location] = 1;
			} else { /*c == ' '*/
				new_board[location] = 0;
			}
			location += 1;
		}
	}
	*board = new_board;
//	printf("\n"); //debug
//	int i; //debug
//	for (i = 0;i<N*N*2;i++){printf("%d|",board[i]);} printf("\n"); //debug
//	fclose(file_pointer); /*<<<need to release file>>>*/
//	file_pointer = NULL;
//	printBoard(*board,*n,*m,2,1); //debug
//	printf("debug: in readfrom() n:%d,m:%d\n",*n,*m);//debug
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

