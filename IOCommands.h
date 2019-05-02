/*
 * IOCommands
 *
 *  Created on: Mar 16, 2019
 *      Author: shahare
 */

#ifndef IOCOMMANDS_H_
#define IOCOMMANDS_H_

void printBoard(int* board,int n, int m, int* state, int mark_errors);
int readBoardFromFile(int* n, int* m, int* board,char* path);
int writeBoardToFile(int n, int m, int* board,char* path);

#endif /* IOCOMMANDS_H_ */
