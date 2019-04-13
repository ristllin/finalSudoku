/*
 * Constants.c
 *
 *  Created on: Mar 16, 2019
 *      Author: Roy Darnell
 */

const char* OPENNING = "'-_-=Welcome to SudokuFun=-_-'";
const char* INVALIDCOMMANDERROR = "No such command exists";
const char* EXCESSPARAMSERROR = "Too many parameters were entered";
const char* MISSINGPARAMSERROR = "Missing parameters"; /*make for each function seperate error?*/
const char* FIRSTPARAMETERERROR = "First parameter out of range or incorrect, parameter should be between 1 and "; /*add after message max range*/
const char* SECONDPARAMETERERROR = "Second parameter out of range or incorrect, parameter should be between 1 and "; /*add after message max range*/
const char* THIRDPARAMETERERROR = "Third parameter out of range or incorrect, parameter should be between 1 and "; /*add after message max range*/
const char* FIRSTPARAMILEGALERROR = "First parameter - illegal value for current board";
const char* SECONDPARAMILEGALERROR = "Second parameter - illegal value for current board";
const char* THIRDPARAMILEGALERROR = "Third parameter - illegal value for current board";
const char* TOOMANYLINESERROR = "Too many lines, Please enter one line at a time";
const char* ILLEGALSAVEERROR = "Can't save erroneous board in edit mode, please fix board and try again. Didn't save board";
const char* FIXEDCELLERROR = "you can't set fixed cells";
const char* WRONGSTATEERROR = "Function unavailable in current state";
const char* INVALIDBOARDERROR = "Board is invalid for command"; /*e.g. erroneous for auto-fill*/
const char* EXECUTIONERROR = "Command finished unsuccessfully"; /*e.g. save command failed to save*/
const char* COMMANDLENGTHERROR = "Invalid command length, please enter a command under 256 chars";
const char* WINNING = "Horray! well done, you won!";
