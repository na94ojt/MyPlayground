#include "LinkedList.h"

enum
{
	SUN,MON,TUE,WED,THU,FRI,SAT
};

void CreateCalender(Calender ** NewCalender)
{
	int i,j;
	int Weekend = WED;
	Node* NewMonth = (Node *)malloc(sizeof(Node));

	(*NewCalender) = (Calender *)malloc(sizeof(Calender));


	(*NewCalender)->Months = NewMonth;

	for (i = 1; i<=12; i++)
	{
		NewMonth->Date = i;
		NewMonth->Week = i;
		NewMonth->Schedule = NULL;

		NewMonth->ChildNode = NULL;
		NewMonth->NextNode = (Node*)malloc(sizeof(Node));

		NewMonth = NewMonth->NextNode;
	}

	NewMonth = (*NewCalender)->Months;

	for (i = 1; i<=12; i++)
	{
		Node * NewDay = (Node *)malloc(sizeof(Node));

		NewMonth->ChildNode = NewDay;

		for (j = 1; j<=31; j++)
		{
			if (2 == i && 28 < j)
			{
				break;
			}
			else if (4 == i && 30 < j)
			{
				break;
			}
			else if (6 == i && 30 < j)
			{
				break;
			}
			else if (9 == i && 30 < j)
			{
				break;
			}
			else if (11 == i && 30 < j)
			{
				break;
			}
			else
			{
				NewDay->Date = j;
				NewDay->Week = (Weekend++)%7;
				NewDay->Schedule = NULL;

				NewDay->ChildNode = NULL;
				NewDay->NextNode = (Node*)malloc(sizeof(Node));

				NewDay = NewDay->NextNode;
			}
		}
		NewMonth = NewMonth->NextNode;
	}

}

void PrintCalender(Calender ** CurrentCalender)
{
	int i,j;
	Node * Month = (*CurrentCalender)->Months;
	Node * Day = Month->ChildNode;

	for (i = 1; i<=12; i++)
	{
		printf("\n%d¿ù\n",Month->Date);

		for (j = 1; j<=31; j++)
		{
			if (2 == i && 28 < j)
			{
				break;
			}
			else if (4 == i && 30 < j)
			{
				break;
			}
			else if (6 == i && 30 < j)
			{
				break;
			}
			else if (9 == i && 30 < j)
			{
				break;
			}
			else if (11 == i && 30 < j)
			{
				break;
			}
			else
			{
				printf("%dÀÏ  ",Day->Date);
				Day = Day->NextNode;
			}
		}
		Month = Month->NextNode;
		Day = Month->ChildNode;
	}
	printf("\n");
}

void AppendSchedule_Day(int month, int day, Calender ** CurrentCalender)
{
	int i,j;
	Node * Month = (*CurrentCalender)->Months;
	Node * Day = Month->ChildNode;

	for (i = 1; i<=12; i++)
	{
		for (j = 1; j<=31; j++)
		{
			if (2 == i && 28 < j)
			{
				break;
			}
			else if (4 == i && 30 < j)
			{
				break;
			}
			else if (6 == i && 30 < j)
			{
				break;
			}
			else if (9 == i && 30 < j)
			{
				break;
			}
			else if (11 == i && 30 < j)
			{
				break;
			}
			else
			{
				if (i == month && j == day)
				{
					char * temp = (char*)malloc(sizeof(char)*100);
					printf("Enter the Schedule : ");
					scanf("%s",temp);

					Day->Schedule = temp;
				}
				else
				{
					Day = Day->NextNode;
				}
			}
		}
		Month = Month->NextNode;
		Day = Month->ChildNode;
	}
}

void PrintSchedule_Day(int month, int day, Calender ** CurrentCalender)
{
	int i,j;
	Node * Month = (*CurrentCalender)->Months;
	Node * Day = Month->ChildNode;

	for (i = 1; i<=12; i++)
	{
		if (i == month)
		{
			for (j = 1; j<=31; j++)
			{
				if (2 == i && 28 < j)
				{
					break;
				}
				else if (4 == i && 30 < j)
				{
					break;
				}
				else if (6 == i && 30 < j)
				{
					break;
				}
				else if (9 == i && 30 < j)
				{
					break;
				}
				else if (11 == i && 30 < j)
				{
					break;
				}
				else
				{
					if (i == month && j == day)
					{
						if (NULL != Day->Schedule)
						{
							printf("%d/%d ",i,j);
							//SUN,MON,TUE,WED,THU,FRI,SAT
							switch(Day->Week)
							{
							case SUN:
								printf("SUN\n");
								break;
							case MON:
								printf("MON\n");
								break;
							case TUE:
								printf("TUE\n");
								break;
							case WED:
								printf("WED\n");
								break;
							case THU:
								printf("THU\n");
								break;
							case FRI:
								printf("FRI\n");
								break;
							case SAT:
								printf("SAT\n");
								break;
							}

							printf("Schedule : %s\n",Day->Schedule);
						}
					}
					else
					{
						Day = Day->NextNode;
					}
				}
			}
			break;
		}
		Month = Month->NextNode;
		Day = Month->ChildNode;
	}
}

