#include "LinkedBubble.h"

int main()
{
	_Node * Head = NULL;
	_Node * Tail = NULL;
	_Node * NewNode = NULL;
	int i,j,check;

	srand(time(NULL));

	for (i = 0; i<9; i++)
	{
		check = 0;

		NewNode = CreateNode(rand()%9+1);

		Tail = Head;

		while (Tail != NULL)
		{
			if (Tail->Data == NewNode->Data)
			{
				check = 1;
				i--;
				break;
			}

			Tail = Tail->Next;
		}

		if (check == 1)
		{
			free(NewNode);
		}
		else
		{
			AddNode(&Head,NewNode);
		}
	}

	Tail = Head;

	while (Tail != NULL)
	{
		printf("%2d",Tail->Data);
		Tail = Tail->Next;
	}
	printf("\n");

	Tail = Head;

	for (i = 0; i<8; i++)
	{
		NewNode = Tail;

		for (j=i;j<8;j++)
		{
			if ((NewNode->Data) > (NewNode->Next->Data))
			{
				swap(NewNode,NewNode->Next);
			}

			NewNode = NewNode->Next;
		}

	}

	Tail = Head;

	while (Tail != NULL)
	{
		printf("%2d",Tail->Data);
		Tail = Tail->Next;
	}
	printf("\n");

	return 0;
}