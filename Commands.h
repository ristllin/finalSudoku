/*
 * Commands.h
 *
 *  Created on: Mar 16, 2019
 *      Author: shahare
 */
#include "List.h"

#ifndef COMMANDS_H_
#define COMMANDS_H_

int execute(int** board, int* user_command, char* user_path, int* m, int* n, int* mark_errors,int* state, Node* ctrl_z, Node** ctrl_z_current, float user_threshold);
void exitSudoku(int** board,Node* ctrl_z);
int set(int n, int m, int x, int y, int z, int* board, Node* ctrl_z, Node** ctrl_z_current,int* state);
int autoFill(int n, int m, int* board, int* state,Node* ctrl_z, Node** ctrl_z_current);
void markErrors(int x, int* mark_errors);
int numSolutions(int n, int m, int* board);
int generate(int x, int y, int* board, int n, int m, Node* ctrl_z, Node** ctrl_z_current);
int validate(int n, int m, int* board);
int guess(int n, int m, float x, int* board, Node* ctrl_z, Node** ctrl_z_current, int* state);
void reset(int n, int m, int* board, Node* ctrl_z, Node** ctrl_z_current);
int guess_hint(int n, int m, int x,  int y, int* board);
int hint(int n, int m, int x, int y, int* board);
int undo(int n, int m, int* board, Node* ctrl_z, Node** ctrl_z_current);
int redo(int n, int m, int* board, Node* ctrl_z, Node** ctrl_z_current);
int save(int n, int m, char* path, int* board, int state);
void toInit(int** board,int* m, int* n,int* mark_errors, Node* ctrl_z, Node** ctrl_z_current,int* state);
int toSolve(int* n, int* m, char* path, int* state, int** board);
int toEdit(int** board,int* m, int* n,int* mark_errors, int* state, char* user_path,Node* ctrl_z, Node** ctrl_z_current);
void truncateArray(int* array, int length);
int chooseRandomOption(int* options,int length);
int selectUniqueRandomValues(int* shuffeled_list, int shuffeled_list_length, int* range_list, int range_list_length);

#endif /* COMMANDS_H_ */
