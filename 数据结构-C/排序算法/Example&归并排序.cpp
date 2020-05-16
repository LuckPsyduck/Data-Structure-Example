// 归并排序.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
using namespace std;

void merge(int *arr, int start, int mid, int last)
{
	int i, j, k;
	int *arr1 = (int *)malloc(sizeof(int)*(mid - start + 1));
	int *arr2= (int *)malloc(sizeof(int)*(last-mid));

	for (i = 0; i < mid - start + 1; i++)
		arr1[i] = arr[start + i];
	for (i = 0; i < last - mid; i++)
		arr2[i] = arr[i + mid + 1];

	i = j = 0;
	k = start;
	while (i<(mid-start+1)&&j<(last-mid))
	{
		if (arr1[i] < arr2[j])
			arr[k++] = arr1[i++];
		else
			arr[k++] = arr2[j++];
	}
	//剩余的元素合并
	while (i < mid - start + 1)
		arr[k++] = arr1[i++];
	while (j < last - mid)
		arr[k++] = arr2[j++];
	free(arr1);
	free(arr2);
}

void mergesort(int *arr, int start, int end)
{
	int mid;
	if (start < end)
	{
		mid = (start + end) / 2;//分解数组

		mergesort(arr, start,mid);//前一半递归排序,从分解为最小单元开始比较
		mergesort(arr, mid + 1, end);//后一半递归排序

		merge(arr, start, mid, end);//两部分合并
	}
}

int main()
{
	int n, *arr;
	printf("input n:\n");
	cin >> n;
	arr = (int *)malloc(sizeof(int)*n);
	printf("input arr:\n");
	for (int i = 0; i <n; i++)
		cin >> arr[i];


	mergesort(arr, 0, n-1);
	puts("sort:");
	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";
	printf("\n");
	return 0;
}



