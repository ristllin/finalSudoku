/*
 * IOCommands
 *
 *  Created on: Mar 16, 2019
 *      Author: Roy Darnell and Shahar Eshed
 */

/*modules*/
#include <AuxFunctions.c>;

void printBoard(int* board, int* state, int mark_errors){
	/*function description: print the board
	 * state: Solve, Edit
	 * args: mark_errors - whether to mark errors or not
	 * return: void
	 */
	int row; int col; int value; int fixed;
	seperator(n,m);
	for (row = 0;row < n;row++){
		printf("|"); /*starting a new row*/
		for (col = 0;col < n;col++){
			value = board[(row*n+col)*2]; /*starting a new cell*/
			fixed = board[(row*n+col)*2 + 1];
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
		seperator(n,m); /*End of row*/
	}
	printf("\n"); /*end of print*/
}

void readBoardFromFile(???){

}

void writeBoardToFile(???) {

}

