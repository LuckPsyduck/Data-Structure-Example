#include "stdafx.h"
#include "PQueue.h"


// 判断队空
int PQueue::PQueueEmpty()
{
	return count == 0;
}

// 判断队满
int PQueue::PQueuefull() 
{
	return count == MaxSize;
}
//重载关系运算符小于<
int operator <(datatype &b, datatype &c)
{
	return b.priority<c.priority;
}

// 队列的插入
void PQueue::InsertPQ(datatype x)
{
	if (PQueuefull())
	{
		cerr << "队列满.\n"; 
		exit(1);
	}
	data[count] = x;
	count++;
}

// 队列的删除
datatype PQueue::DeQueue()
{
	int i=0;
	if (PQueueEmpty())
	{
		cerr << "队列空.\n"; 
		exit(1);
	}
	datatype min = data[0];
	int minindex = 0;
	for (i = 0; i<count; i++)//按优先级排序
		if (data[i]<min)//重载了小于号的意义
		{
			min = data[i]; 
			minindex = i;
		}
	for (i = minindex; i<count - 1; i++)
		data[i] = data[i + 1];//按优先级排序，且保持先进先出,这是与上一个程序的区别
	count--;
	return min;
}

// 取队列的头元素
datatype PQueue::PQueuefront()
{
	if (PQueueEmpty())
	{
		cerr << "队列空.\n";
		exit(1);
	}
	datatype min = data[0];
	for (int i = 1; i<count; i++)
		if (data[i]<min)
			min = data[i];
	return min;
}

//求队列的元素个数
int PQueue::PQueueSize()
{
	return count;
}


