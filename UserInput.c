/*
 * UserInput.c
 *
 *  Created on: Mar 16, 2019
 *      Author: shahare
 */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Constants.h"

#define OK       0
#define NO_INPUT 1
#define TOO_LONG 2

//find the next space or EOF
int locationOfSpace(char* buffer){
	char ch;
	int chCnt = 0;
	ch = buffer[chCnt];
	while( ch != ' ' && ch !=EOF && ch != '\n' ){
		//printf("location of space: char is %c\n", ch);
			chCnt++;
			ch = buffer[chCnt];
	}
	return chCnt;
}

//find the next string or last character
char* setTheLocationToStartOfNextString(char* buffer){
	char ch;
	int chCnt = 0;
	ch = buffer[chCnt];
	while( ch == ' '){
			chCnt++;
			ch = buffer[chCnt];
	}
	return buffer+chCnt;
}


int numberOfParameters(char* buffer){
	char ch;
	int paramsCnt = 0;
	buffer = setTheLocationToStartOfNextString(buffer); //delete spaces
	ch = *buffer;

	while(ch !=EOF && ch != '\n' && ch!= '\0'){
			buffer = locationOfSpace(buffer)+buffer; //end of string
			paramsCnt++;
			buffer = setTheLocationToStartOfNextString(buffer); //delete spaces
			ch = *buffer;

		}
	//printf("debugging: number of params is %d\n", paramsCnt);
	return paramsCnt;
	}


int getLine (const char *prmpt, char *buff, size_t sz) {
    int ch, extra;

    // Get line with buffer overrun protection.
    if (prmpt != NULL) {
        printf ("%s", prmpt);
    }
    if (fgets (buff, sz, stdin) == NULL)
        return NO_INPUT;

    // If it was too long, there'll be no newline. In that case, we flush
    // to end of line so that excess doesn't affect the next call.
    if (buff[strlen(buff)-1] != '\n') {
        extra = 0;
        while (((ch = getchar()) != '\n') && (ch != EOF))
            extra = 1;
        return (extra == 1) ? TOO_LONG : OK;
    }

    //check if the line contains only white space
    if (numberOfParameters(buff)==0)
    	return NO_INPUT;

    // Otherwise remove newline and give string back to caller.
    //buff[strlen(buff)-1] = '\0';
    return OK;
}



