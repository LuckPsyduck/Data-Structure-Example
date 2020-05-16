/**********************循环队列******************************/
/*********存储空间为MAX_QSIZE的循环队列中，最多只能存放MAX_QSIZE-1个元素********/
/*队列空的条件是队尾指针等于队头指针，队列满的条件改为（队尾指针+1）对MAX_QSIZE求余 等于队头指针*/
#include<stdio.h>                  
#include<malloc.h>
#include<stdlib.h>
#include<math.h>
#define ERROR -1
#define OK 1

#define STACK_INIT_SIZE 10//初始分配量
#define STACK_INCREMENT 2//分配增量

typedef int Status;

typedef int QElemType;

#define MAX_QSIZE 5//实际最大队列长度为 MAX_QSIZE+1

struct SqQueue
{
	QElemType *base;//初始化的动态分配存储空间
	int front;//头指针,指向队列头元素
	int rear;//尾指针，指向队列尾元素的下一个位置
};


void InitQueue(SqQueue &Q)
{
	Q.base = (QElemType *)malloc(MAX_QSIZE*sizeof(QElemType));//头结点
	if (!Q.base)
		exit(EXIT_FAILURE);
	Q.front = Q.rear = 0;
}

void DestroyQueue(SqQueue &Q)
{
	if (Q.base)
		free(Q.base);
	Q.base = NULL;
	Q.front = Q.rear = 0;
}

void ClearQueue(SqQueue &Q)
{
	Q.front = Q.rear = 0;
}

Status QueueEmpty(SqQueue Q)
{
	if (Q.front==Q.rear)
		return true;
	else
		return false;
}

/******************返回队头元素**********************/
Status GetHead(SqQueue Q, QElemType &e)
{
	if (Q.front == Q.rear)
		return ERROR;
	e = Q.base[Q.front];
	return OK;
}
/***************************取余的目的是将值限定在0到MAX_QSIZE-1中**************************/

/*******************插入队尾元素***************************/
Status EnQueue(SqQueue &Q, QElemType e)
{
	if ((Q.rear + 1) % MAX_QSIZE == Q.front)//队列满
		return ERROR;
	Q.base[Q.rear] = e;
	Q.rear = (Q.rear + 1) % MAX_QSIZE;
	return OK;
}

int QueueLength(SqQueue Q)
{
	return (Q.rear - Q.front + MAX_QSIZE) % MAX_QSIZE;
}
/********************删除队头元素，用e返回***************************/
Status DeQueue(SqQueue &Q, QElemType &e)
{
	if (Q.front == Q.rear)//
		return ERROR;
	e = Q.base[Q.front];
	Q.front = (Q.front + 1) % MAX_QSIZE;//移动头指针
	return OK;
}

void QueueTraverse(SqQueue Q, void(*visit)(QElemType))
{
	int i = Q.front;
	while (i != Q.rear)
	{
		visit(Q.base[i]);
		i = (i + 1) % MAX_QSIZE;
	}
	printf("\n");
}


