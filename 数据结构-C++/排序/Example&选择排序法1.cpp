// 选择排序法.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<iomanip>
#include<stdlib.h>
#include<time.h>
using namespace std;

#define N 10

void gensort(int b[], int n)//车轮比较法
{
	int i, j, k;
	for (i = 0; i<n - 1; i++)
	{
		k = i;
		for (j = i + 1; j<n; j++)
			if (b[k]>b[j])
				k = j;
		if (k != i)
		{
			int temp = b[k];
			b[k] = b[i]; 
			b[i] = temp;
		}
	}
}

//选择排序法测试
void main()
{
	int ai[N], i;
	srand(time(0));// rand 检索生成的伪随机数字
	for (i = 0; i<N; i++)
		ai[i] = rand() % 100;
	cout << "排序前数组:\n";
	for (i = 0; i<N; i++)
		cout << setw(4) << ai[i];
	cout << endl;
	gensort(ai, sizeof(ai) / sizeof(int));
	cout << "排序后数组:\n";
	for (i = 0; i<N; i++)
		cout << setw(4) << ai[i];
	cout << endl; cin.get();
}



