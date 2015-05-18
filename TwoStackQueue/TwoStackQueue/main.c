#include "LinkedListStack.h"

int main()
{
	int i;
	LinkedListStack * OutputStack = NULL;
	LinkedListStack * InputStack = NULL;
	Node * NewNode = NULL;

	LLS_CreateStack(&OutputStack);
	LLS_CreateStack(&InputStack);

	for (i = 0; i<5; i++)
	{
		NewNode = LLS_CreateNode(i);
		LLS_Push(OutputStack,NewNode);
	}

	for (i = 0; i<5; i++)
	{
		NewNode = LLS_Pop(OutputStack);
		LLS_Push(InputStack,NewNode);
	}

	for (i = 0; i<5; i++)
	{
		NewNode = LLS_Pop(InputStack);
		printf("%d\n",NewNode->Data);
		free(NewNode);
	}

	return 0;
}