/*
 * Algorithem.c
 *
 *  Created on: Mar 16, 2019
 *      Author: Roy Darnell
 */
#include "AuxFunctions.h"
#include <stdlib.h>
#include <stdio.h>
//#include "gurobi_c.h"
#include <string.h>
#include "Constants.h"
#include "List.h"
#include "Commands.h"
#include "IOCommands.h"

int recursiveEBA(int n, int m, int* board, int starting_point);
int LP(int n, int m, double* sol, int* board);
int ConstraintsSudoku(int n, int m, int* ind, double* val, GRBmodel *model){return 1;}
int ILP(int n, int m, int* board){return 1;}
int LPSolveCell(int location, int n, int m, int* board, float* legal_options){return 1;};
int LPSolver(int n, int m,float threshold, int* board, struct Node* ctrl_z, struct Node** ctrl_z_current, int* state){return 1;};
int LP(int n, int m, double* sol, int* board){return 1;}


int EBA(int n,int m,int* board){
	int rslt = -1;
	/* EBA - exhaustive backtracking algorithm, runs over every legal value for every empty cell (by index)
	 *  args: current board
	 *  return: number of correct solutions from current state (doesn't change given board)
	 * */
	int *fixed_board; const int N = n*m; int i;
	fixed_board = calloc(N*N*2,sizeof(int));
	copyBoard(board,fixed_board,N); /*copy board to temp_board*/
	for (i=0;i<N*N;i++){ /*each existing value in board, fix in temp_board*/
		if (board[i*2] != 0){
			fixed_board[i*2+1] = 1;
		}
	}
	if (DEBUG){printf("original:\n");}
	if (DEBUG){printBoard(board,n,m,1);}
	if (DEBUG){printf("fixed_board:\n");}
	if (DEBUG){printBoard(fixed_board,n,m,1);}
	rslt = recursiveEBA(n,m,fixed_board,0); /*send to recursive EBA starting from 0*/
	free(fixed_board);
	return rslt;
}

