// 十进制转八进制.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include "Stack.h"

void conversion()
{
	CStack *S;
	SElemType e;
	int n;
	S->InitStack(&S);
	printf("输入十进制数:");
	cin >> n;
	if (n<0)
	{
		printf("\n数必须大于零!\n");
		return;
	}
	if (!n)
		S->Push(0);
	while (n)
	{
		S->Push(n % 8);//反着取出
		n = n / 8;
	}
	printf("结果是:");
	while (!S->StackEmpty())
	{
		S->Pop(&e);
		printf("%d", e);
	}
	cout << endl;
}
void main()
{
	printf("convert.cpp运行结果:\n");
	conversion();
	getchar();
}

