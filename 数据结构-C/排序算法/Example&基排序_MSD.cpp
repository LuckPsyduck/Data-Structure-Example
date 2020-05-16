// 基排序_MSD.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

int getdigit(int x, int d)
{
	int a[] = { 1,1,10 };
	return ((x / a[d]) % 10);
}

void PrintArr(int arr[], int n)
{
	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";
	cout << endl;
}

void MSDdix_sort(int arr[], int begin, int end, int d)
{
	const int radix = 10;
	int count[radix], i, j;
	int *bucket = (int *)malloc((end - begin + 1) * sizeof(int));

	for (i = 0; i < radix; i++)
		count[i] = 0;

	for (i = begin; i <= end; i++)
		count[getdigit(arr[i], d)]++;

	for (i = 1; i < radix; i++)
		count[i] = count[i] + count[i - 1];

	for (i = end; i >= begin; --i)
	{
		j = getdigit(arr[i], d);
		bucket[count[j] - 1] = arr[i];
		--count[j];
	}
	for (i = begin, j = 0; i <= end; ++i, ++j)
		arr[i] = bucket[j];//满足第一个条件后的顺序
	free(bucket);
	for (i = 0; i < radix; i++)
	{
		int p1 = begin + count[i];//左边界
		int p2 = begin + count[i + 1] - 1;//右边界
		if (p1 < p2&&d>1)
			MSDdix_sort(arr, p1, p2, d - 1);//排序剩下的情况
	}
}

int main()
{
	int arr[10] = { 12,14,54,5,6,3,9,8,47,89 };
	cout << "排序前:\n";
	PrintArr(arr, 10);
	MSDdix_sort(arr, 0, 9, 2);
	cout << "排序后:\n";
	PrintArr(arr, 10);
    return 0;
}

