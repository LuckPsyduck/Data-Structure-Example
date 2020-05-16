#pragma once
#include<iostream>
#include<iomanip>
#include<stdlib.h>
#include<string.h>
using namespace std;

#define QueueSize 10
typedef int datatype;

class CQueue
{
public:
	CQueue() ;
	~CQueue() {}

private:
	int front;
	int rear;
	int count;
	datatype data[QueueSize];
public:
	// 判断队空
	int queueempty();

	// 判断队满
	int queuefull();

	// 入队(队列的插入)
	void enqueue(datatype);

	// 出队(队列的删除)
	datatype dequeue();

	// 取队列的头元素
	datatype queuefront();

	//求队列的长度(即队列的元素个数)
	int QueueLength();
};

