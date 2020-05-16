// 快速排序法.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

void sort(int *arr, int left, int right)
{
	int i, j, temp;
	if (left < right)
	{ 
		i = left;
		j = right;
		temp = arr[left];
		while (i<j)
		{
			while (arr[j] >= temp&&j > i)//先从最右边向左查找第一个小于temp的值，两者交换
				j--;
			if (j > i)
				arr[i++] = arr[j];
			while (arr[i] <= temp&&j > i)//从最左边开始向右查找第一个大于temp的值，两者交换
				i++;
			if (j > i)
				arr[j--] = arr[i];
		}//不断将区域化小
		arr[i] = temp;
		sort(arr, left, i - 1);
		sort(arr, i + 1, right);
	}
}

int main()
{
	int n, *arr;
	printf("input n:\n");
	scanf("%d", &n);
	arr = (int *)malloc(sizeof(int)*n);
	printf("input arr:\n");
	for (int i = 0; i < n; i++)
		scanf("%d", &arr[i]);

	sort(arr,0,n-1);
	puts("sort:");
	for (int i = 0; i <n; i++)
		printf("%d ",arr[i]);
	printf("\n");
	return 0;
}

