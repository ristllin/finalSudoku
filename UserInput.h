/*
 * UserInput.h
 *
 *  Created on: Mar 16, 2019
 *      Author: shahare
 */

#ifndef USERINPUT_H_
#define USERINPUT_H_

int locationOfSpace(char* buffer);
char* setTheLocationToStartOfNextString(char* buffer);
int numberOfParameters(char* buffer);
int getLine (const char *prmpt, char *buff, size_t sz);
void userInput(int* board, int m,int n,int state, int* user_command, char* user_path, float* user_threshold);

#endif /* USERINPUT_H_ */
