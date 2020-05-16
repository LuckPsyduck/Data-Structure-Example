// 通用冒泡排序法.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<iomanip>
#include<stdlib.h>
#include<time.h>
using namespace std;

#define N 10

typedef int(*isgreat)(void *this_num, void *next_num);

void gensort(void *base, int n, int elemsize, isgreat great)//调用函数
{
	int i, j, k;
	for (i = 1; i < n; i++)
		for (j = 0; j < n - i; j++)//每次把最大的选出来放到最后
		{
			char *this_num = (char *)base + j*elemsize;
			char *next_num = this_num + elemsize;

			if (great(this_num, next_num)>0)
				for (k = 0; k<elemsize; k++)//元素互换，此函数针对复杂类型
				{
					char temp = this_num[k];
					this_num[k] = next_num[k];
					next_num[k] = temp;
				}
		}
}

int greatint(void *first, void *second)
{
	return (*(int *)first>*(int *)second);
}

int greatfloat(void *first, void *second)
{
	return (*(float *)first>*(float *)second);
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
	gensort(ai, sizeof(ai) / sizeof(int), sizeof(int), greatint);
	cout << "排序后数组:\n";
	for (i = 0; i<N; i++)
		cout << setw(4) << ai[i];
	cout << endl;
	float bf[N];
	for (i = 0; i<N; i++)
		bf[i] = rand() / 200.0;
	cout << setiosflags(ios::fixed);
	cout << "排序前数组:\n";
	for (i = 0; i<N; i++)
		cout << setprecision(2) << setw(7) << bf[i];
	cout << endl;
	gensort(bf, sizeof(bf) / sizeof(float), sizeof(float), greatfloat);
	cout << "排序后数组:\n";
	for (i = 0; i<N; i++)
		cout << setprecision(2) << setw(7) << bf[i];
	cout << endl; cin.get();
}







