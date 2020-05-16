#include "stdafx.h"
#include "Stack.h"

void CStack::CreateStack(int n, int m, int mark)
{
	ElemType x, a[LEN / 2];
	int i, j;
	for (i = 0; i<m; i++)
		a[i] = rand() % 100;
	for (i = 0; i<m - 1; i++)
	{
		int k = i;
		for (j = i + 1;j<m; j++)
			if (a[k]>a[j])
				k = j;
		if (k != i)
		{
			x = a[k]; 
			a[k] = a[i]; 
			a[i] = x;
		}
	}
	for (i = 0; i<m; i++)
		if (mark == 1)
			Push(a[m - 1 - i]);//ÉýÐò
		else
			if (mark == -1) 
				Push(a[i]);//½µÐò
			else 
				Push(rand() % 100);//ÎÞÐò
}

//Çå¿ÕÕ»
void CStack::ClearStack()
{ 
	top = 0;
}

//¼ì²éÕ»ÊÇ·ñÎª¿Õ
bool CStack::StackEmpty()
{
	return top == 0; 
}

//¶ÁÈ¡Õ»¶¥ÔªËØ
ElemType CStack::Peek()
{
	if (top == 0)
	{
		cerr << "Õ»Îª¿Õ!" << endl;
		exit(1);
	}
	return stack[top];
}

//ÏòÕ»ÖÐ²åÈëÔªËØ
void CStack::Push(const ElemType& item, int m)
{
	if (top == m) 
	{
		cerr << "Õ»ÒÑÂú!" << endl;
		exit(1);
	}
	top++;
	stack[top] = item;
}

//´ÓÕ»ÖÐÉ¾³ýÔªËØ
ElemType CStack::Pop()
{
	if (top == 0)
	{
		cerr << "Õ»Îª¿Õ!" << endl;
		exit(1);
	}
	top--;
	return stack[top + 1];
}

//¼ì²éÕ»ÊÇ·ñÒÑÂú
bool CStack::StackFull(int m)
{
	return top == m;
}

//Õ»µÄÊä³ö
void CStack::StackPrint(int m)
{
	for (int i = 0; i<m; i++)
		cout << setw(3) << Pop();
}
