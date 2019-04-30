/*
 * Algorithem.h
 *
 *  Created on: Mar 16, 2019
 *      Author: shahare
 */

//#include "gurobi_c.h"

#ifndef ALGORITHEM_H_
#define ALGORITHEM_H_

int recursiveEBA(int n, int m, int* board, int starting_point);
int EBA(int n,int m,int* board);
int randomWeightedNumber(double* list, int length);
int LP(int n, int m, double* sol, int* board);

int ConstraintsSudoku(int n, int m, int* ind, double* val, GRBmodel *model);
int ILP(int n, int m, int* board);
int LPSolveCell(int location, int n, int m, int* board, float* legal_options);
int LPSolver(int n, int m,float threshold, int* board, struct Node* ctrl_z, struct Node* ctrl_z_current);
int LP(int n, int m, double* sol, int* board);


#endif /* ALGORITHEM_H_ */
