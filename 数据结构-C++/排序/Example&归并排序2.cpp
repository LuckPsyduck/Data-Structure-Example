// 归并排序2.cpp : 定义控制台应用程序的入口点。
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

void output(sqlist r, int n)
{
	for (int i = 0; i<n; i++)
		cout << setw(4) << r[i].key;
	cout << endl;
}

void xuanze(sqlist b, int m, int n)
{
	int i, j, k;
	for (i = m; i<n - 1; i++)
	{
		k = i;
		for (j = i; j<n; j++)
			if (b[k].key>b[j].key)
				k = j;
		if (k != i)
		{
			rec temp = b[k];
			b[k] = b[i]; 
			b[i] = temp;
		}
	}
}

void merge(sqlist r, int l, int m, int h, sqlist r2)
{
	xuanze(r, l, m);
	xuanze(r, m, h);
	output(r, M);
	int i, j, k;
	k = i = l;
	for (j = m; i<m&&j<h; k++)
	{
		if (r[i].key <= r[j].key)
		{
			r2[k] = r[i];
			i++;
		}
		else
		{
			r2[k] = r[j]; 
			j++;
		}
		output(r2, M);
	}
	while (j<h)
	{
		r2[k] = r[j]; 
		j++;
		k++;
	}
	while (i <= m)
	{
		r2[k] = r[i]; 
		i++;
		k++;
	}
	output(r2, M);
}

void main()
{
	sqlist a, b; int i, j = 0, k = M / 2, n = M;
	srand(time(0));
	for (i = 0; i<M; i++)
	{
		a[i].key = rand() % 80; 
		b[i].key = 0;
	}
	cout << "排序前数组:\n";
	output(a, M);
	cout << "数组排序的过程演示:\n";
	merge(a, j, k, n, b);
	cout << "排序后数组:\n";
	output(b, M); 
	cin.get();
}



