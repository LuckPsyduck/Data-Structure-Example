#include "stdafx.h"
#include "PQueue.h"

// 判断队空
int PQueue::PQueueEmpty()
{
  return count==0;
}

// 判断队满
int PQueue::PQueuefull()
{
  return count==MaxSize;
}

//重载关系运算符小于<
int operator <(datatype &b,datatype &c)//不属于类的成员函数//自定义
 {
	return b.priority<c.priority;
}

//队列的插入
void PQueue::InsertPQ(datatype x)
{
	if(PQueuefull())
    {
		cerr<<"队列满.\n";
		exit(1);
	}
  data[count]=x;
   count++;
 }

//队列的删除
datatype PQueue::DeQueue()
{
	if(PQueueEmpty())
    {
		cerr<<"队列空.\n";
		exit(1);
	}
  datatype min=data[0];
  int minindex=0;
  for(int i=0;i<count;i++)
	 if(data[i]<min)//优先级,删除优先级低的//均是重载的小于号
	  {
		  min=data[i];
		  minindex=i;
	  }
  data[minindex]=data[count-1];//覆盖，删除
  count--;
  return min;
 }

// 取队列的头元素
datatype PQueue::PQueuefront()
{
	if(PQueueEmpty())
   {
		cerr<<"队列空.\n";
		exit(1);
   }
  datatype min=data[0];
  for(int i=1;i<count;i++)
   if(data[i]<min)//优先级低的
    min=data[i];
  return min;
 }

//求队列的元素个数
int PQueue::PQueueSize()
{
	return count;
}



