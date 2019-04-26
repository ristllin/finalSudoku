/*
 * Commands.h
 *
 *  Created on: Mar 16, 2019
 *      Author: shahare
 */

#ifndef COMMANDS_H_
#define COMMANDS_H_

void execute(int* board, int* user_command, char* user_path, int* m, int* n, int* mark_errors,int* state, struct Node* ctrl_z, struct Node* ctrl_z_current, int* guess_board);
void exitSudoku(int* board, int* user_command, int* m, int* n, int* mark_errors,int* state, struct Node* ctrl_z, struct Node* ctrl_z_current, int* guess_board);
int set(int n, int m, int x, int y, int z, int* board, struct Node* ctrl_z, struct Node* ctrl_z_current);
void autoFill(int n, int m, int* board, int* state);
void markErrors(int x, int* mark_errors);
void numSolutions(int n, int m, int* board);
void generate(int x, int y, int* board);
void validate(int* board, int* state);
void guess(float x, int* state, int* board);
void reset(int n, int m, int* board, struct Node* ctrl_z, struct Node* ctrl_z_current);
void guess_hint(int x, int* state, int* board);
void hint(int x, int y, int* board, int* state);
int undo(int n, int m, int* board, struct Node* ctrl_z, struct Node* ctrl_z_current);
int redo(int n, int m, int* board, struct Node* ctrl_z, struct Node* ctrl_z_current);
void save(int n, int m, char* path, int* board, int* state);
void toInit(int* board, int* guess_board,int* m, int* n,int* mark_errors, struct Node* ctrl_z, struct Node* ctrl_z_current,int* state);
void toSolve(int* n, int* m, char* path, int* state, int* board, int* guess_board);
void toEdit(int* n, int* m, char* path, int* state, int* board);


#endif /* COMMANDS_H_ */
