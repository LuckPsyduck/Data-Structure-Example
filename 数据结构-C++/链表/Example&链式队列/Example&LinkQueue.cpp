#include "stdafx.h"
#include "LinkQueue.h"
using namespace std;

// 判断队空
int CLinkQueue::queueempty()
{
	return front == NULL && rear == NULL;
}

// 判断队满
int CLinkQueue::queuefull()
{
	return count == QueueSize;
}

// 入队(队列的插入)
void CLinkQueue::enqueue(datatype x)//在队列中插入一元素e为Q的新队尾元素
{
	queuenode *p;
	p = (queuenode *)malloc(sizeof(queuenode));
	p->data = x;
	p->next = NULL;
	if (!queueempty())
	{ 
		rear->next = p;
		rear = p; 
	}
	else
		front = rear = p;
	count++;
}

// 出队(队列的删除)
datatype CLinkQueue::dequeue()//若队列不空则删除队列头部元素并用e返回其值
{
	datatype  x;
	queuenode *p;
	if (queueempty())
	{
		cerr << "队列已空\n";
		exit(1);
	}
	p = front;
	x = p->data;
	front = p->next;
	if (rear == p) 
		rear = NULL;
	count--;
	delete p;
	return x;
}

// 取队列的头元素
datatype CLinkQueue::queuefront()
{
	if (queueempty())
	{
		cerr << "队列空.\n"; 
		exit(1);
	}
	return front->data;
}


//求队列的长度(即队列的元素个数)
int CLinkQueue::QueueLength()
{
	return count;
}


