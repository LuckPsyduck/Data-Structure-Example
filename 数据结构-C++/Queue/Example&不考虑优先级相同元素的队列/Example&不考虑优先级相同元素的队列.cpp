// 不考虑优先级相同元素的队列.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include "PQueue.h"

void main()
{
	PQueue MyQueue;
	datatype task;
	int i, m;
	cout << "输入产生随机数的种子数m:";
	cin >> m;
	srand(m);
	cout << "生成顺序优先级队列MyQueue:\n";
	for (i = 0; i<MaxSize; i++)
	{
		task.taskNo = i + 1;
		task.priority = rand() % 10;
		MyQueue.InsertPQ(task);
	}
	cout << "求顺序优先级队列MyQueue的长度:";
	cout << MyQueue.PQueueSize() << endl;
	cout << "输出顺序优先级队列MyQueue:\n";
	cout << "序号 任务号 优先级\n";
	i = 1;
	while (!MyQueue.PQueueEmpty())
	{
		cout << setw(2) << i;
		task = MyQueue.DeQueue();
		cout << setw(6) << task.taskNo;
		cout << setw(7) << task.priority << endl;
		i++;
	}
	cin.get();
	cin.get();
}


