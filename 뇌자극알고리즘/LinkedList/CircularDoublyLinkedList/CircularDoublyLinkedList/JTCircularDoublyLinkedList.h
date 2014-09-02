/************************************************
********	JTCircularDoublyLinkedList	*********
****************	version 0.1		*************
*************************************************

*****Functions of This Engine*****
1. CreateNode
	: Create the New Node at Memory
2. DestroyNode
	: Detroy the Node from Memory
3. AppendNode
	: Apeend the Node at Tail of List
4. InsertNewHead
	: Insert the New Head
5. InsertAfter
	: Insert the Node at Middle of List
6. RemoveNode
	: Remove the Node at List
7. GetNodeCount
	: Count the Nodes at List

*************************************************/


#ifndef JTCIRCULARDOUBLYLINKEDLIST_H
#define JTCIRCULARDOUBLYLINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct tagNode
{
	void* Data;

	struct tagNode* NextNode;
	struct tagNode* PrevNode;
}Node;


Node*	CreateNode(void* NewData);
void	DestroyNode(Node* CurrentNode);
void	AppendNode(Node** Head, Node* NewNode);
void	InsertNewHead(Node** Head, Node* NewHead);
void	InsertAfter(Node* Current, Node* NewNode);
void	RemoveNode(Node** Head, Node* Remove);
int		GetNodeCount(Node* Head);


#endif