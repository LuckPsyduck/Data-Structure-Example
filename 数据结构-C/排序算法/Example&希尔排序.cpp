// 希尔排序.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

using namespace std;

void shell(int *arr, int n)
{
	int i, j, x, d;
	d = n / 2;                      //每次迭代的比较间隔
	while (d>=1)                    //控制循环
	{
		for (i = d + 1; i <= n; i++)
		{
			x = arr[i];
			j = i - d;
			while ((j>0)&&(x< arr[j]))
			{
				arr[j + d] = arr[j];//赋值大的元素
				j -= d;
			}
			arr[j + d] = x;//赋值小的元素
		}
		d /= 2;//下一个比较间隔
	}
}
/*
static void shell_sort(int unsorted[] , int len)
{
	int group, i, j, temp;
	for (group = len / 2; group > 0; group /= 2)
	{
		for (i = group; i < len; i++)
		{
			for (j = i - group; j >= 0; j -= group)
			{
				if (unsorted[j] > unsorted[j + group])
				{
					temp = unsorted[j];
					unsorted[j] = unsorted[j + group];
					unsorted[j + group] = temp;
				}
			}
		}
	}
}
*/
int main()
{
	int n, *arr;
	cout << "input n:" << endl;
	cin >> n;
	arr = (int *)malloc(sizeof(int)*n);
	cout << "input arr:\n";
	for (int i = 1; i <= n; i++)
		cin >> arr[i];
	shell(arr, n);
	cout << "sort :" << endl;
	for (size_t i = 1; i <= n; i++)
		cout << arr[i] << " ";
	cout << endl;
    return 0;
}

