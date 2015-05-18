#ifndef _LINKEDBUBBLE
#define _LINKEDBUBBLE

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct __Node
{
	int Data;
	struct __Node * Next;
}_Node;

_Node * CreateNode(int Data);
void AddNode(_Node ** Head,_Node * NewNode);
void swap(_Node * Node1,_Node* Node2);

#endif