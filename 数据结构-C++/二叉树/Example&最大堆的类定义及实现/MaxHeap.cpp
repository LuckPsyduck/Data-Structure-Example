#include "stdafx.h"
#include "MaxHeap.h"

using namespace std;

CMaxHeap::CMaxHeap(int MaxSize)
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

void CMaxHeap::Destroyheap()
{
	free(heapArray);
}

void CMaxHeap::Clearheap()
{
	heapsize = 0;
}

bool CMaxHeap::HeapEmpty()
{
	if (heapsize == 0) 
		return true;
	else 
		return false;
}

bool CMaxHeap::HeapFull()
{
	return heapsize == maxheapSize;
}

int CMaxHeap::HeapLength()
{
	return heapsize;
}

ElemType CMaxHeap::GetTop()
{
	if (heapsize == 0)
	{
		cerr << "堆已空!\n"; 
		exit(1);
	}
	return heapArray[0];
}

void CMaxHeap::FilterUp()//从下至上，所以根据当前结点，算出父亲结点，然后跟父亲结点进行比较，									
{								//如果子结点小的话，则需要进行相互交换，反之不用，直到循环到下标到达结尾；
	int c, p;
	ElemType temp;
	c = heapsize - 1;
	p = (c - 1) / 2;
	temp = heapArray[c];
	while (c != 0)
	{
		if (heapArray[p]>temp)//大则交换
			break;
		heapArray[c] = heapArray[p];
		c = p;
		p = (c - 1) / 2;
	}
	heapArray[c] = temp;
}

void CMaxHeap::FilterDown()//根据当前结点，算出左右子结点，然后跟当前结点进行比较，如果左右结点小，
{	 //这里需要注意的是，取左右子结点中小的进行交换，因为其中必然会有三者之中的最小值，反之不用，直到循环到下标到达0
	int c, p;
	ElemType temp;
	p = 0;
	c = 2 * p + 1;
	temp = heapArray[p];
	while (c<heapsize)
	{
		if (c + 1<heapsize&&heapArray[c + 1]>heapArray[c])//找出结点最大的比较
			c = c + 1;
		if (temp>heapArray[c])//再与父亲结点比较
			break;
		heapArray[p] = heapArray[c];
		p = c;
		c = 2 * p + 1;
	}
	heapArray[p] = temp;
}

void CMaxHeap::HeapInsert(ElemType item)
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

ElemType CMaxHeap::HeapDelete()
{
	ElemType temp;
	if (heapsize == 0)
	{
		cerr << "堆已空!\n";
		exit(1);
	}
	temp = heapArray[0];
	heapArray[0] = heapArray[heapsize - 1];
	heapsize--;
	FilterDown();
	return(temp);
}