void PrintSchedule_Month(int month,Calender ** CurrentCalender)
{
	int i,j;
	Node * Month = (*CurrentCalender)->Months;
	Node * Day = Month->ChildNode;

	for (i = 1; i<=12; i++)
	{
		if (i == month)
		{
			for (j = 1; j<=31; j++)
			{
				if (2 == i && 28 < j)
				{
					break;
				}
				else if (4 == i && 30 < j)
				{
					break;
				}
				else if (6 == i && 30 < j)
				{
					break;
				}
				else if (9 == i && 30 < j)
				{
					break;
				}
				else if (11 == i && 30 < j)
				{
					break;
				}
				else
				{
					if (Day->Schedule != NULL)
					{
						printf("%d/%d ",i,j);
						//SUN,MON,TUE,WED,THU,FRI,SAT
						switch(Day->Week)
						{
						case SUN:
							printf("SUN\n");
							break;
						case MON:
							printf("MON\n");
							break;
						case TUE:
							printf("TUE\n");
							break;
						case WED:
							printf("WED\n");
							break;
						case THU:
							printf("THU\n");
							break;
						case FRI:
							printf("FRI\n");
							break;
						case SAT:
							printf("SAT\n");
							break;
						}
						printf("Schedule : %s\n",Day->Schedule);

					}
				}
				Day = Day->NextNode;	
			}
			break;
		}

		Month = Month->NextNode;
		Day = Month->ChildNode;
	}
}

void PrintSchedule_All(Calender ** CurrentCalender)
{
	int i,j;
	Node * Month = (*CurrentCalender)->Months;
	Node * Day = Month->ChildNode;

	for (i = 1; i<=12; i++)
	{

		for (j = 1; j<=31; j++)
		{

			if (2 == i && 28 < j)
			{
				break;
			}
			else if (4 == i && 30 < j)
			{
				break;
			}
			else if (6 == i && 30 < j)
			{
				break;
			}
			else if (9 == i && 30 < j)
			{
				break;
			}
			else if (11 == i && 30 < j)
			{
				break;
			}
			else
			{
				if (Day->Schedule != NULL)
				{
					printf("%d/%d ",i,j);
					//SUN,MON,TUE,WED,THU,FRI,SAT
					switch(Day->Week)
					{
					case SUN:
						printf("SUN\n");
						break;
					case MON:
						printf("MON\n");
						break;
					case TUE:
						printf("TUE\n");
						break;
					case WED:
						printf("WED\n");
						break;
					case THU:
						printf("THU\n");
						break;
					case FRI:
						printf("FRI\n");
						break;
					case SAT:
						printf("SAT\n");
						break;
					}
					printf("Schedule : %s\n",Day->Schedule);

				}
			}
			Day = Day->NextNode;	
		}


		Month = Month->NextNode;
		Day = Month->ChildNode;
	}
}

void RemoveSchedule(Calender ** CurrentCalender, int month, int day)
{
	int i,j;
	Node * Month = (*CurrentCalender)->Months;
	Node * Day = Month->ChildNode;

	for (i = 1; i<=12; i++)
	{
		if (i == month)
		{
			for (j = 1; j<=31; j++)
			{
				if (2 == i && 28 < j)
				{
					break;
				}
				else if (4 == i && 30 < j)
				{
					break;
				}
				else if (6 == i && 30 < j)
				{
					break;
				}
				else if (9 == i && 30 < j)
				{
					break;
				}
				else if (11 == i && 30 < j)
				{
					break;
				}
				else
				{
					if (i == month && j == day)
					{
						if (NULL != Day->Schedule)
						{
							free(Day->Schedule);
							Day->Schedule = NULL;
						}
					}
					Day = Day->NextNode;
				}
			}
			break;
		}
		Month = Month->NextNode;
		Day = Month->ChildNode;
	}
}