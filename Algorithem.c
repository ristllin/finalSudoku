/*
 * Algorithem.c
 *
 *  Created on: Mar 16, 2019
 *      Author: Roy Darnell
 */
#include "AuxFunctions.h"
#include <stdlib.h>
#include <stdio.h>
#include "gurobi_c.h"
#include <string.h>

//int recursiveEBA(int n, int m, int* board, int starting_point);
//int LP(int n, int m, double* sol, int* board);

int EBA(int n,int m,int* board){
	int rslt = -1;
	/* EBA - exhaustive backtracking algorithm, runs over every legal value for every empty cell (by index)
	 *  args: current board
	 *  return: number of correct solutions from current state (doesn't change given board)
	 * */
	int *temp_board; const int N = n*m; int i;
	printf("debug: EBA() called\n");
	printf("with: n:%d,m:%d,board:%d,board(addr):%d\n",n,m,board,&board); //debug
	temp_board = calloc(N*N*2,sizeof(int));
	copyBoard(board,temp_board,N); /*copy board to temp_board*/
	for (i=0;i<N*N;i++){ /*each existing value in board, fix in temp_board*/
		if (board[i*2] != 0){
			temp_board[i*2+1] = 1;
		}
	}
	rslt = recursiveEBA(n,m,temp_board,0); /*send to recursive EBA starting from 0*/
	free(temp_board);
	return rslt;
}

