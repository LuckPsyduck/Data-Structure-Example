#pragma once

#include<iostream>
#include<iomanip>
#include<stdlib.h>
#include<conio.h>

typedef int ElemType;

#define HeapSIZE 10
#define MaxHeapSize 100

class CMaxHeap
{
private:
	ElemType *heapArray;
	int maxheapSize;
	int heapsize;
public:

	//构造一个空堆S
	CMaxHeap(int);

	//堆存在则堆被销毁
	void Destroyheap();

	//堆存在则清为空堆
	void Clearheap();

	//堆空则返回true,否则false
	bool HeapEmpty();

	//堆满则返回true,否则false
	bool HeapFull();

	// 堆存在则返回堆的元素个数,即堆的长度
	int HeapLength();

	//堆存在且非空则返回堆的堆顶元素
	ElemType GetTop();

	// 插入后的堆调整,使之符合最大堆的定义
	void FilterUp();

	//删除后的堆调整,使之符合最大堆的定义
	void FilterDown();

	//堆插入
	void HeapInsert(ElemType item);

	//堆删除
	ElemType HeapDelete();
};