void userInput(int* board, int m,int n,int state, int* user_command, char* user_path, float* user_threshold){
	/*Implementation limitations:
	 * 	- Max 256 chars
	 * - Max 1 line
	 * - Parameters - command correlation (e.g. set gets exactly 3 params)
	 * - Command - state correlation
	 * - Parameters range
	 * - Follow error hierarchy according to implementation doc.
	 * Otherwise returns relevant error*/
	/*initiate variables*/

	char    input[MAXBUFFERSIZE]; /* sufficient to handle one line */
	int     invalid_command = 1; /* the command was valid */
	int     command_flag = 0;
	const int N = m*n;
	/*get user input*/
	while(invalid_command){ /* run until the command is valid */
		command_flag = getLine (ENTERCOMMAND, input, sizeof(input));
		 if (command_flag == NO_INPUT) {
		        // Extra NL since my system doesn't output that on EOF.
		        continue;
		    }

		    if (command_flag == TOO_LONG) {
		        printf ("Error: %s\n", TOOMANYCHARACTERS);
		        continue;
		    }

		//printf ("debugging [%s]\n", input);

		/*split to variables (validate amount)*/
		/*Get command name*/
		char* buffer = input;
//		printf("debugging: name of command:%s\n", command_name);
		buffer = setTheLocationToStartOfNextString(buffer);
		//printf("debugging: %c\n", *buffer);
		char command_name[MAXBUFFERSIZE];
		strcpy(command_name, buffer);

		int locationOfSpcae = locationOfSpace(buffer);
		command_name[locationOfSpcae]= '\0';
		//printf("debugging: name of command:%s\n", command_name);
		//increase pointer to end of command name
		buffer = buffer + locationOfSpcae;
		// increase pointer to the start of next parameter
		buffer = setTheLocationToStartOfNextString(buffer);
		//printf("debugging: the rest of command:%s\n", buffer);
		/*Check if the command name is valid from this state value*/
		int paramCnt = 0; //number of parameters
		if(strcmp(command_name,COMMANDSOLVE)==0){ //solve command
			//valid in all states
			paramCnt = numberOfParameters(buffer);
			if(paramCnt>1){
				printf("Error: %s", EXCESSPARAMSERROR);
				continue;
			}
			if(paramCnt<1){
				printf("Error: %s", MISSINGPARAMSERROR);
				continue;
			}
			locationOfSpcae = locationOfSpace(buffer); //find the next location of space
			buffer[locationOfSpcae] = '\0'; //end of word
			user_command[0]= 15;
			strcpy(user_path, buffer);
			invalid_command = 0;
			break;
		}

		if(strcmp(command_name,COMMANDEDIT)==0){ //edit command
			//valid in all states
			paramCnt = numberOfParameters(buffer);

			if(paramCnt>1){
				printf("Error: %s", EXCESSPARAMSERROR);
				continue;
				}
			locationOfSpcae = locationOfSpace(buffer); //find the next location of space
			buffer[locationOfSpcae] = '\0'; //end of word
			strcpy(user_path, buffer); // might be empty
			user_command[0]= 16;
			invalid_command = 0;
			break;

		}
		if(strcmp(command_name,COMMANDMARKERRORS)==0){ //mark errors command
			if(state !=1){ //only available in 'solve' mode
				printf("Error: %s", WRONGSTATEERROR);
				continue;
			}
			paramCnt = numberOfParameters(buffer);
			if(paramCnt>1){
				printf("Error: %s", EXCESSPARAMSERROR);
				continue;
			}
			if(paramCnt<1){
				printf("Error: %s", MISSINGPARAMSERROR);
				continue;
			}
			locationOfSpcae = locationOfSpace(buffer); //find the next location of space
			buffer[locationOfSpcae] = '\0'; //end of word
			char *rest;
			int value1 = strtol(buffer,&rest,10);
			if (strcmp(rest,buffer)==0){
				printf("Error: %s", NOTINT);
				continue;

			}
			if(value1==0 || value1==1 ){
				user_command[0]= 3;
				user_command[1]= value1;
				invalid_command = 0;
				break;

			}
			else{
				printf("Error: %s \n", FIRSTPARAMETERERRORMARKERRORS);
				continue;
			}
		}
		if(strcmp(command_name,COMMANDPRINTBOARD)==0){ //print board
			if(state == 0){ //not available in 'int' mode
				printf("Error: %s", WRONGSTATEERROR);
				continue;
						}
			paramCnt = numberOfParameters(buffer);
			if(paramCnt>0){
				printf("Error: %s", EXCESSPARAMSERROR);
				continue;
				}

			user_command[0]= 17;
			invalid_command = 0;
			break;
				}

		if(strcmp(command_name,COMMANDSET)==0){ //set X Y Z
			if(state == 0){ //not available in 'int' mode
				printf("Error: %s", WRONGSTATEERROR);
				continue;
						}
			paramCnt = numberOfParameters(buffer);
			if(paramCnt>3){
				printf("Error: %s", EXCESSPARAMSERROR);
				continue;
			}
			if(paramCnt<3){
				printf("Error: %s", MISSINGPARAMSERROR);
				continue;
			}

			//value 1
			char *rest;
			int value1 = strtol(buffer,&rest,10);
			if (strcmp(rest,buffer)==0){
				printf("Error: %s", NOTINT);
				continue;

			}
			if(value1<0 || value1>N){ // m = lines
				printf("Error: %s %d \n", FIRSTPARAMETERERROR, m);
				continue;
			}
			buffer = rest;
			buffer = setTheLocationToStartOfNextString(buffer);

			//value 2
//			printf("Debugging: rest of buffer is %s \n", buffer);
			int value2 = strtol(buffer,&rest,10);
			if (strcmp(rest,buffer)==0){
				printf("Error: %s", NOTINT);
				continue;
			}
			if(value2<0 || value2>N){ // n = rows
				printf("Error: %s %d", SECONDPARAMETERERROR, n);
				continue;
			}
			buffer = rest;
			buffer = setTheLocationToStartOfNextString(buffer);

			//value 3
			//printf("Debugging: rest of buffer is %s \n", buffer);
			int value3 = strtol(buffer,&rest,10);
			if (strcmp(rest,buffer)==0){
				printf("Error: %s", NOTINT);
				continue;
			}
			if(value3<0 || value3>(N)){ // alphabat size = m*n
				printf("Error: %s %d", THIRDPARAMETERERROR, m*n);
				continue;
			}
			user_command[0]= 1;
			user_command[1]= value1;
			user_command[2]= value2;
			user_command[3]= value3;
			invalid_command = 0;
			break;

			}
		if(strcmp(command_name,COMMANDVALIDATE)==0){ //validate
			if(state == 0){ //not available in 'int' mode
				printf("Error: %s", WRONGSTATEERROR);
				continue;
						}
			paramCnt = numberOfParameters(buffer);
			if(paramCnt>0){
				printf("Error: %s", EXCESSPARAMSERROR);
				continue;
				}

			user_command[0]= 6;
			invalid_command = 0;
			break;
				}
		if(strcmp(command_name,COMMANDGUESS)==0){ //Guess
			//valid in Solve mode only
			if(state != 1){ //available in 'Solve' mode only
				printf("Error: %s", WRONGSTATEERROR);
				continue;
						}
			paramCnt = numberOfParameters(buffer);
			if(paramCnt>1){
				printf("Error: %s", EXCESSPARAMSERROR);
				continue;
			}
			if(paramCnt<1){
				printf("Error: %s", MISSINGPARAMSERROR);
				continue;
			}
			//value 1
			char *rest;
			float value1 = strtof(buffer,&rest);
			if (strcmp(rest,buffer)==0){
				printf("Error: %s", NOTINT);
				continue;

			}
			if(value1<0.0 || value1>1.0){ // m = lines
				printf("Error: %s\n", FIRSTPARAMETERERRORGUESS);
				continue;
			}

			user_command[0]= 7;
			*user_threshold = value1;
			invalid_command = 0;
			break;
		}
		if(strcmp(command_name,COMMANDGENERATE)==0){ //generate X Y
			if(state != 2){ //available in 'edit' mode
				printf("Error: %s", WRONGSTATEERROR);
				continue;
						}
			paramCnt = numberOfParameters(buffer);
			if(paramCnt>2){
				printf("Error: %s", EXCESSPARAMSERROR);
				continue;
			}
			if(paramCnt<2){
				printf("Error: %s", MISSINGPARAMSERROR);
				continue;
			}

			//value 1
			char *rest;
			int value1 = strtol(buffer,&rest,10);
			if (strcmp(rest,buffer)==0){
				printf("Error: %s", NOTINT);
				continue;

			}
			if(value1<0 || value1>(m*n)){ // m = lines
				printf("Error: %s %d \n", FIRSTPARAMETERERROR, m*n);
				continue;
			}
			buffer = rest;
			buffer = setTheLocationToStartOfNextString(buffer);

			//value 2
			//printf("Debugging: rest of buffer is %s \n", buffer);
			int value2 = strtol(buffer,&rest,10);
			if (strcmp(rest,buffer)==0){
				printf("Error: %s", NOTINT);
				continue;
			}
			if(value2<0 || value2>(m*n)){ // n = rows
				printf("Error: %s %d", SECONDPARAMETERERROR, (m*n));
				continue;
			}

			user_command[0]= 5;
			user_command[1]= value1;
			user_command[2]= value2;
			invalid_command = 0;
			break;

			}
		if(strcmp(command_name,COMMANDUNDO)==0){ //undo
				if(state == 0){ //not available in 'int' mode
					printf("Error: %s", WRONGSTATEERROR);
					continue;
							}
				paramCnt = numberOfParameters(buffer);
				if(paramCnt>0){
					printf("Error: %s", EXCESSPARAMSERROR);
					continue;
					}

				user_command[0]= 11;
				invalid_command = 0;
				break;
					}
		if(strcmp(command_name,COMMANDREDO)==0){ //redo
			if(state == 0){ //not available in 'int' mode
				printf("Error: %s", WRONGSTATEERROR);
				continue;
						}
			paramCnt = numberOfParameters(buffer);
			if(paramCnt>0){
				printf("Error: %s", EXCESSPARAMSERROR);
				continue;
				}

			user_command[0]= 12;
			invalid_command = 0;
			break;
				}

		if(strcmp(command_name,COMMANDSAVE)==0){ //save X command
			if(state == 0){ //not available in 'int' mode
				printf("Error: %s", WRONGSTATEERROR);
				continue;
						}
			paramCnt = numberOfParameters(buffer);
			if(paramCnt>1){
				printf("Error: %s", EXCESSPARAMSERROR);
				continue;
			}
			if(paramCnt<1){
				printf("Error: %s", MISSINGPARAMSERROR);
				continue;
			}
			locationOfSpcae = locationOfSpace(buffer); //find the next location of space
			buffer[locationOfSpcae] = '\0'; //end of word
			user_command[0]= 13;
			strcpy(user_path,buffer);
			invalid_command = 0;
			break;
		}

		if(strcmp(command_name,COMMANDHINT)==0){ //hint X Y
			if(state != 1){ // available in 'solve' mode
				printf("Error: %s", WRONGSTATEERROR);
				continue;
						}
			paramCnt = numberOfParameters(buffer);
			if(paramCnt>2){
				printf("Error: %s", EXCESSPARAMSERROR);
				continue;
			}
			if(paramCnt<2){
				printf("Error: %s", MISSINGPARAMSERROR);
				continue;
			}

			//value 1
			char *rest;
			int value1 = strtol(buffer,&rest,10);
			if (strcmp(rest,buffer)==0){
				printf("Error: %s", NOTINT);
				continue;

			}
			if(value1<0 || value1>N){
				printf("Error: %s %d \n", FIRSTPARAMETERERROR, N);
				continue;
			}
			buffer = rest;
			buffer = setTheLocationToStartOfNextString(buffer);

			//value 2
			//printf("Debugging: rest of buffer is %s \n", buffer);
			int value2 = strtol(buffer,&rest,10);
			if (strcmp(rest,buffer)==0){
				printf("Error: %s", NOTINT);
				continue;
			}
			if(value2<0 || value2>N){
				printf("Error: %s %d \n", SECONDPARAMETERERROR, N);
				continue;
			}

			user_command[0]= 10;
			user_command[1]= value1;
			user_command[2]= value2;
			invalid_command = 0;
			break;
			}

		if(strcmp(command_name,COMMANDGUESSHINT)==0){ //guess hint X Y
			if(state != 1){ // available in 'solve' mode
				printf("Error: %s", WRONGSTATEERROR);
				continue;
						}
			paramCnt = numberOfParameters(buffer);
			if(paramCnt>2){
				printf("Error: %s", EXCESSPARAMSERROR);
				continue;
			}
			if(paramCnt<2){
				printf("Error: %s", MISSINGPARAMSERROR);
				continue;
			}

			//value 1
			char *rest;
			int value1 = strtol(buffer,&rest,10);
			if (strcmp(rest,buffer)==0){
				printf("Error: %s", NOTINT);
				continue;

			}
			if(value1<0 || value1>N){
				printf("Error: %s %d \n", FIRSTPARAMETERERROR, N);
				continue;
			}
			buffer = rest;
			buffer = setTheLocationToStartOfNextString(buffer);

			//value 2
			//printf("Debugging: rest of buffer is %s \n", buffer);
			int value2 = strtol(buffer,&rest,10);
			if (strcmp(rest,buffer)==0){
				printf("Error: %s", NOTINT);
				continue;
			}
			if(value2<0 || value2>N){
				printf("Error: %s %d \n", SECONDPARAMETERERROR, N);
				continue;
			}

			user_command[0]= 9;
			user_command[1]= value1;
			user_command[2]= value2;
			invalid_command = 0;
			break;
			}
		if(strcmp(command_name,COMMANDNUMSOLUTIONS)==0){ //num solutions
			if(state == 0){ //not available in 'int' mode
				printf("Error: %s", WRONGSTATEERROR);
				continue;
						}
			paramCnt = numberOfParameters(buffer);
			if(paramCnt>0){
				printf("Error: %s", EXCESSPARAMSERROR);
				continue;
				}

			user_command[0]= 4;
			invalid_command = 0;
			break;
				}
		if(strcmp(command_name,COMMANDAUTOFILL)==0){ //autofill
			if(state != 1){ //available in 'solve' mode
				printf("Error: %s", WRONGSTATEERROR);
				continue;
						}
			paramCnt = numberOfParameters(buffer);
			if(paramCnt>0){
				printf("Error: %s", EXCESSPARAMSERROR);
				continue;
				}

			user_command[0]= 2;
			invalid_command = 0;
			break;
				}
		if(strcmp(command_name,COMMANDRESET)==0){ //reset
			if(state == 0){ //not available in 'int' mode
				printf("Error: %s", WRONGSTATEERROR);
				continue;
						}
			paramCnt = numberOfParameters(buffer);
			if(paramCnt>0){
				printf("Error: %s", EXCESSPARAMSERROR);
				continue;
				}

			user_command[0]= 8;
			invalid_command = 0;
			break;
				}
		if(strcmp(command_name,COMMANDEXIT)==0){ //exit
		//Available in all sates
			paramCnt = numberOfParameters(buffer);
			if(paramCnt>0){
				printf("Error: %s", EXCESSPARAMSERROR);
				continue;
				}

			user_command[0]= 0;
			invalid_command = 0;
			break;
				}

		printf("Error: %s", INVALIDCOMMANDERROR);
	}


	/*validate by order*/
	/*update user_command*/
	/*command string to int*/
	/*exit - 0, set - 1, autoFill - 2, markErrors - 3, numSolutions - 4, generate - 5, validate - 6*/
	/*guess - 7, reset - 8, guess_hint - 9, hint - 10, undo - 11, redo - 12, save - 13, toInit - 14*/
	/*toSolve - 15, toEdit - 16, printBoard - 17*/
}
