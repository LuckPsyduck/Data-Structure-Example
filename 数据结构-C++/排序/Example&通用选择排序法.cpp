// 通用选择排序法.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<iomanip>
#include<stdlib.h>
#include<time.h>
using namespace std;

#define N 10

typedef bool(*isgreat)(void *this_num, void *next_num);

void gensort(void *base, int n, int elemsize, isgreat great)
{
	int i, j, k;
	for (i = 0; i<n - 1; i++)//车轮比较法，0号元素与后面所有的元素比较，选出最小的，
	{													//然后将下一个元素与之后的元素比较，选出最小的，直到最后一个
		k = i; //待比较元素
		char *this_num = (char *)base + k*elemsize;
		char *that = this_num;

		for (j = i + 1; j<n; j++)
		{
			char *next_num = (char *)base + j*elemsize;
			if (great(that, next_num)) 
				that = next_num;//that 为当时比较的最小元素
		}
		if (this_num != that)//当最小元素不是当前待比较的元素，则交换两者
		{
			for (int k = 0; k<elemsize; k++)
			{
				char temp = this_num[k];
				this_num[k] = that[k];
				that[k] = temp;
			}
		}
	}
}

bool greatint(void *first, void *second)
{
	return (*(int *)first>*(int *)second);//强制类型转换，加上解引用运算符
}

bool greatdouble(void *first, void *second)
{
	return (*(double *)first>*(double *)second);
}

//通用选择排序法测试
void main()
{
	int ai[N], i;
	srand(time(0));
	for (i = 0; i<N; i++)
		ai[i] = rand() % 100;
	cout << "排序前数组:\n";
	for (i = 0; i<N; i++)
		cout << setw(4) << ai[i]; cout << endl;
	gensort(ai, sizeof(ai) / sizeof(int), sizeof(int), greatint);
	cout << "排序后数组:\n";
	for (i = 0; i<N; i++)
		cout << setw(4) << ai[i]; cout << endl;
	double bf[N];
	for (i = 0; i<N; i++)
		bf[i] = rand() / 200.0;
	cout << setiosflags(ios::fixed);//置位，指定浮点数在固定十进制形式显示
	cout << "排序前数组:\n";
	for (i = 0; i<N; i++)
		cout << setprecision(2) << setw(7) << bf[i]; 
	cout << endl;

	gensort(bf, sizeof(bf) / sizeof(double), sizeof(double), greatdouble);
	cout << "排序后数组:\n";
	for (i = 0; i<N; i++)
		cout << setprecision(2) << setw(7) << bf[i];//精度
	cout << endl; cin.get();
}






