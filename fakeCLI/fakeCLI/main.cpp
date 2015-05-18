#include "Tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

using namespace std;

//string  ** parser(string command);
/*
int main()
{
	Tree * mytree = new Tree(new TreeNode("root"));
	char shell[20];
	vector<char> command_temp;
	char push = 0;

	while (true)
	{
		sprintf_s(shell,20,"JTSHELL@%s] ",mytree->currentDIR->dirname);
		fputs(shell,stdout);

		do
		{
			push = getchar();	
			command_temp.push_back(push);

		} while (push != '\n');
		
		string command(command_temp.begin(),command_temp.end());
		parser(command);
		command_temp.clear();
	}

	return 0;
}

string  ** parser(string command_string)
{
	string ** result = new string*[5];
	char * command_char = new char[command_string.size()+1];
	char * result_temp = NULL;
	command_char[command_string.size()] = '\0';

	copy(command_string.begin(),command_string.end(),command_char);

	result_temp = strtok(command_char," ");

	int i = 0;

	while (result_temp != NULL && i<5)
	{
		result[i] = new string();
		*result[i++] = string(result_temp);
		result_temp = strtok(NULL," ");
	}

	command_string = *result[0];
	command_string = *result[1];
	

	return result;
}*/