int recursiveEBA(int n, int m, int* board, int starting_point){
	/* EBA - exhaustive backtracking algorithm, runs over every legal value for every empty cell (by index)
	 *  args: current board, starting point - actual place (including fixed\unfixed cells) on board
	 *  return: number of correct solutions from current state (doesn't change given board)
	 * */
	const int N = n*m; int board_state,fixed = -1; int* legal_options; int rslt,i,value = 0;
	rslt = 0;
//	printf("debug: recursiveEBA() called\n");
//	printf("with: n:%d,m:%d,board:%d,starting point:%d\n",n,m,board,starting_point);
//	printBoard(board,n,m,2,1);
	legal_options = calloc(N,sizeof(int));
	/*if board is legaly finished return 1*/
	board_state = isFinished(n,m,board);
	switch(board_state){
		case(0):
			free(legal_options);
			return 0; /*if board has illegal cell - return 0*/
			break;
		case(1):
			free(legal_options);
			return 1; /*if board is finished - return 1*/
			break;
	}
	/*board isn't finished*/
	deleteUnfixedFromPoint(n,m,board,starting_point);
	fixed = board[starting_point + 1];
	while (fixed != 0 && starting_point < N*N*2){ /*find next unfixed cell and set starting point to it*/
		starting_point += 2;
		fixed = board[starting_point + 1];
	}
//	printf("starting point: x:%d,y:%d\n",xFromLocation(N,starting_point),yFromLocation(N,starting_point));
	if (optionsForLocation(n,m,xFromLocation(N,starting_point),yFromLocation(N,starting_point),board,legal_options) == 0){return 0;}//check next unfixed cell's options
	for (i=0;i<N;i++){/*for each option fill cell with one of the values and call recuresively*/
		if (legal_options[i] == 1){
			board[starting_point] = i+1;//
			rslt += recursiveEBA(n, m, board, starting_point+2);/*add to rslt variable all options that returned with value*/
		}
	}
	free(legal_options);
//	printf("debug: EBA rslt: %d\n",rslt);
	return rslt;
}
//
//int ConstraintsSudoku(int n, int m, int* ind, double* val, GRBmodel *model){
//	/* the function adds to model all the constraints of Sudoku game
//	 * return 0 --> error, 1---> success
//	 */
//	/* First constraint: Each cell gets a value */
//
//		  /* variables xij0...xij(N-1) (0,1,..,N-1)
//		  ind[0] =  i*N*N + j*N + 0; ind[1] = i*N*N + j*N + 1; ...; ind[2] =  i*N*N + j*N + N-1;
//		  /* coefficients (according to variables in "ind")
//		  val[0] = 1; val[1] = 1;... ;val[N-1] = 1;*/
//	int i, j, v, error, ig, jg, count;
//	GRBenv   *env   = NULL;
//	const int N= n*m;
//	  for (i = 0; i < N; i++) {
//			  for (j = 0; j < N; j++) {
//				  for (v = 0; v < N; v++) {
//					  ind[v] = i*N*N + j*N + v; /*ind[v] -> variable's index*/
//					  val[v] = 1.0; /*vals[v] -> coefficients */
//				  }
//				  /* add constraint to model - note size 3 + operator GRB_LESS_EQUAL */
//				  error = GRBaddconstr(model, N, ind, val, GRB_EQUAL, 1.0, NULL);
//				  if (error) {
//					  printf("ERROR %d Each cell gets a value GRBaddconstr(): %s\n", error, GRBgeterrormsg(env));
//					  return 1;
//				  }
//			  }
//		  }
//
//
//		  /* Second constraint: Each value must appear once in each row */
//		  for (v = 0; v < N; v++) {
//		      for (j = 0; j < N; j++) {
//		        for (i = 0; i < N; i++) {
//		          ind[i] = i*N*N + j*N + v;
//		          val[i] = 1.0;
//		        }
//
//		        error = GRBaddconstr(model, N, ind, val, GRB_EQUAL, 1.0, NULL);
//		        if (error) {
//		        		  printf("ERROR %d Each value must appear once in each row GRBaddconstr(): %s\n", error, GRBgeterrormsg(env));
//		        		  return 1;
//		        	  }
//		      }
//		    }
//
//		  /* Third constraint: Each value must appear once in each column */
//		  for (v = 0; v < N; v++) {
//		      for (i = 0; i < N; i++) {
//		        for (j = 0; j < N; j++) {
//		          ind[j] = i*N*N + j*N + v;
//		          val[j] = 1.0;
//		        }
//
//		        error = GRBaddconstr(model, N, ind, val, GRB_EQUAL, 1.0, NULL);
//		        if (error) {
//						  printf("ERROR %d Each value must appear once in each column GRBaddconstr(): %s\n", error, GRBgeterrormsg(env));
//						  return 1;
//					  }
//		      }
//		    }
//
//		    /* Forth constraint: Each value must appear once in each subgrid */
//
//		    for (v = 0; v < N; v++) {
//		      for (ig = 0; ig < n; ig++) { //n-> block length
//		        for (jg = 0; jg < m; jg++) { // m-> block width
//		          count = 0;
//		          for (i = ig*m; i < (ig+1)*m; i++) {
//		            for (j = jg*n; j < (jg+1)*n; j++) {
//		              ind[count] = i*N*N + j*N + v;
//		              val[count] = 1.0;
//		              count++;
//		            }
//		          }
//
//		          error = GRBaddconstr(model, N, ind, val, GRB_EQUAL, 1.0, NULL);
//		          if (error) {
//						  printf("ERROR %d Each value must appear once in each subgrid GRBaddconstr(): %s\n", error, GRBgeterrormsg(env));
//						  return 1;
//					  }
//		        }
//		      }
//		    }
//		    return 0;
//}
//
//int ILP(int n, int m, int* board){
//	/* ILP - Integer Linear Programming, used by validate, generate and hint functions, uses gorubi to solve the board
//	*  args: soduko board
//	*  return: soduko board (changes given board), 0 -> no errors, 1 -> errors
//	* */
//	GRBenv   *env   = NULL;
//	  GRBmodel *model = NULL;
//	  int       error = 0;
//	  const int N = n*m;
//	  double*	sol = (double*)calloc(N*N*N,sizeof(double)); //save sol values
//	  int*		ind = (int*)calloc(N,sizeof(int)); //Variable's index
//	  double*   val = (double*)calloc(N,sizeof(int)); // Variable's Coefficients
//	  double*	lb = (double*)calloc(N*N*N,sizeof(double)); // lb = lowerbound
//	  char*		vtype = (char*)calloc(N*N*N,sizeof(char)); // variables types
//	  //char**	names = (char**)calloc(N*N*N,sizeof(char*)); // pointer to the name of variable
//	  //char*		namestorage= (char*)calloc(10*N*N*N,sizeof(char)); // names storage
//	  //char*		cursor;
//	  double 	objval;
//	  int       i, j, v, ig, jg, count, location;
//	  int       optimstatus;
//
//	  /* Create an empty model */
//	  //cursor = namestorage;
//	      for (i = 0; i < N; i++) {
//	          for (j = 0; j < N; j++) {
//	        	  location = (i + j*N)*2;
//	              for (v = 0; v < N; v++) {
//	                  if (board[location] == v) {
//	                      lb[i*N*N+j*N+v] = 1; /*LB = lowerbound*/
//	                  }
//	                  else {
//	                      lb[i*N*N+j*N+v] = 0;
//	                  }
//	                  //names[i*N*N+j*N+v] = cursor;
//	                  vtype[i*N*N+j*N+v] = GRB_BINARY; //change to GRB_CONTINUOUS in LP
//	                  //sprintf(names[i*N*N+j*N+v], "x[%d,%d,%d]", i, j, v+1);
//	                  //cursor += strlen(names[i*N*N+j*N+v]) + 1;
//	              }
//	          }
//	      }
//
//
//	  /* Create environment - log file is sudoku.log */
//	  error = GRBloadenv(&env, "sudokuILP.log");
//	  if (error) {
//		  printf("ERROR %d GRBloadenv(): %s\n", error, GRBgeterrormsg(env));
//		  return 0;
//	  }
//
//	  error = GRBsetintparam(env, GRB_INT_PAR_LOGTOCONSOLE, 0);
//	  if (error) {
//		  printf("ERROR %d GRBsetintattr(): %s\n", error, GRBgeterrormsg(env));
//		  return 0;
//	  }
//
//	  /* Create new model named "sudoku" */
//	  error = GRBnewmodel(env, &model, "sudoku", N*N*N, NULL, lb, NULL, vtype, NULL);
//	  if (error) {
//		  printf("ERROR %d GRBnewmodel(): %s\n", error, GRBgeterrormsg(env));
//		  return 0;
//	  }
//
//
//	  /* ADD constraint */
//	  error = ConstraintsSudoku(n,m,ind,val,model);
//	  if(error){
//		  return 0;
//	  }
//
//
//	  /* Optimize model - need to call this before calculation */
//	  error = GRBoptimize(model);
//	  if (error) {
//		  printf("ERROR %d GRBoptimize(): %s\n", error, GRBgeterrormsg(env));
//		  return 0;
//	  }
//
//	  /* Write model to 'sudoku.lp' - this is not necessary but very helpful */
//	  error = GRBwrite(model, "sudokuILP.lp");
//	  if (error) {
//		  printf("ERROR %d GRBwrite(): %s\n", error, GRBgeterrormsg(env));
//		  return 0;
//	  }
//
//	  /* Get solution information */
//
//	  error = GRBgetintattr(model, GRB_INT_ATTR_STATUS, &optimstatus);
//	  if (error) {
//		  printf("ERROR %d GRBgetintattr(): %s\n", error, GRBgeterrormsg(env));
//		  return 0;
//	  }
//
//	  /* get the objective -- the optimal result of the function */
//	  error = GRBgetdblattr(model, GRB_DBL_ATTR_OBJVAL, &objval);
//	  if (error) {
//		  printf("ERROR %d GRBgettdblattr(): %s\n", error, GRBgeterrormsg(env));
//		  return 0;
//	  }
//	  /* solution found */
//	  if (optimstatus == GRB_OPTIMAL) {
//	     }
//	  /* no solution found */
//	     else if (optimstatus == GRB_INF_OR_UNBD) {
//	    	 printf("ERROR: Model is infeasible or unbounded\n");
//	    	 return 0;
//	     }
//	  /* error or calculation stopped */
//	     else {
//	    	 printf("ERROR: Optimization was stopped early\n");
//	    	 return 0;
//	     }
//
//	  /* get the solution - the assignment to each variable */
//	  error = GRBgetdblattrarray(model, GRB_DBL_ATTR_X, 0, N*N*N, sol);
//	  if (error) {
//		  printf("ERROR %d GRBgetdblattrarray(): %s\n", error, GRBgeterrormsg(env));
//		  return 0;
//	  }
//
//	  /* update board */
//	  for (i = 0; i < N; i++) {
//	  	          for (j = 0; j < N; j++) {
//	  	        	  location = (i + j*N)*2;
//	  	              for (v = 0; v < N; v++) {
//	  	                  if (sol[i*N*N+j*N+v] == 1) {
//	  	                      board[location] = v+1;
//	  	                  }
//	  	                  else {
//	  	                	  board[location] = 0;
//	  	                  }
//	  	              }
//	  	          }
//	  	      }
//
//	  /* make sure board is finished */
//	  error = isFinished(n,m,board);
//	  if(error!=1) //1==win
//	  {
//		  printf("ERROR: %d, Finish optimization, but board is unsolved.\n", error);
//		  return 0;
//	  }
//
//	  /* IMPORTANT !!! - Free model and environment */
//	  GRBfreemodel(model);
//	  GRBfreeenv(env);
//	  free(ind);
//	  free(lb);
//	  free(vtype);
//	 // free(names);
//	 // free(namestorage);
//	  free(sol);
//	  free(val);
//
//	  return 1;
//}
//
//int LPSolveCell(int location, int n, int m, float threshold, int* board, float* legal_options){
//	/* Linear programming algorithm, Used by guess and guessHint functions. solves using gorubi solver module
//	*  args: gets board to solve, doesn't change it, builds solution on guess board
//	*  return: all possible solutions with scores higher than threshold and their scores to specific cell, 0 -> no solution to guess_board, 1 -> there is solution
//	* */
//	int success, x, y, i, sol_index;
//	const int N = n*m;
//	double*	sol = (double*)calloc(N*N*N,sizeof(double)); //save sol values
//	success = LP(n,m,sol,board);
//	if(!success){
//		return 0;
//	}
//	x = xFromLocation(N, location);
//	y = yFromLocation(N, location);
//	sol_index = N*N*x + N*y;
//	for (i=0; i<N; i++) {
//		if(sol[sol_index+i]>threshold){
//			legal_options[i*2]= i+1.0; //optional value
//			legal_options[i*2+1]= sol[sol_index+i]; //score
//	    }
//		else{
//			legal_options[i*2]= -1.0; //optional value
//			legal_options[i*2+1]= -1.0; //score
//		}
//	}
//	return 1;
//
//}
//
//int LPSolver(int n, int m,float threshold, int* board){
//	/*Linear programming algorithm, Used by guess and guessHint functions. solves using gorubi solver module
//	 *  args: gets board to solve, and threshold
//	 * return: solved board, If several values hold for the same cell, randomly choose one according to the score
//	 *
//	 */
//	const int N = n * m;
//	double*	sol = (double*)calloc(N*N*N,sizeof(double)); //save sol values
//}
//
//int LP(int n, int m, double* sol, int* board){
//	/* gets board, and fill Gurobi matrix (sol) with the solution
//		*  args: soduko board
//		*  return: 0 - > failed, 1 -> success
//		* */
//		GRBenv   *env   = NULL;
//		  GRBmodel *model = NULL;
//		  int       error = 0;
//		  const int N = n*m;
//		  int*		ind = (int*)calloc(N,sizeof(int)); //Variable's index
//		  double*   val = (double*)calloc(N,sizeof(int)); // Variable's Coefficients
//		  double*	obj = (double*)calloc(N*N*N,sizeof(double)); // Coefficients for objective's variables
//		  double*	lb = (double*)calloc(N*N*N,sizeof(double)); // lb = lowerbound
//		  double*	ub = (double*)calloc(N*N*N,sizeof(double)); // ub = upperbound
//		  char*		vtype = (char*)calloc(N*N*N,sizeof(char)); // variables types
//		  //char**	names = (char**)calloc(N*N*N,sizeof(char*)); // pointer to the name of variable
//		  //char*		namestorage= (char*)calloc(10*N*N*N,sizeof(char)); // names storage
//		  //char*		cursor;
//		  double 	objval;
//		  int       i, j, v, ig, jg, count, location;
//		  int       optimstatus;
//
//		  /* Create an empty model */
//		  //cursor = namestorage;
//		      for (i = 0; i < N; i++) {
//		          for (j = 0; j < N; j++) {
//		        	  location = (i + j*N)*2;
//		              for (v = 0; v < N; v++) {
//		                  if (board[location] == v) {
//		                      lb[i*N*N+j*N+v] = 1; /*LB = lowerbound*/
//		                      ub[i*N*N+j*N+v] = 1;
//		                      obj[i*N*N+j*N+v] = 1;
//		                  }
//		                  else {
//		                      lb[i*N*N+j*N+v] = 0;
//		                      ub[i*N*N+j*N+v] = 1;
//		                      obj[i*N*N+j*N+v] = 0;
//		                  }
//		                  //names[i*N*N+j*N+v] = cursor;
//		                  vtype[i*N*N+j*N+v] = GRB_CONTINUOUS; //change to GRB_CONTINUOUS in LP
//		                  //sprintf(names[i*N*N+j*N+v], "x[%d,%d,%d]", i, j, v+1);
//		                  //cursor += strlen(names[i*N*N+j*N+v]) + 1;
//		              }
//		          }
//		      }
//
//
//		  /* Create environment - log file is sudokuLP.log */
//		  error = GRBloadenv(&env, "sudokuLP.log");
//		  if (error) {
//			  printf("ERROR %d GRBloadenv(): %s\n", error, GRBgeterrormsg(env));
//			  return 0;
//		  }
//
//		  error = GRBsetintparam(env, GRB_INT_PAR_LOGTOCONSOLE, 0);
//		  if (error) {
//			  printf("ERROR %d GRBsetintattr(): %s\n", error, GRBgeterrormsg(env));
//			  return 0;
//		  }
//
//		  /* Create new model named "sudokuLP", optional -> add names */
//		  error = GRBnewmodel(env, &model, "sudokuLP", N*N*N, obj, lb, ub, vtype, NULL);
//		  if (error) {
//			  printf("ERROR %d GRBnewmodel(): %s\n", error, GRBgeterrormsg(env));
//			  return 0;
//		  }
//
//
//		  /* ADD constraint */
//		  	  error = ConstraintsSudoku(n,m,ind,val,model);
//		  	  if(error){
//		  		  return 0;
//		  	  }
//
//		  /* Optimize model - need to call this before calculation */
//		  error = GRBoptimize(model);
//		  if (error) {
//			  printf("ERROR %d GRBoptimize(): %s\n", error, GRBgeterrormsg(env));
//			  return 0;
//		  }
//
//		  /* Write model to 'sudoku.lp' - this is not necessary but very helpful */
//		  error = GRBwrite(model, "sudokuLP.lp");
//		  if (error) {
//			  printf("ERROR %d GRBwrite(): %s\n", error, GRBgeterrormsg(env));
//			  return 0;
//		  }
//
//		  /* Get solution information */
//
//		  error = GRBgetintattr(model, GRB_INT_ATTR_STATUS, &optimstatus);
//		  if (error) {
//			  printf("ERROR %d GRBgetintattr(): %s\n", error, GRBgeterrormsg(env));
//			  return 0;
//		  }
//
//		  /* get the objective -- the optimal result of the function */
//		  error = GRBgetdblattr(model, GRB_DBL_ATTR_OBJVAL, &objval);
//		  if (error) {
//			  printf("ERROR %d GRBgettdblattr(): %s\n", error, GRBgeterrormsg(env));
//			  return 0;
//		  }
//		  /* solution found */
//		  if (optimstatus == GRB_OPTIMAL) {
//		     }
//		  		  /* no solution found */
//		     else if (optimstatus == GRB_INF_OR_UNBD) {
//		    	 printf("ERROR: Model is infeasible or unbounded\n");
//		    	 return 0;
//		     }
//		  /* error or calculation stopped */
//		     else {
//		    	 printf("ERROR: Optimization was stopped early\n");
//		    	 return 0;
//		     }
//
//		  /* get the solution - the assignment to each variable */
//		  error = GRBgetdblattrarray(model, GRB_DBL_ATTR_X, 0, N*N*N, sol);
//		  if (error) {
//			  printf("ERROR %d GRBgetdblattrarray(): %s\n", error, GRBgeterrormsg(env));
//			  return 0;
//		  }
//
//
//		  /* IMPORTANT !!! - Free model and environment */
//		  GRBfreemodel(model);
//		  GRBfreeenv(env);
//		  free(ind);
//		  free(lb);
//		  free(vtype);
//		  free(obj);
//		  free(val);
//
//		  return 1;
//
//}
