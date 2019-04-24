/*
 * List
 *
 *  Created on: Apr 6, 2019
 *      Author: Roy Darnell and Shahar Eshed
 */

#ifndef LIST_H_
#define LIST_H_
struct Node  {
	int x;
	int y;
	int data;
	struct Node* next;
	struct Node* prev;
};
struct Node* GetNewNode(int x);
void InsertAtHead(int x,struct Node* head);
void InsertAtTail(int x,struct Node* head);
void Print(struct Node* head);
void ReversePrint(struct Node* head);
void RemoveNode(struct Node* node);
void RemoveFollowingNodes(struct Node* head);

#endif /* LIST_H_ */
