/*
 * Constants.c
 *
 *  Created on: Mar 16, 2019
 *      Author: Roy Darnell
 */
const int MAXBUFFERSIZE = 256;
const int DEBUG = 1;
const char* OPENNING = "'-_-=Welcome to SudokuFun=-_-'";
const char* ENTERCOMMAND = "Please enter a command: ";
const char* TOOMANYCHARACTERS = " too many characters were entered in a single line \n";
const char* INVALIDCOMMANDERROR = "No such command exists\n";
const char* EXCESSPARAMSERROR = "Too many parameters were entered \n";
const char* MISSINGPARAMSERROR = "Missing parameters \n"; /*make for each function seperate error?*/
const char* FIRSTPARAMETERERROR = "First parameter out of range or incorrect, parameter should be between 1 and "; /*add after message max range*/
const char* SECONDPARAMETERERROR = "Second parameter out of range or incorrect, parameter should be between 1 and "; /*add after message max range*/
const char* THIRDPARAMETERERROR = "Third parameter out of range or incorrect, parameter should be between 1 and "; /*add after message max range*/
const char* FIRSTPARAMILEGALERROR = "First parameter - illegal value for current board";
const char* SECONDPARAMILEGALERROR = "Second parameter - illegal value for current board";
const char* THIRDPARAMILEGALERROR = "Third parameter - illegal value for current board";
const char* TOOMANYLINESERROR = "Too many lines, Please enter one line at a time";
const char* ILLEGALSAVEERROR = "Can't save erroneous board in edit mode, please fix board and try again. Didn't save board";
const char* FIXEDCELLERROR = "you can't set fixed cells";
const char* FILLEDCELLERROR = "you can't get hints for cells with values";
const char* WRONGSTATEERROR = "Function unavailable in current state \n";
const char* INVALIDBOARDERROR = "Board is erroneous, can not complete command"; /*e.g. erroneous for auto-fill*/
const char* EXECUTIONERROR = "Command finished unsuccessfully"; /*e.g. save command failed to save*/
const char* COMMANDLENGTHERROR = "Invalid command length, please enter a command under 256 chars";
const char* UNSOLVEDBOARD = "The board is not solvable";
const char* COMMANDSOLVE = "solve";
const char* COMMANDEDIT = "edit";
const char* COMMANDMARKERRORS = "mark_errors";
const char* COMMANDPRINTBOARD = "print_board";
const char* COMMANDSET = "set";
const char* COMMANDVALIDATE = "validate";
const char* COMMANDGUESS = "guess";
const char* COMMANDGENERATE = "generate";
const char* COMMANDUNDO = "undo";
const char* COMMANDREDO = "redo";
const char* COMMANDSAVE = "save";
const char* COMMANDHINT = "hint";
const char* COMMANDGUESSHINT = "guess_hint";
const char* COMMANDNUMSOLUTIONS = "num_solutions";
const char* COMMANDAUTOFILL = "autofill";
const char* COMMANDRESET = "reset";
const char* COMMANDEXIT = "exit";
const char* NOTINT = "The given string did not consist solely of digit characters. \n";
const char* FIRSTPARAMETERERRORGUESS= "First parameter out of range or incorrect, parameter should be between 0 and 1 \n";
const char* FIRSTPARAMETERERRORMARKERRORS= "First parameter out of range or incorrect, parameter should be 0 or 1 \n";
const char* XSIZEISTOOLARGE = "The board contains less empty cells then the provided number \n";
const char* WINNING = "Horray! well done, you won!";
const char* CURRUPTFILEFORMAT = "Invalid file format";
const char* INVALIDFILEPATH = "Invalid File Path";
const char* NOMOREMOVES = "No more moves were previously made";
const char* READINGFAILED = "Failed to read from given path";
const char* SAVINGFAILED = "Saving file - Failed";
const char* LPFAILED = "LP Algorithm - Failed";
const char* SETFAILED = "failed to set cell";