int recursiveEBA(int n, int m, int* board, int starting_point){
	/* EBA - exhaustive backtracking algorithm, runs over every legal value for every empty cell (by index)
	 *  args: current board, starting point - actual place (including fixed\unfixed cells) on board
	 *  return: number of correct solutions from current state (doesn't change given board)
	 * */
	const int N = n*m;
	int board_state,fixed;
	int* legal_options;
	int rslt,i;
	rslt = 0;
	fixed = -1;
	legal_options = calloc(N,sizeof(int));
	board_state = isFinished(n,m,board);
	switch(board_state){
		case(0):
			free(legal_options);
			return 0; /*if board has illegal cell - return 0*/
			break;
		case(1):
			free(legal_options);
			if (DEBUG){printf("<<<is a valid solution!!>>>\n");}
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
	if (optionsForLocation(n,m,xFromLocation(N,starting_point),yFromLocation(N,starting_point),board,legal_options) == 0){
		if (DEBUG){printf("<<mistake board:>>\n");printBoard(board,n,m,1);}
		return 0; /*no legal options for location - mistake was made*/
	}
/*	check next unfixed cell's options*/
	for (i=0;i<N;i++){/*for each option fill cell with one of the values and call recuresively*/
		if (legal_options[i] == 1){
			deleteUnfixedFromPoint(n,m,board,starting_point);
			if (DEBUG && (starting_point < 0 || starting_point > N*N*2)){printf("<<<<segmentation error!!!>>>");}
			board[starting_point] = i+1;
			rslt += recursiveEBA(n, m, board, starting_point+2);/*add to rslt variable all options that returned with value*/
		}
	}
	free(legal_options);
	return rslt;
}

//
//int ConstraintsSudoku(int n, int m, int* ind, double* val, GRBmodel *model){
//
///*
//	 the function adds to model all the constraints of Sudoku game
//	 * return 0 --> error, 1---> success
//	 First constraint: Each cell gets a value
//		   variables xij0...xij(N-1) (0,1,..,N-1)
//		  ind[0] =  i*N*N + j*N + 0; ind[1] = i*N*N + j*N + 1; ...; ind[2] =  i*N*N + j*N + N-1;
//		  / coefficients (according to variables in "ind")
//		  val[0] = 1; val[1] = 1;... ;val[N-1] = 1;
//*/
//	int i, j, v, error, ig, jg, count;
//	GRBenv   *env   = NULL;
//	const int N= n*m;
//	  for (i = 0; i < N; i++) {
//			  for (j = 0; j < N; j++) {
//				  for (v = 0; v < N; v++) {
//					  ind[v] = i*N*N + j*N + v;
//					  val[v] = 1.0;
//				  }
//				  /* add constraint to model - note size 3 + operator GRB_LESS_EQUAL*/
//				  error = GRBaddconstr(model, N, ind, val, GRB_EQUAL, 1.0, NULL);
//				  if (error) {
//					  printf("ERROR %d Each cell gets a value GRBaddconstr(): %s\n", error, GRBgeterrormsg(env));
//					  return 1;
//				  }
//			  }
//		  }
//
//
//		  /* Second constraint: Each value must appear once in each row*/
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
//		/*   Third constraint: Each value must appear once in each column*/
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
//		   /*  Forth constraint: Each value must appear once in each subgrid*/
//
//		    for (v = 0; v < N; v++) {
//		      for (ig = 0; ig < n; ig++) { /*n-> block length*/
//		        for (jg = 0; jg < m; jg++) { /* m-> block width*/
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
//
//
//int randomWeightedNumber(double* list, int length){
///*	 return random v out of list with values and their weights. return -1 in case of an error;*/
//	double sum_of_weight, rnd;
//	int location,i;
//	sum_of_weight = 0.0;
//	for(i=0; i<length; i++) {
//		location = i*2+1;
//	   sum_of_weight += list[location];
//	}
//	rnd = (double)rand()/RAND_MAX* sum_of_weight;
//	for(i=0; i<length; i++) {
//		location = i*2+1;
//	  if(rnd < list[location])
//	    return (int)list[location-1];
//	  rnd -= list[location];
//	}
//	return -1;
//}
//
//
//
//int ILP(int n, int m, int* board){
///*
//	 ILP - Integer Linear Programming, used by validate, generate and hint functions, uses gorubi to solve the board
//	*  args: soduko board
//	*  return: soduko board (changes given board), 0 -> no errors, 1 -> errors
//*/
//	GRBenv   *env   = NULL;
//	  GRBmodel *model = NULL;
//
//	  const int N = n*m;
//	  double*	sol;
//	  double* val;
//	  double* lb;
//	  int* ind;
//	  char* vtype;
//	  double 	objval;
//	  int       i, j, v, location, error;
//	  int       optimstatus;
//		if (DEBUG){
//			printf(">>debug: ILP() called\n");
//		}
//		if (DEBUG){
//			printf("with: n:%d,m:%d\n",n,m);}
//
//	  sol = (double*)calloc(N*N*N,sizeof(double)); /*save sol values*/
//	  ind = (int*)calloc(N,sizeof(int)); /*Variable's index*/
//	  val = (double*)calloc(N,sizeof(double)); /*Variable's Coefficients*/
//	  lb = (double*)calloc(N*N*N,sizeof(double)); /* lb = lowerbound*/
//	  vtype = (char*)calloc(N*N*N,sizeof(char)); /* variables types*/
//	  char**	names = (char**)calloc(N*N*N,sizeof(char*));
//	  char*		namestorage= (char*)calloc(10*N*N*N,sizeof(char));
//	  char*		cursor;
//
//	  error = 0;
//
//	  cursor = namestorage;
//	      for (i = 0; i < N; i++) {
//	          for (j = 0; j < N; j++) {
//	        	  location = (i + j*N)*2;
//	        	  board[location] = board[location]-1;
//	              for (v = 0; v < N; v++) {
//	                  if (board[location] == v) {
//	                      lb[i*N*N+j*N+v] = 1; /*LB = lowerbound*/
//	                  }
//	                  else {
//	                      lb[i*N*N+j*N+v] = 0;
//	                  }
//	                  names[i*N*N+j*N+v] = cursor;
//	                  vtype[i*N*N+j*N+v] = GRB_BINARY;
//	                  sprintf(names[i*N*N+j*N+v], "x[%d,%d,%d]", i, j, v+1);
//	                  cursor += strlen(names[i*N*N+j*N+v]) + 1;
//	              }
//	          }
//	      }
//
//
//	/*   Create environment - log file is sudoku.log*/
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
//	/*   Create new model named "sudoku"*/
//	  error = GRBnewmodel(env, &model, "sudoku", N*N*N, NULL, lb, NULL, vtype, names);
//	  if (error) {
//		  printf("ERROR %d GRBnewmodel(): %s\n", error, GRBgeterrormsg(env));
//		  return 0;
//	  }
//
//
//	 /*  ADD constraint*/
//	  error = ConstraintsSudoku(n,m,ind,val,model);
//	  if(error){
//		  return 0;
//	  }
//
//
//	 /*  Optimize model - need to call this before calculation*/
//	  error = GRBoptimize(model);
//	  if (error) {
//		  printf("ERROR %d GRBoptimize(): %s\n", error, GRBgeterrormsg(env));
//		  return 0;
//	  }
//
//	  /* Write model to 'sudoku.lp' - this is not necessary but very helpful*/
//	  error = GRBwrite(model, "sudokuILP.lp");
//	  if (error) {
//		  printf("ERROR %d GRBwrite(): %s\n", error, GRBgeterrormsg(env));
//		  return 0;
//	  }
//
//	  /* Get solution information*/
//
//	  error = GRBgetintattr(model, GRB_INT_ATTR_STATUS, &optimstatus);
//	  if (error) {
//		  printf("ERROR %d GRBgetintattr(): %s\n", error, GRBgeterrormsg(env));
//		  return 0;
//	  }
//
//	   /*get the objective -- the optimal result of the function*/
//	  error = GRBgetdblattr(model, GRB_DBL_ATTR_OBJVAL, &objval);
//	  if (error) {
//		  printf("ERROR %d GRBgettdblattr(): %s\n", error, GRBgeterrormsg(env));
//		  return 0;
//	  }
//	/*   solution found*/
//	  if (optimstatus == GRB_OPTIMAL) {
//	     }
//	   /*no solution found*/
//	     else if (optimstatus == GRB_INF_OR_UNBD) {
//	    	 printf("ERROR: Model is infeasible or unbounded\n");
//	    	 return 0;
//	     }
//	   /*error or calculation stopped*/
//	     else {
//	    	 printf("ERROR: Optimization was stopped early\n");
//	    	 return 0;
//	     }
//
//	 /*  get the solution - the assignment to each variable*/
//	  error = GRBgetdblattrarray(model, GRB_DBL_ATTR_X, 0, N*N*N, sol);
//	  if (error) {
//		  printf("ERROR %d GRBgetdblattrarray(): %s\n", error, GRBgeterrormsg(env));
//		  return 0;
//	  }
//
///*	   update board*/
//	  for (i = 0; i < N; i++) {
//	  	          for (j = 0; j < N; j++) {
//	  	        	  location = (i + j*N)*2;
//	  	              for (v = 0; v < N; v++) {
//	  	                  if ((int)sol[i*N*N+j*N+v] == 1) {
//	  	                      board[location] = v+1;
//	  	                  }
//	  	                  else {
//	  	                	  board[location] = 0;
//	  	                  }
//	  	              }
//	  	          }
//	  	      }
//
//	 /*  make sure board is finished*/
//	  if(DEBUG){printf("here\n");}
//	  if(DEBUG){printBoard(board,n,m,1);}
//	  error = isFinished(n,m,board);
//	  if(error!=1) /*1==win*/
//	  {
//		  printf("ERROR: %d, Finished optimization, but board is unsolved.\n", error);
//		  return 0;
//	  }
//
///*	   IMPORTANT !!! - Free model and environment*/
//	  GRBfreemodel(model);
//	  GRBfreeenv(env);
//	  free(ind);
//	  free(lb);
//	  free(vtype);
//	  free(names);
//	  free(namestorage);
//	  free(sol);
//	  free(val);
//
//	  return 1;
//}
//
//
//
//int LPSolveCell(int location, int n, int m, int* board, float* legal_options){
//	/* Linear programming algorithm, Used by guess and guessHint functions. solves using gorubi solver module
//	*  args: gets board to solve, doesn't change it, builds solution on guess board
//	*  return: all possible solutions with scores higher than 0 and their scores to specific cell, 0 -> no solution to guess_board, 1 -> there is solution
//	*/
//	int success, x, y, i, sol_index;
//	const int N = n*m;
//	double*	sol;
//	sol = (double*)calloc(N*N*N,sizeof(double));
///*	printf("Debugging: inside LPSolveCell, value of location is %d\n", board[location] );*/
//	success = LP(n,m,sol,board);
///*	success = 1;*/
//	if(!success){
//		return 0;
//	}
//	x = xFromLocation(N, location);
//	y = yFromLocation(N, location);
//	sol_index = N*N*x + N*y;
///*	printf("Debuging index is %d, sol val ",sol_index);*/
//	for (i=0; i<N; i++) {
//		if(sol[sol_index+i]>0){
//			legal_options[i*2]= i+1.0;/* optional value*/
//			legal_options[i*2+1]= sol[sol_index+i]; /*score*/
//	    }
//		else{
//			legal_options[i*2]= -1.0; /*optional value*/
//			legal_options[i*2+1]= -1.0; /*score*/
//			/*printf("value of legal op is %f", legal_options[i*2+1]);*/
//		}
//	}
//	free(sol);
//	return 1;
//
//}
//
//
//int LPSolver(int n, int m,float threshold, int* board, struct Node* ctrl_z, struct Node** ctrl_z_current, int* state){
//	/*Linear programming algorithm, Used by guess  functions. solves using gorubi solver module
//	 *  args: gets board to solve, and threshold
//	 * return: solved board, If several values hold for the same cell, randomly choose one according to the score
//	 *
//	 */
//	int success, valid_cnt, sol_index, location, i, j, v, valid, sol_value;
//	const int N=n*m;
//	double*	sol;
//	double* legal_options;
//	sol = (double*)calloc(N*N*N,sizeof(double));
//	legal_options = (double*)calloc(N*2,sizeof(double));
///*	run LP and get sol matrix */
//	success = LP(n,m,sol,board);
//	if(!success){
//			return 0;
//		}
///*	go over empty cells and fill them*/
//	valid_cnt = 0;
//		for (i = 0; i < N; i++) {
//			 for (j = 0; j < N; j++) {
//				  location = (i + j*N)*2;
//				  for (v = 0; v < N; v++) {
///*						check if score is higher than x  and*/
//					  sol_index = i*N*N+j*N+v;
//					  if (sol[sol_index] > threshold && board[location]==0) {
//						  board[location] = v+1;
//						  valid = isLegal(n,m,xFromLocation(N, location),yFromLocation(N, location),board);
//						  if(valid){
//							  legal_options[valid_cnt*2]= (float)v+1.0; /*optional value*/
//							  legal_options[valid_cnt*2+1]= sol[sol_index+v]; /*score*/
//							  valid_cnt++;
//						  }
//						  board[location]= 0;
//					  	  }
//				  	  }
///*				  choose one item randomly using weighted random*/
//				  sol_value = randomWeightedNumber(legal_options, valid_cnt);
///*				   place it on board using location;*/
//				  RemoveFollowingNodes(*ctrl_z_current); /*delete following moves if existing*/
//				  InsertAtTail(-3,0,0,ctrl_z); /*add starting marker*/
//				  *ctrl_z_current = (*ctrl_z_current)->next; /*advance current ctrl-z to new node*/
//				  if(sol_value!=-1){  /*there is an option higher than X*/
//						valid =  set(n, m, i+1, j+1, sol_value, board, ctrl_z, ctrl_z_current, state);
//						if(!valid){
//							printf("EROOR: %s\n", SETFAILED);
//							return 0;
//							}
//				  	  }
//				  InsertAtTail(-4,0,0,ctrl_z); /*add end marker*/
//				  *ctrl_z_current = (*ctrl_z_current)->next; /*advance current ctrl-z to new node*/
//			 }
//		}
//	free(sol);
//	free(legal_options);
//	return 1;
//
//}
//
//
//
//int LP(int n, int m, double* sol, int* board){
//	/* gets board, and fill Gurobi matrix (sol) with the solution
//		*  args: soduko board
//		*  return: 0 - > failed, 1 -> success
//		*  */
//
//		GRBenv   *env   = NULL;
//		GRBmodel *model = NULL;
//
//		const int N = n*m;
//		int*		ind;
//		double* 	val;
//		double*	obj;
//		double*	lb;
//		double*	ub;
//		char*		vtype;
//		double 	objval;
//		int       i, j, v, location, error;
//		int       optimstatus;
//		ind = (int*)calloc(N,sizeof(int)); /*Variable's index*/
//		val = (double*)calloc(N,sizeof(int)); /* Variable's Coefficients*/
//		obj = (double*)calloc(N*N*N,sizeof(double)); /* Coefficients for objective's variables */
//		lb = (double*)calloc(N*N*N,sizeof(double)); /* lb = lowerbound */
//		ub = (double*)calloc(N*N*N,sizeof(double)); /* ub = upperbound */
//		vtype = (char*)calloc(N*N*N,sizeof(char)); /* variables types */
//		  /*char**	names = (char**)calloc(N*N*N,sizeof(char*)); // pointer to the name of variable
//		  //char*		namestorage= (char*)calloc(10*N*N*N,sizeof(char)); // names storage
//		  //char*		cursor; */
//		  error = 0;
//
//		  /* Create an empty model
//		  //cursor = namestorage;*/
//		      for (i = 0; i < N; i++) {
//		          for (j = 0; j < N; j++) {
//		        	  location = (i + j*N)*2;
//		              for (v = 0; v < N; v++) {
//		                  if (board[location] == v) {
//		                      lb[i*N*N+j*N+v] = 1.0;
//		                      ub[i*N*N+j*N+v] = 1.0;
//		                      obj[i*N*N+j*N+v] = 1.0;
//		                  }
//		                  else {
//		                      lb[i*N*N+j*N+v] = 0.0;
//		                      ub[i*N*N+j*N+v] = 1.0;
//		                      obj[i*N*N+j*N+v] = 1.0/rand();
//		                  }
//		                  /*names[i*N*N+j*N+v] = cursor;*/
//		                  vtype[i*N*N+j*N+v] = GRB_CONTINUOUS;
//		                  /*sprintf(names[i*N*N+j*N+v], "x[%d,%d,%d]", i, j, v+1);
//		                  //cursor += strlen(names[i*N*N+j*N+v]) + 1;*/
//		              }
//		          }
//		      }
//
//
//		   /*Create environment - log file is sudokuLP.log*/
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
//		   /*Create new model named "sudokuLP", optional -> add names*/
//		  error = GRBnewmodel(env, &model, "sudokuLP", N*N*N, obj, lb, ub, vtype, NULL);
//		  if (error) {
//			  printf("ERROR %d GRBnewmodel(): %s\n", error, GRBgeterrormsg(env));
//			  return 0;
//		  }
//
//
//		   /*ADD constraint*/
//		  	  error = ConstraintsSudoku(n,m,ind,val,model);
//		  	  if(error){
//		  		  return 0;
//		  	  }
//
//		  /* Optimize model - need to call this before calculation*/
//		  error = GRBoptimize(model);
//		  if (error) {
//			  printf("ERROR %d GRBoptimize(): %s\n", error, GRBgeterrormsg(env));
//			  return 0;
//		  }
//
//		   /*Write model to 'sudoku.lp' - this is not necessary but very helpful*/
//		  error = GRBwrite(model, "sudokuLP.lp");
//		  if (error) {
//			  printf("ERROR %d GRBwrite(): %s\n", error, GRBgeterrormsg(env));
//			  return 0;
//		  }
//
//		  /* Get solution information*/
//
//		  error = GRBgetintattr(model, GRB_INT_ATTR_STATUS, &optimstatus);
//		  if (error) {
//			  printf("ERROR %d GRBgetintattr(): %s\n", error, GRBgeterrormsg(env));
//			  return 0;
//		  }
//
//		  /* get the objective -- the optimal result of the function*/
//		  error = GRBgetdblattr(model, GRB_DBL_ATTR_OBJVAL, &objval);
//		  if (error) {
//			  printf("ERROR %d GRBgettdblattr(): %s\n", error, GRBgeterrormsg(env));
//			  return 0;
//		  }
//		   /*solution found*/
//		  if (optimstatus == GRB_OPTIMAL) {
//		     }
//		  		/*   no solution found*/
//		     else if (optimstatus == GRB_INF_OR_UNBD) {
//		    	 printf("ERROR: Model is infeasible or unbounded\n");
//		    	 return 0;
//		     }
//		  /* error or calculation stopped*/
//		     else {
//		    	 printf("ERROR: Optimization was stopped early\n");
//		    	 return 0;
//		     }
//
//		   /*get the solution - the assignment to each variable*/
//		  error = GRBgetdblattrarray(model, GRB_DBL_ATTR_X, 0, N*N*N, sol);
//		  if (error) {
//			  printf("ERROR %d GRBgetdblattrarray(): %s\n", error, GRBgeterrormsg(env));
//			  return 0;
//		  }
//
//
//		   /*IMPORTANT !!! - Free model and environment*/
//		  GRBfreemodel(model);
//		  GRBfreeenv(env);
//		  free(ind);
//		  free(lb);
//		  free(ub);
//		  free(vtype);
//		  free(obj);
//		  free(val);
//
//		  return 1;
//
//}
