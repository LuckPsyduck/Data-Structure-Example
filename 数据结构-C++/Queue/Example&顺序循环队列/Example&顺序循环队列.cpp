// 顺序循环队列.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"Queue.h"

void main()
{
	CQueue MyQueue;
	int i, x, m, a[3];
	printf("输入产生随机数的种子数m:");
	scanf("%d", &m);
	srand(m);
	printf("生成顺序循环队列MyQueue:\n");
	for (i = 0; i<QueueSize;)
	{
		x = rand() % 1000;
		if (100 <= x&&x <= 999)
		{
			MyQueue.enqueue(x); 
			i++;
		}
	}
	printf("求顺序循环队列MyQueue的长度:");
	printf("%d\n", MyQueue.QueueLength());
	printf("输出顺序循环队列MyQueue:\n");
	printf("同时求任一个三位数是否为回文数.\n");
	while (!MyQueue.queueempty())
	{
		x = MyQueue.dequeue();
		printf("%4d", x);
		a[0] = x % 10;
		x = x / 10; 
		a[1] = x % 10;
		x = x / 10; 
		a[2] = x;
		if (a[0] != a[2]) 
			printf("不是回文数!\n");
		if (a[0] == a[2])
			printf("是回文数!\n");
	}
	cin.get(); 
	cin.get();
}
