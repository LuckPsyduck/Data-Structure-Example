// 快速排序3.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<iomanip>
#include<stdlib.h>
#include<time.h>

using namespace std;

#define M 11
typedef int KeyType;
typedef int ElemType;

struct rec 
{
	KeyType key;
	ElemType data;
};

typedef rec sqlist[M];

void output(sqlist b, int n)
{
	for (int i = 1; i<n; i++)
		cout << setw(4) << b[i].key;
	cout << endl;
}

void quicksort(sqlist r, int s, int t)
{
	int i = s, j = t;
	if (s<t)
	{
		r[0] = r[s];
		while (i<j)
		{
			while (i<j&&r[j].key >= r[0].key)
				j--;
			r[i] = r[j];
			while (i<j&&r[i].key <= r[0].key) 
				i++;
			r[j] = r[i];
		}
		r[i] = r[0];
		output(r, M);
	}
	else 
		return;

	quicksort(r, s, j - 1);
	quicksort(r, j + 1, t);
}

void main()
{
	sqlist a1; int i, n = M, low = 0, high = 10;
	srand(time(0));
	for (i = 0; i<n; i++)
		a1[i].key = rand() % 80;
	cout << "排序前数组:\n";
	output(a1, n);
	cout << "数组排序的过程演示:\n";
	quicksort(a1, low, high);
	cout << "排序后数组:\n";
	output(a1, n);
	cin.get();
}



