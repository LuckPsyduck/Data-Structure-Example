// 折半插入排序.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

void insertsort(int *arr, int n)
{
	int *temp, temp_n;
	temp = (int *)malloc(sizeof(int)*(n + 1));
	for (size_t i = 0;i < n; i++)
		temp[i + 1] = arr[i];
	temp[0] = 0;
	int i, j, low, high, mid;
	for (i = 2; i <=n; i++)
	{
		temp[0] =temp[i];//arr[0]用于存放待比较的元素
		low = 1;
		high = i - 1;//比较1到i-1的元素
		while (low <= high)
		{
			mid = (low + high) / 2;
			if (temp[mid] > temp[0])
				high = mid - 1;
			else
				low = mid + 1;
		}
		for (j = i - 1; j >= high + 1; --j)
			temp[j + 1] = temp[j];//后移，空出插入元素的位置
		temp[high + 1] = temp[0];
	}
	for (size_t i = 1; i <=n; i++)
		arr[i - 1] = temp[i];
}


int main()
{
	int *arr;
	int n;
	printf("input n:\n");
	scanf("%d", &n);
	arr = (int *)malloc(sizeof(int)*n);
	puts("intput arr:");
	for (int i = 0; i < n; i++)//第一个元素为0，用于存储待比较的元素
		scanf("%d", &arr[i]);

	insertsort(arr, n);
	puts("sort:");
	for (int i = 0; i < n; i++)
		printf("%d ", arr[i]);

	printf("\n");
	return 0;
}

