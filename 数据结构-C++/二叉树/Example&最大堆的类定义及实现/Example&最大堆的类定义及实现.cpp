// 最大堆的类定义及实现.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"MaxHeap.h"

using namespace std;

void PrintArray(int a[], int n)
{
	for (int i = 0; i<n; i++)
		cout << setw(3) << a[i];
	cout << endl;
}

void main()
{
	cout << "maxheapm.cpp运行结果:\n";
	ElemType b[HeapSIZE];
	srand(350);
	for (int i = 0; i<HeapSIZE; i++)
		b[i] = rand() % 100;
	cout << "输出数组b:\n";
	PrintArray(b, HeapSIZE);

	CMaxHeap H(HeapSIZE), H1(HeapSIZE);
	for (int i = 0; i<HeapSIZE; i++)
		H.HeapInsert(b[i]);

	cout << "输出当前堆H的堆顶元素:\n";
	cout << setw(3) << H.GetTop() << endl;

	cout << "输出插入后数组b:\n";
	PrintArray(b, HeapSIZE);

	cout << "输出逐个删除的H堆中元素:\n";
	while (!H.HeapEmpty())
		cout << setw(3) << H.HeapDelete();
	cout << endl;

	for (int i = 0; i<HeapSIZE; i++)
		H1.HeapInsert(rand() % 100);

	cout << "输出当前堆H1的堆顶元素:\n";
	cout << setw(3) << H1.GetTop() << endl;

	cout << "输出逐个删除的H1堆中元素:\n";
	while (!H1.HeapEmpty())
		cout << setw(3) << H1.HeapDelete();
	cout << endl;

	H.Destroyheap(); 
	H1.Destroyheap();
}


