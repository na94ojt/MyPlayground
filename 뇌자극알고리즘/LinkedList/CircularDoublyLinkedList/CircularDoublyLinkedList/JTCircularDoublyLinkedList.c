#include "JTCircularDoublyLinkedList.h"

Node*	CreateNode(void* NewData)
{
	Node* NewNode = (Node*)malloc(sizeof(Node));

	NewNode->Data = NewData;
	NewNode->NextNode = NULL;
	NewNode->PrevNode = NULL;

	return NewNode;
}

void	DestroyNode(Node* CurrentNode)
{
	free(CurrentNode->Data);
	free(CurrentNode);
}

void	AppendNode(Node** Head, Node* NewNode)
{
	if (NULL == (*Head))
	{
		(*Head) = NewNode;
	}
	else
	{
		Node* Tail = (*Head);

		while (NULL != Tail->NextNode)
		{
			Tail = Tail->NextNode;
		}

		Tail->NextNode = NewNode;
	}
}

void	InsertNewHead(Node** Head, Node* NewHead)
{
	if (NULL == (*Head))
	{
		(*Head) = NewHead;
	}
	else
	{
		NewHead->NextNode = (*Head);
		NewHead->PrevNode = (*Head)->PrevNode;
		(*Head)->PrevNode = NewHead;
		(*Head)->PrevNode->NextNode = NewHead;

		(*Head) = NewHead;		
	}
}

void	InsertAfter(Node* Current, Node* NewNode)
{
	NewNode->NextNode = Current->NextNode;
	NewNode->PrevNode = Current;

	Current->NextNode = NewNode;
	NewNode->NextNode->PrevNode = NewNode;
}

void	RemoveNode(Node** Head, Node* Remove)
{
	if (Remove == (*Head))
	{
		Node * Temp = (*Head);

		(*Head) = (*Head)->NextNode;
		(*Head)->PrevNode = Temp->PrevNode;
		(*Head)->PrevNode->NextNode = (*Head);
	}
	else
	{
		Node * Current = Remove->NextNode;

		Current->NextNode = Remove->NextNode;
		Current->NextNode->PrevNode = Current;

		Remove->NextNode = NULL;
		Remove->PrevNode = NULL;
	}
}

int		GetNodeCount(Node* Head)
{
	int Count = 0;
	Node* Current = Head;

	while (NULL == Current)
	{
		Count++;
		Current = Current->NextNode;
	}

	return Count;
}