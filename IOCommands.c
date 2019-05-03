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

void printBoard(int* board,int n, int m, int mark_errors){
	/*function description: print the board
	 * state: Solve, Edit
	 * args: mark_errors - whether to mark errors or not
	 * return: void
	 */

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
					else {
						printf(" ");
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

int readBoardFromFile(int* n, int* m, int** board,char* path){
	/*function description: loads file in correct format to a given soduko board variable
		 * args: n,m - size of board, path - file path
		 * return: 1 for fail, 0 for success
		 */
	FILE* file_pointer;
	int N;
	int num,c,location;
	int* new_board;
	if (DEBUG){printf(">>debug: readBoardFromFile() called\n");}
	/*if (DEBUG){printf("with: n:%d,m:%d,board:%d,path:%d\n",n,m,board,path);}*/
	file_pointer = fopen(path, "r");
	if (file_pointer == NULL){ /*catch errors*/
		printf("%s: %s \n",INVALIDFILEPATH,path);
		if (DEBUG){printf("<<debug: readBoardFromFile(1) finished\n");}
		return 1;
	}
	location = 0;
	num = 0;
	while(c != '\n' && !(feof(file_pointer))){ /*get n,m*/
		c = fgetc(file_pointer);
		if (DEBUG){printf("%c|",c);}
		if (c != ' ' && c != '\n'){
			num = (num * 10) + (c - 48); /*Accumulating number*/
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
	if (DEBUG){printf("\n");}
	if (*n > 5 || *m > 5 || *m <= 0 || *n <= 0){printf("%s \n",CURRUPTFILEFORMAT);return 1;}
	N = (int)*n * (int)*m;
	new_board = (int*)calloc(N*N*2,sizeof(int)); /* rows X columns X [value,type] */
/*	free(board); <<<need to happen to avoid memory leak!>>> */
	while (1) { /*sets board according to n and m*/
		c = fgetc(file_pointer);
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
	fclose(file_pointer); /*<<<need to release file>>>*/
	if (DEBUG){printf("n:%d,m:%d\n",*n,*m);}
	if (DEBUG){printBoard(*board,*n,*m,1);}
	if (DEBUG){printf("<<debug: readBoardFromFile(0) finished\n");}
	return 0;
}

int writeBoardToFile(int n, int m, int* board,char* path){
	/*function description: saves soduko board to a file
		 * args: n,m - size of board, path - file path
		 * return: 1 for fail, 0 for success
		 */
	FILE* file_pointer;
	int row,col;
	int N = n*m;
	int value;
	int fixed;
	char* sign;
	file_pointer = fopen(path, "w+");
	if (DEBUG){printf(">>debug: WriteBoardToFile() called\n");}
	/*if (DEBUG){printf("with: n:%d,m:%d,board:%d,path:%s\n",n,m,board,path);}*/
	if (file_pointer == NULL){
		printf("%s\n",INVALIDFILEPATH);
		fclose(file_pointer);
		if (DEBUG){printf("<<debug: WriteBoardToFile(1) finished\n");}
		return 1;
	}
	fprintf(file_pointer,"%d %d\n",n,m); /*	The first line contains the block size m n. These are two integers, separated by a single space. */
	for (row = 0; row < N; row++){ /*	Each line contains a single row of the board. */
		for (col = 0; col < N; col++){
			value = board[(row*N+col)*2]; /*starting a new cell*/
			fixed = board[(row*N+col)*2 + 1];
			if (fixed == 1){
				sign = ".";
			} else if(fixed == 0){
				sign = " ";
			} else {
				printf("%s\n",ILLEGALSAVEERROR);
				fclose(file_pointer);
				if (DEBUG){printf("<<debug: WriteBoardToFile(1) finished\n");}
				return 1;
			}
			fprintf(file_pointer,"%d%s",value,sign);
		}
		fprintf(file_pointer,"\n");
	}
	fclose(file_pointer);
	if (DEBUG){printf("<<debug: WriteBoardToFile(0) finished\n");}
	return 0;
}

