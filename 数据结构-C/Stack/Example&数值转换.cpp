/**********************十进制转n进制********************/

#include"Stack.h"
#define N 8    //定义待转换的进制 N（2-9）

void conversion()
{
	SqStack s;
	unsigned n;
	SElemType e;
	InitStack(s);

	printf("将十进制整数n转换为%d进制数，请输入：n（>=0）=", N);
	scanf("%u", &n);
	while (n)
	{
		Push(s, n%N);
		n = n / N;
	}
	while (!StackEmpty(s))
	{
		Pop(s, e);
		printf("%d", e);
	}
	printf("\n");
}

void main()
{
	conversion();
}
