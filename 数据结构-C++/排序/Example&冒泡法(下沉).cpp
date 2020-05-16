// 冒泡法(下沉).cpp : 定义控制台应用程序的入口点。
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
	for (i = 1; i<n; i++)
	{
		for (j = 0; j<n - i; j++)//选出最大数，放在最后
			if (b[j]>b[j + 1])
			{
				int temp = b[j];
				b[j] = b[j + 1]; 
				b[j + 1] = temp;
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
	cout << endl; cin.get();
}







