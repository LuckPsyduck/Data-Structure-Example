#include"stdafx.h"
#include "MinHeap.h"
using namespace std;


CMinHeap::CMinHeap(int MaxSize)
{
	if (MaxSize <= 0)
	{
		cerr << "参数MaxSize非法!\n";
		exit(1);
	}
	heapArray = (ElemType *) new ElemType[MaxSize];
	if (!heapArray)
		exit(-1);
	maxheapSize = HeapSIZE;
	heapsize = 0;
}

void CMinHeap::Destroyheap()
{
	free(heapArray);
}

void CMinHeap::Clearheap()
{
	heapsize = 0;
}

bool CMinHeap::HeapEmpty()
{
	if (heapsize == 0)
		return true;
	else
		return false;
}

bool CMinHeap::HeapFull()
{
	return heapsize == maxheapSize;
}

int CMinHeap::HeapLength()
{
	return heapsize;
}

ElemType CMinHeap::GetTop() //堆存在且非空则返回堆的堆顶元素
{
	if (heapsize == 0)
	{
		cerr << "堆已空!\n";
		exit(1);
	}
	return heapArray[0];
}

void CMinHeap::FilterUp()// 插入后的堆调整,使之符合最小堆的定义
{
	int c, p;  //插到数组的最后一个位置上，增加堆大小，并且上浮；
	ElemType temp;
	c = heapsize - 1;
	p = (c - 1) / 2;//找父结点//按层序排列 2n-1,2n  左右结点   相当于完全二叉树
	temp = heapArray[c];
	while (c != 0)//逐次比较和根结点的大小
	{
		if (heapArray[p] <= temp)
			break;
		heapArray[c] = heapArray[p];
		c = p;
		p = (c - 1) / 2;
	}
	heapArray[c] = temp;
}

void CMinHeap::FilterDown()	//删除后的堆调整,使之符合最小堆的定义
{						//将数组头元素用数组尾元素进行替换，减小堆大小，并且下沉；
	int c, p;              
	ElemType temp; //从上至下，所以根据当前结点，算出左右子结点，然后跟当前结点进行比较，				
	p = 0;				   //	如果左右结点小，这里需要注意的是，取左右子结点中小的进行交换，
	c = 2 * p + 1;//子结点
	temp = heapArray[p];//根结点
	while (c < heapsize)
	{
		if (c + 1 < heapsize&&heapArray[c + 1] < heapArray[c])//左右结点
			c = c + 1;
		if (temp <= heapArray[c])//再将最小的与根结点比较,进行交换
			break;
		heapArray[p] = heapArray[c];
		p = c;
		c = 2 * p + 1;
	}
	heapArray[p] = temp;
}

void CMinHeap::HeapInsert(ElemType item)
{
	if (heapsize == HeapSIZE)
	{
		cerr << "堆已满!\n";
		exit(1);
	}
	heapArray[heapsize] = item;
	heapsize++;
	FilterUp();
}

ElemType CMinHeap::HeapDelete()
{
	ElemType temp;
	if (heapsize == 0)
	{
		cerr << "堆已空!\n";
		exit(1);
	}
	temp = heapArray[0];
	heapArray[0] = heapArray[heapsize - 1];//补一个元素上去，相当于删除一个，再重新调整
	heapsize--;
	FilterDown();
	return(temp);
}

