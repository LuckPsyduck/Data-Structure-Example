// 通用冒泡法(上浮).cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<iomanip>
#include<stdlib.h>
#include<time.h>
using namespace std;

#define N 10

void gensort(int b[], int n)
{
	int i, j;
	for (i = 0; i<n - 1; i++)//每次选出小的放在前列
	{
		for (j = i + 1; j<n; j++)
			if (b[i]>b[j])
			{
				int temp = b[i];
				b[i] = b[j];
				b[j] = temp;
			}
		for (int k = 0; k<n; k++)
			cout << setw(4) << b[k];
		cout << endl;
	}
}

void main()
{
	int ai[N], i;
	srand(time(0));
	for (i = 0; i<N; i++)
		ai[i] = rand() % 100;
	cout << "排序前数组:\n";
	for (i = 0; i<N; i++)
		cout << setw(4) << ai[i];
	cout << endl;
	cout << "排序过程演示:\n";
	gensort(ai, sizeof(ai) / sizeof(int));
	cout << "排序后数组:\n";
	for (i = 0; i<N; i++)
		cout << setw(4) << ai[i];
	cout << endl;
	cin.get();
}








