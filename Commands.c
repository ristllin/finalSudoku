/*
 * Commands.c
 *
 *  Created on: Mar 16, 2019
 *      Author: shahare
 */

void execute(int* board, int* user_command, char* user_path, int m, int n, int* mark_errors,int* ctrl_z,int* state, int* ctrl_z_current){

}

void exit(){
	/*function description: Terminates the program.
	 * args:
	 * return:
	 */

}

void set(int x, int y, int z, int* state, int* ctrl_z, int* ctrl_z_current){
	/*function description: sets the value of cell <x,y> to z, user may empty a cell
	 * satet: Edit, Solve (fixed cells are not updated)
	 * args: cell -> <x,y>
	 * return:
	 */
	/*set*/
	/*check if user entered erroneous value*/
	/*update ctrl_z, delete the further steps after current one*/

}

void autoFill(int* board, int* state){
	/*function description: Automatically fill "obvious" values – cells which contain a single legal value.
	 * state: solve
	 * args:
	 * return:
	 */

}

void markErrors(int x, int* mark_errors, int* state){
	/*function description: set the mark_errors flag to x value
	 * state: Solve
	 * args: x
	 * return: void
	 */

}

void numSolutions(int* board, int* state){
	/*function description: Print the number of solutions for the current board
	 * state: Edit, Solve
	 * args:
	 * return:
	 */

}

void generate(int x, int y, int* board){
	/* function description: Generates a puzzle by randomly filling X empty cells with legal values,
running ILP to solve the board, and then clearing all but Y random cells.
	 * state: Edit
	 * args: x --> number of cells to fill, y --> number of cells to clear
	 * return: void
	 */
	/* check number of empty cells */
	/* fill x randomly selected cells with legal values */
	/* if there is no legal value --> reset, and try up to 1000 rounds */
	/* choose y sells and clear it */
	/* if there is no legal value --> reset, and try up to 1000 rounds */

}

void validate(int* board, int* state){
	/*function description:The command prints whether the board is found to be solvable, or not using ILP
	 * states: Solve, Edit
	 * args:
	 * return:void
	 */
	/*check state*/
	/*validate using ILP*/
	/*print*/

}

void guess(float x, int* state, int* board){
	/*function description: fills all cell values with a score of X or greater usong LP. If several
values hold for the same cell, randomly choose one according to the score 	 *
	 * state: Solve
	 * args: x --> lower boundary of score
	 * return: void
	 */

}

void reset(int* state, int* board, int* ctrl_z, int* ctrl_z_current){
	/* function description: Undo all moves, reverting the board to its original loaded state
	 * state: Solve, Edit
	 * args:
	 * return: void
	 */

}

void guess_hint(int x, int* state, int* board){
	/* function description: Show a guess to the user for a single cell X,Y using LP and print suggested value
	 * state: Solve
	 * args: x --> lower boundary of score
	 * return: void
	 */

}

void hint(int x, int y, int* board, int* state){
	/*function description: Give a hint to the user by showing the solution of a single cell X,Y
	 * and print the value of cell <X,Y> found by the ILP solution.
	 * state: solve
	 * args: <x,y> cell location
	 * return:
	 */


}

void undo(int* board, int* state){
	/*function description: Undo previous moves done by the user
	 * states: Edit, Solve
	 * args:
	 * return:
	 */
	/* set to board to previous state */
	/* set pointer in the list */
	/* no moves to undo --> error */
	/* print change */

}

void redo(int* board, int* state){
	/*function description: Redo a move previously undone by the user.
	 * states: Edit, Solve
	 * args:
	 * return: void
	 */
	/* set to board to next state */
	/* set pointer in the list */
	/* no moves to redo --> error */
	/* print change */

}

void save(char* X, int* board, int* state){
	/*function description: Saves the current game board to the specified file
	 * states: Edit, Solve
	 * args: X --> file's path
	 * return:
	 */

	/*check mode*/
	/* edit - do not save erroneous files and boards without solution*/
	/* edit - mark cells containing values as fixed */

}

void toInit(){
	/*function description:
	 * args:
	 * return:
	 */

}

void toSolve(char* x, int* state, int* board){
	/*function description: change state to 'Solve' mode, and set board from file
	 * args: x --> file path
	 * return: void
	 */

}

void toEdit(char* x, int* state, int* board){
	/*function description: change state to 'Edit' mode, and set board from file or to empty board if the file path is empty
	 * args: x --> file path
	 * return: void
	 */

}

