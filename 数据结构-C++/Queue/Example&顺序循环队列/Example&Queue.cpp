#include "stdafx.h"
#include"Queue.h"

//构造函数
CQueue::CQueue()
{
	front = rear = count = 0;
}

// 判断队空
int CQueue::queueempty()
{
	return count == 0;
}

// 判断队满
int CQueue::queuefull()
{
	return count == QueueSize;
}

// 入队(队列的插入)
void CQueue::enqueue(datatype x)//在队列中插入一元素e为Q的新队尾元素
{
	if (queuefull())
		printf("队列满.\n");
	count++;
	data[rear] = x;
	rear = (rear + 1) % QueueSize;
	//rear指针后移
}

// 出队(队列的删除)
datatype CQueue::dequeue()//若队列不空则删除队列头部元素并用e返回其值
{
	datatype temp;
	if (queueempty())
		printf("队列空.\n");
	temp = data[front];
	count--;
	//front指针后移
	front = (front + 1) % QueueSize;
	return temp;
}

// 取队列的头元素
datatype CQueue::queuefront()
{
	if (queueempty())
		printf("队列空.\n");
	return data[front];
}

//求队列的长度(即队列的元素个数)
int CQueue::QueueLength()
{
	return count;
}



