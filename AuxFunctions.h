/*
 * AuxFunctions.h
 *
 *  Created on: Mar 16, 2019
 *      Author: Roy Darnell
 */

#ifndef AUXFUNCTIONS_H_
#define AUXFUNCTIONS_H_

int isFinished(int n, int m, int* board);
int optionsForLocation(int n, int m, int x, int y, int* board, int* legal_options);
int isLegal(int n, int m, int x, int y, int* board);
void seperator(int n,int m);
void copyBoard(int* origin, int* target, int N);
int singleOption(int* options,int N);
void deleteUnfixedFromPoint(int n, int m, int* board,int location);
int sumArray(int* array, int length);
int yFromLocation(int N, int location);
int xFromLocation(int N, int location);
int locationFromXY(int N, int x, int y);
void updateErrors(int n, int m, int* board);
int isLegalLocal(int n, int m, int x, int y, int* board);

#endif /* AUXFUNCTIONS_H_ */
