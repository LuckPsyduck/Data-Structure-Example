// 选择排序法2.cpp : 定义控制台应用程序的入口点。
//从后往前，选出最大，次大......

#include "stdafx.h"
#include<iostream>
#include<iomanip>
#include<stdlib.h>
#include<time.h>
using namespace std;

#define N 10

void gensort(int b[], int n)
{
	int i, j, k;
	for (i = 1; i<n; i++)//比较n-1次
	{
		k = n - i;
		for (j = n - i - 1; j >= 0; j--)//从后往前
			if (b[k]<b[j])
				k = j;//选择最大的
		if (k != n - i)
		{
			int temp = b[k];
			b[k] = b[n - i]; 
			b[n - i] = temp;
		}
		for (int m = 0; m<N; m++)
			cout << setw(4) << b[m]; cout << endl;
	}
}

//选择排序法测试
void main()
{
	int ai[N], i;
	srand(time(0));
	for (i = 0; i<N; i++)
		ai[i] = rand() % 100;
	cout << "排序前数组:\n";
	for (i = 0; i<N; i++)
		cout << setw(4) << ai[i];
	cout << endl << "排序过程演示:\n";
	gensort(ai, sizeof(ai) / sizeof(int));
	cout << "排序后数组:\n";
	for (i = 0; i<N; i++)
		cout << setw(4) << ai[i];
	cout << endl; 
	cin.get();
}


