// 堆排序.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
using namespace std;
//大顶堆(最大为树根)（左右孩子的值小于父亲结点）
//完全二叉树的结构
void HeapAdjust(int *arr, int i, int size)//调整堆
{
	int lchild = 2 * i;
	int rchild = 2 * i + 1;
	int max = i;
	if (i <= size / 2)//有叶子的结点
	{
		if (lchild <= size&&arr[lchild] > arr[max])
			max = lchild;
		if (rchild <= size&&arr[rchild] > arr[max])
			max = rchild;
		if (max != i)
		{
			swap(arr[i], arr[max]);
			HeapAdjust(arr, max, size);//使以max为双亲结点的子树为堆
		}
	}
}

void BulidHeap(int *arr, int size)
{
	int i;
	for (i = size / 2; i >= 1; i--)//非结点的最大序号为size/2
		HeapAdjust(arr, i, size);//以子树为单位进行调整,由下置上
}

void HeapSort(int *arr, int size)
{
	int i;
	BulidHeap(arr, size);
	for (i = size; i >= 1; i--)
	{
		swap(arr[1], arr[i]);//交换堆顶与最后一个元素，即将删除的最大元素放到最后
		HeapAdjust(arr, 1, i - 1);//余下的元素重新建立为大顶堆
	}
}

int main()
{
	int n, *arr;
	printf("input n:\n");
	cin >> n;
	arr = (int *)malloc(sizeof(int)*n);
	printf("input arr:\n");
	for (int i = 1; i <= n; i++)
		cin >> arr[i];

	HeapSort(arr, n);
	puts("sort:");
	for (int i = 1; i <= n; i++)
		cout << arr[i] << " ";
	printf("\n");
	return 0;
}

