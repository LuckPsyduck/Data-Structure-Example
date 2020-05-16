// 基数排序2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<iomanip>
#include<stdlib.h>
#include<time.h>
using namespace std;

const int N = 10;
const int rd = 10;
const int D = 2;

void output(int a[], int n)
{
	cout << "    ";
	for (int i = 0; i<n; i++)
		cout << setw(4) << a[i];
	cout << endl;
}

template<class Elem>
void radix(Elem A[], Elem B[], int n, int k, int r, int cnt[])//模板函数
{
	int j;
	for (int i = 0, rtok = 1; i<k; i++, rtok *= r)
	{
		for (j = 0; j<r; j++) 
			cnt[j] = 0;

		for (j = 0; j<n; j++) 
			cnt[(A[j] / rtok) % r]++;

		for (j = 1; j<r; j++)
			cnt[j] = cnt[j - 1] + cnt[j];

		for (j = n - 1; j >= 0; j--)
			B[--cnt[(A[j] / rtok) % r]] = A[j];

		for (j = 0; j<n; j++) 
			A[j] = B[j];

		output(A, n);
	}
}

void main()
{
	int a[N], b[N], c[N], i, k = 2;
	srand(time(0));
	for (i = 0; i<N; i++)
	{
		a[i] = rand() % 100;
		b[i] = 0;
	}
	cout << "排序前数组a:\n";
	output(a, N);
	cout << "数组排序的过程演示:\n";
	radix<int>(a, b, 10, k, 10, c);
	cout << "排序后数组a:\n";
	output(a, N); cin.get();
}







