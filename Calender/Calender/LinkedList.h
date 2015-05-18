#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>


//일정추가
//일정 삭제
//현재 날짜 출력



typedef struct tagNode
{
	int Date;
	int Week;
	char * Schedule;

	struct tagNode * NextNode;
	struct tagNode * ChildNode;
}Node;

typedef struct tagCalender
{
	Node * Months;
}Calender;

void CreateCalender(Calender ** NewCalender);
void PrintCalender(Calender ** CurrentCalender);
void AppendSchedule_Day(int month, int day, Calender ** CurrentCalender);
void PrintSchedule_Day(int month, int day, Calender ** CurrentCalender);
void PrintSchedule_Month(int month,Calender ** CurrentCalender);
void PrintSchedule_All(Calender ** CurrentCalender);
void RemoveSchedule(Calender ** CurrentCalender, int month, int day);

#endif