/*
 * List
 *
 *  Created on: Apr 6, 2019
 *      Author: Roy Darnell and Shahar Eshed
 */

#ifndef LIST_H_
#define LIST_H_
typedef struct Node  {
	int x;
	int y;
	int data;
	struct Node* next;
	struct Node* prev;
} Node;
struct Node* GetNewNode(int data,int xdata, int ydata);
void InsertAtHead(int data,int xdata,int ydata,struct Node* head);
void InsertAtTail(int data,int xdata,int ydata,struct Node* head);
void Print(struct Node* head);
void ReversePrint(struct Node* head);
void RemoveNode(struct Node* node);
void RemoveFollowingNodes(struct Node* head);

#endif /* LIST_H_ */
