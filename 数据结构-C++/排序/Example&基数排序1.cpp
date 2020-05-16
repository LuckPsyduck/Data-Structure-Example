// 基数排序1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<iomanip>
#include<stdlib.h>
#include<time.h>
using namespace std;

const int N = 10;
class jishu
{
public:
	jishu(int d[], int s) :n(s)
	{
		for (int i = 0; i<n; i++)
			A[i] = d[i];
	}
	void output()
	{
		for (int i = 0; i<n; i++)
			cout << setw(4) << A[i];
		cout << endl;
	}
	void radix(int B[], int k, int r, int cnt[])//由低位到高位
	{
		int j;
		for (int i = 0, rtok = 1; i<k; i++, rtok *= r)
		{
			for (j = 0; j<r; j++) //初始化
				cnt[j] = 0;

			for (j = 0; j<n; j++) 
				cnt[(A[j] / rtok) % r]++;//同位相同的元素个数

			for (j = 1; j<r; j++) 
				cnt[j] = cnt[j - 1] + cnt[j];//相应位元素存储在数组中的位置

			for (j = n - 1; j >= 0; j--)
				B[--cnt[(A[j] / rtok) % r]] = A[j];//进行排序,放入到B

			for (j = 0; j<n; j++)
				A[j] = B[j];//赋给A 进行下一轮的排序
			output();
		}
	}
private:int A[N], n;
};
void main()
{
	int a[N], b[N], c[N], i, k = 3;
	srand(time(0));
	for (i = 0; i<N; i++)
	{
		a[i] = rand() % 1000;//三位数的基数排序
		b[i] = 0;
	}
	jishu jx(a, N);
	cout << "排序前数组a:\n";
	jx.output();
	cout << "数组排序的过程演示:\n";
	jx.radix(b, k, 10, c);
	cout << "排序后数组a:\n";
	jx.output(); 
	cin.get();
}









