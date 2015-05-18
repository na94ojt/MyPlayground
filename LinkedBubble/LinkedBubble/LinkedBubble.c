#include "LinkedBubble.h"

_Node * CreateNode(int Data)
{
	_Node * NewNode = (_Node *)malloc(sizeof(_Node));

	NewNode->Data = Data;
	NewNode->Next = NULL;

	return NewNode;
}

void AddNode(_Node ** Head,_Node * NewNode)
{
	if ( (*Head) == NULL )
	{
		*Head = NewNode;
	}
	else
	{
		_Node * Tail = (*Head);

		while (Tail->Next != NULL)
		{
			Tail = Tail->Next;
		}

		Tail->Next = NewNode;
	}
}

void swap(_Node * Node1,_Node* Node2)
{
	int temp;

	temp = Node1->Data;
	Node1->Data = Node2->Data;
	Node2->Data = temp;
}