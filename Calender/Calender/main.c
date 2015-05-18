#include "LinkedList.h"
#include <stdio.h>

void PrintMenu();
void AddSchedule(Calender ** CurrentCalender);
void RemovetheSchedule(Calender ** CurrentCalender);
void PrintDaySchedule(Calender ** CurrentCalender);
void PrintMonthSchedule(Calender ** CurrentCalender);

int main()
{
	int select;
	Calender * Calender;

	CreateCalender(&Calender);
	PrintCalender(&Calender);

	do
	{
		PrintMenu();

		scanf("%d",&select);
		system("cls");
		switch (select)
		{
		case 1:
			AddSchedule(&Calender);
			break;
		case 2:
			RemovetheSchedule(&Calender);
			break;
		case 3:
			PrintDaySchedule(&Calender);
			break;
		case 4:
			PrintMonthSchedule(&Calender);
			break;
		case 5:
			PrintSchedule_All(&Calender);
			break;
		case 6:
			break;
		default:
			printf("Insert a Right Number\n");
			break;
		}
	}while (6 != select);
	return 0;
}

void PrintMenu()
{
	printf("Manage Your Schedule\n");
	printf("1.Add Schedule\n");
	printf("2.Remove the Schedule\n");
	printf("3.Print Schedule a Day\n");
	printf("4.Print Schedule on Month\n");
	printf("5.Print Schedule All");
	printf("6.Exit\n");
	printf("Your Choice :");
}

void AddSchedule(Calender ** CurrentCalender)
{
	int month,day;
	printf("Month:");
	scanf("%d",&month);
	printf("Day:");
	scanf("%d",&day);

	AppendSchedule_Day(month,day,CurrentCalender);
}

void RemovetheSchedule(Calender ** CurrentCalender)
{
	int month,day;
	printf("Month:");
	scanf("%d",&month);
	printf("Day:");
	scanf("%d",&day);

	RemoveSchedule(CurrentCalender,month,day);
}

void PrintDaySchedule(Calender ** CurrentCalender)
{
	int month,day;
	printf("Month:");
	scanf("%d",&month);
	printf("Day:");
	scanf("%d",&day);

	PrintSchedule_Day(month,day,CurrentCalender);
}

void PrintMonthSchedule(Calender ** CurrentCalender)
{
	int month,day;
	printf("Month:");
	scanf("%d",&month);

	PrintSchedule_Month(month,CurrentCalender);
}