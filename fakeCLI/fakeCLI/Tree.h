#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <string.h>

class TreeNode
{
public:
	char * dirname;


	TreeNode * childNODE;
	TreeNode * siblingNODE;
	TreeNode * parentNODE;

	TreeNode(char * name)
		: dirname(name)
	{
		childNODE = NULL;
		siblingNODE = NULL;
		parentNODE = NULL;
	}

	~TreeNode()
	{
		if (NULL != this->childNODE)
		{
			delete(this->childNODE);
		}

		if (NULL != this->siblingNODE)
		{
			delete(this->childNODE);
		}
	}
};

class Tree
{
public:
	TreeNode * rootDIR;
	TreeNode * currentDIR;


	Tree(TreeNode * root)
		: rootDIR(root)
	{
		currentDIR = rootDIR;
	}

	~Tree()
	{

	}

	void appendNEWDIR(TreeNode * parent, TreeNode * newdir)
	{
		if (NULL == parent->childNODE)
		{
			parent->childNODE = newdir;
		}
		else
		{
			TreeNode * elder = parent->childNODE;

			while (NULL != elder->siblingNODE)
			{
				elder = elder->siblingNODE;
			}

			elder->siblingNODE = newdir;
		}
		newdir->parentNODE = parent;
	}

	void deleteDIR(TreeNode * destNODE)
	{

		if (destNODE->parentNODE->childNODE == destNODE)
		{
			destNODE->parentNODE->childNODE = destNODE->siblingNODE;
		}
		else
		{
			TreeNode * currentNODE = destNODE->parentNODE->childNODE;

			while (currentNODE->siblingNODE != destNODE)
			{
				currentNODE = currentNODE->siblingNODE;
			}

			currentNODE->siblingNODE = destNODE->siblingNODE;
		}


		destNODE->siblingNODE = NULL;

		delete(destNODE);
	}

	TreeNode * getCURRENTDIR()
	{
		return currentDIR;
	}

	TreeNode * findDIR_CHILD(TreeNode * parent,char * dirname)
	{
		TreeNode * temp = parent;

		while (strcmp(temp->dirname,dirname) != 0)
		{
			temp = temp->childNODE;
		}

		return temp;
	}

	TreeNode * findDIR_SIBLING(TreeNode * elder, char * dirname)
	{
		TreeNode * temp = elder;

		while (strcmp(temp->dirname,dirname) != 0)
		{
			temp = temp->siblingNODE;
		}

		return temp;
	}
};

#endif