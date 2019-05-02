/*
 * Commands.h
 *
 *  Created on: Mar 16, 2019
 *      Author: shahare
 */

#ifndef COMMANDS_H_
#define COMMANDS_H_

int execute(int** board, int* user_command, char* user_path, int* m, int* n, int* mark_errors,int* state, struct Node* ctrl_z, struct Node* ctrl_z_current, int* guess_board, float user_threshold);
void exitSudoku(int* board, int* user_command, int* m, int* n, int* mark_errors,int* state, struct Node* ctrl_z, struct Node* ctrl_z_current, int* guess_board);
int set(int n, int m, int x, int y, int z, int* board, struct Node* ctrl_z, struct Node** ctrl_z_current,int* state);
int autoFill(int n, int m, int* board, int* state,struct Node* ctrl_z, struct Node** ctrl_z_current);
void markErrors(int x, int* mark_errors);
int numSolutions(int n, int m, int* board);
int generate(int x, int y, int* board, int n, int m, struct Node* ctrl_z, struct Node** ctrl_z_current,int* state);
int validate(int n, int m, int* board);
int guess(int n, int m, float x, int* board, struct Node* ctrl_z, struct Node** ctrl_z_current, int* state);
void reset(int n, int m, int* board, struct Node* ctrl_z, struct Node** ctrl_z_current);
int guess_hint(int n, int m, int x,  int y, int* board);
int hint(int n, int m, int x, int y, int* board);
int undo(int n, int m, int* board, struct Node* ctrl_z, struct Node** ctrl_z_current);
int redo(int n, int m, int* board, struct Node* ctrl_z, struct Node** ctrl_z_current);
int save(int n, int m, char* path, int* board, int* state);
void toInit(int* board, int* guess_board,int* m, int* n,int* mark_errors, struct Node* ctrl_z, struct Node** ctrl_z_current,int* state);
int toSolve(int* n, int* m, char* path, int* state, int** board, int* guess_board,struct Node* ctrl_z, struct Node* ctrl_z_current);
int toEdit(int* board, int* guess_board,int* m, int* n,int* mark_errors, int* state, char* user_path,struct Node* ctrl_z, struct Node** ctrl_z_current);


#endif /* COMMANDS_H_ */
