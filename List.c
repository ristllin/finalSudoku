/*
 * List.c
 *
 *  Created on: Apr 6, 2019
 *      Author: Roy Darnell and Shahar Eshed
 */
/* Doubly Linked List implementation */
#include<stdio.h>
#include<stdlib.h>
#include "List.h"
//
//struct Node  {
//	int x;
//	int y;
//	int data;
//	struct Node* next;
//	struct Node* prev;
//};

/*Creates a new Node and returns pointer to it*/
struct Node* GetNewNode(int data,int xdata, int ydata) {
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->data = data;
	newNode->x = xdata;
	newNode->y = ydata;
	newNode->prev = NULL;
	newNode->next = NULL;
	return newNode;
}

/*Inserts a Node at head of doubly linked list*/
void InsertAtHead(int data,int xdata,int ydata,struct Node* head) {
	struct Node* newNode = GetNewNode(data,xdata,ydata);
	if(head == NULL) {
		head = newNode;
		return;
	}
	head->prev = newNode;
	newNode->next = head;
	head = newNode;
}

/*Inserts a Node at tail of Doubly linked list*/
void InsertAtTail(int data,int xdata,int ydata,struct Node* head) {
	struct Node* temp = head;
	struct Node* newNode = GetNewNode(data,xdata,ydata);
	if(head == NULL) {
		head = newNode;
		return;
	}
	while(temp->next != NULL) temp = temp->next; // Go To last Node
	temp->next = newNode;
	newNode->prev = temp;
}

/*Prints all the elements in linked list in forward traversal order*/
void Print(struct Node* head) {
	struct Node* temp = head;
	printf("Forward: ");
	while(temp != NULL) {
		printf("x:%d,y%d,value:%d|",temp->x,temp->y,temp->data);
		temp = temp->next;
	}
	printf("\n");
}

/*Prints all elements in linked list in reverse traversal order.*/
void ReversePrint(struct Node* head) {
	struct Node* temp = head;
	if(temp == NULL) return; /*empty list, exit*/
	/* Going to last Node*/
	while(temp->next != NULL) {
		temp = temp->next;
	}
	/* Traversing backward using prev pointer*/
	printf("Reverse: ");
	while(temp != NULL) {
		printf("x:%d,y%d,value:%d|",temp->x,temp->y,temp->data);
		temp = temp->prev;
	}
	printf("\n");
}

void RemoveNode(struct Node* node){
	/*release memory allocation, connect previous and next node*/
	struct Node* next = node->next;
	struct Node* prev = node->prev;
	next->prev = prev;
	prev->next = next;
	node->data = -1;
	node->x = -1;
	node->y = -1;
	node->next = NULL;
	node->prev = NULL;
}

void RemoveFollowingNodes(struct Node* head){
	/*removes all nodes from given node forward, including given node*/
	struct Node* temp = head;
	struct Node* next_node;
	if (head == NULL){return;} /*list is already empty*/
	next_node = head->next;
	if (head == NULL){return;}
	while (next_node != NULL) {
		temp->data = -1; /*zeroing all fields is not obligatory, but helps in debug*/
		temp->x = -1;
		temp->y = -1;
		temp->next = NULL;
		temp->prev = NULL;
		free(temp);
		temp = next_node;
		next_node = temp->next;
	}
	temp->data = -1; /*zeroing all fields is not obligatory, but helps in debug*/
	temp->x = -1;
	temp->y = -1;
	temp->next = NULL;
	temp->prev = NULL;
	free(temp);
}
