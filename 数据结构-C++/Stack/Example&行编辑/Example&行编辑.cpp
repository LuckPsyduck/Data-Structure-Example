// 行编辑.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Stack.h"

#define EOFILE '^'

void LineEdit()
{
	CStack *S, *T;
	char str[100];
	int strlen = 0;
	char e;
	char ch;
	S->InitStack(&S);
	T->InitStack(&T);
	ch = getchar();
	while (ch != EOFILE)//结束标志
	{
		while (ch != EOFILE&&ch != '\n')
		{
			switch (ch) 
			{
			case '#':
				S->Pop(&ch);
				break;
			case '@':
				S->ClearStack();
				break;
			default:
				S->Push(ch);
				break;
			}
			ch = getchar();
		}
		if (ch == '\n')
			S->Push(ch);
		while (!S->StackEmpty())
		{
			S->Pop(&e);
			T->Push(e);
		}
		while (!T->StackEmpty())//还原顺序
		{
			T->Pop(&e);
			str[strlen++] = e;
		}
		if (ch != EOFILE) 
			ch = getchar();
	}
	printf("输出编辑后字符串:\n");
	str[strlen] = '\0';
	printf("%s\n", str);
	S->DestroyStack();
	T->DestroyStack();
}

void main()
{
	printf("LINEEDIT.CPP运行结果:\n");
	printf("输入字符串,以输入字符`作为结束:\n");
	LineEdit();
	cin.get();
	cin.get();
}

