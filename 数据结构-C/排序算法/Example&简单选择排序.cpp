// 简单选择排序.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

void sort(int *arr, int n)
{
	int i, j, k,temp;
	for (i = 0; i < n; i++)
	{
		temp = arr[i];//待比较元素
		k = i;
		for(j=i+1;j<n;j++)
			if (arr[j]<temp)
			{
				temp = arr[j];//最小值
				k = j;//最小值的索引
			}
		if (i != k)//如果最小值与待比较的值不相等
		{
			temp = arr[i];
			arr[i] = arr[k];//依次按顺序排放最小值
			arr[k] = temp;
		}
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

	sort(arr,n);
	puts("sort:");
	for (int i = 0; i <n; i++)
		printf("%d ", arr[i]);
	printf("\n");
	return 0;
}

