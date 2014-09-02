#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_INDEX 4

int numofcompare = 0;

void BubbleSort(int DataSet[], int Length) 
{ 
	int i = 0; 
	int j = 0; 
	int temp = 0; 

	for ( i=0; i<Length-1; i++ ) 
	{ 
		for ( j=0; j<Length-(i+1); j++ )  
		{
			numofcompare++;
			if ( DataSet[j] > DataSet[j+1] ) 
			{ 
				temp = DataSet[j+1]; 
				DataSet[j+1] = DataSet[j]; 
				DataSet[j] = temp; 
			} 
		} 
	} 
} 

int main( void ) 
{ 
	int DataSet[MAX_INDEX]; 
	int Length = MAX_INDEX;
	int i = 0, j = 0;

	srand(time(NULL));


	for (i = 0; i<MAX_INDEX; i++)
	{
		DataSet[i] = rand()%MAX_INDEX;
		for (j = 0; j<i ;j++)
		{
			if (DataSet[i] == DataSet[j])
			{
				i--;
				break;
			}
		}
	}

	printf("Before Sort\n");
	for ( i=0; i<Length; i++ ) 
	{ 
		printf("%d ", DataSet[i]); 
	} 

	printf("\n\n");

	BubbleSort(DataSet, Length); 

	printf("After Sort\n");
	for ( i=0; i<Length; i++ ) 
	{ 
		printf("%d ", DataSet[i]); 
	} 

	printf("\n"); 
	printf("%d\n",numofcompare);
	return 0; 
}
