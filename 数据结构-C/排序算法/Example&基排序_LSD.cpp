// 基排序_LSD.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

int getdigit(int x, int d)//取出各个位
{
	int a[] = { 1,1,10,100 };//第0位的元素没用
	return (x / a[d]) % 10;
}

void PrintArr(int arr[], int n)
{
	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";
	cout << endl;
}

void LSDdix_sort(int arr[], int begin, int end, int d)
{
	const int radix = 10;
	int count[radix], i, j;
	int *bucket = (int *)malloc((end - begin + 1) * sizeof(int));

	for (int k = 1; k <= d; k++)
	{
		for (i = 0; i < radix; i++)
			count[i] = 0;

		for (i = begin; i <= end; i++)
			count[getdigit(arr[i], k)]++;//各个桶中的数的个数

//count[1]至count[9],count[1]存的数为桶0和桶1的元素个数,依次类推
		for (i = 1; i < radix; i++)
			count[i] = count[i] + count[i - 1];

		for (i = end; i >= begin; --i)
		{
			j = getdigit(arr[i], k);//求出关键码的第k位的数字，
			bucket[count[j] - 1] = arr[i];//count[j]为j存储完最后一个元素大小，count[j]-1,则为可以存储j数字的最后一个位置，
			--count[j];////对应桶的装入数据索引减一 ，依次将元素向前存储
		}
		for (i = begin, j = 0; i <= end; ++i, ++j)
			arr[i] = bucket[j];////从各个桶中收集数据
	}
	free(bucket);
}

int main()
{
	int br[10] = { 20,80,90,589,998,965,852,123,456,789 };
	cout << "原数据如下:" << endl;
	PrintArr(br, 10);
	LSDdix_sort(br, 0, 9, 3);
	cout << "排序后数据如下:" << endl;
	PrintArr(br, 10);
    return 0;
}

