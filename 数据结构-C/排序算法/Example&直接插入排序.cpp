// 直接插入排序.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


void insertsort(int *arr, int n)
{
	int j = 0;
	for (int i = 1; i < n; i++)
		if (arr[i] < arr[i - 1])
		{
			int temp = arr[i];
			for (j = i - 1; j >= 0 && arr[j] > temp; j--)
				arr[j + 1] = arr[j];//元素向后移，
			arr[j + 1] = temp;//将这次比较的元素填到正确的位置
		}
}

int main()
{
	int *arr;
	int n;
	printf("input n:\n");
	scanf("%d",&n);
	arr = (int *)malloc(sizeof(int)*n);
	puts("intput arr:");
	for (int i = 0; i < n; i++)
		scanf("%d", &arr[i]);

	insertsort(arr, n);
	puts("sort:");
	for (int i = 0; i < n; i++)
		printf("%d ",arr[i]);

	printf("\n");
    return 0;
}

