// 表达式求值.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include "Stack.h"

#define EOFILE '^'

char OP[10] = { '+','-','*','/','(',')','#' };

int precede[7][7] = {
	1,1,2,2,2,1,1,
	1,1,2,2,2,1,1,
	1,1,1,1,2,1,1,
	1,1,1,1,2,1,1,
	2,2,2,2,2,3,0,
	1,1,1,1,0,1,1,
	2,2,2,2,2,0,3 };

int In(char c, char *op)//判断输入的运算符， '+','-','*','/','(',')','#'
{
	int i = 0;
	while (i<7)
		if (c == op[i++])
			return 1;
	return 0;
}

char Precede(char op, char c)
{
	int pos_op;
	int pos_c;
	int i;
	for (i = 0; i<7; i++)
	{
		if (op == OP[i]) 
			pos_op = i;
		if (c == OP[i])
			pos_c = i;
	}
	switch (precede[pos_op][pos_c])
	{
	case 1:  return '>';
	case 2:  return '<';
	case 3:  return '=';
	}
	return 'A';
}

char Operate(int a, char theta, int b)
{
	switch (theta)
	{
	case '+':return a + b - '0';
	case '-':return a - b + '0';
	case '*':return (a - '0')*(b - '0') + '0';
	case '/':return (a - '0') / (b - '0') + '0';
	}
	return 'A';
}

char EvaluateExpression()
{
	CStack *OPND, *OPTR;
	char c, x, theta;
	char a, b;
	OPTR->InitStack(&OPTR);
	OPTR->Push('#');
	OPND->InitStack(&OPND);
	c = getchar();
	while (c != '#' || OPTR->GetTop() != '#')
	{
		if (!In(c, OP))//不属于 '+','-','*','/','(',')','#'
		{
			OPND->Push(c); 
			c = getchar();
		}
		else
			switch (Precede(OPTR->GetTop(), c))
			{
			case '<':
				OPTR->Push(c);
				c = getchar(); 
				break;
			case '=':
				OPTR->Pop(&x);
				c = getchar();
				break;
			case '>':
				OPTR->Pop(&theta);
				OPND->Pop(&b); 
				OPND->Pop(&a);
				OPND->Push(Operate(a, theta, b));
				break;
			}
	}
	c = OPND->GetTop();
	OPTR->DestroyStack();
	OPND->DestroyStack();
	return c;
}

void main()
{
	char i;
	printf("expre.cpp运行结果:\n");
	printf("范围[0,9],输入以#号结束:");
	i = EvaluateExpression();
	cout << "\n表达式的值是:";
	cout << i - '0' << endl;
	cin.get();
}

