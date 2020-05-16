//选择排序法(函数模板、上浮)xuanze4f.cpp
#include"stdafx.h"
#include<iostream>
#include<iomanip>
#include<stdlib.h>
#include<time.h>
using namespace std;

#define M 10
template<class T>
void sortp(T d[], int size)
{
	int i, j, k, m;
	for (i = 0; i<size - 1; i++)
	{
		k = i;
		for (j = i + 1; j<size; j++)
			if (d[k]>d[j])
				k = j;
		if (i != k)
		{
			T g;
			g = d[i]; 
			d[i] = d[k]; 
			d[k] = g;
		}
		for (m = 0; m<size; m++) 
			cout << setw(7) << d[m];
		cout << endl;
	}
}

void main()
{
	int q[M], n = M, i;
	srand(time(0));
	for (i = 0; i<n; i++) q[i] = rand() % 100;
	cout << "排序前数组:\n";
	for (i = 0; i<n; i++)
		cout << setw(4) << q[i];
	cout << endl << "数组排序过程演示:\n";
	sortp(q, n);
	cout << "排序后数组:\n";
	for (i = 0; i<n; i++)
		cout << setw(4) << q[i];
	cout << endl;
	float w[M];
	cout << setiosflags(ios::fixed);
	for (i = 0; i<n; i++)
		w[i] = rand() / 100.0;
	cout << "排序前数组:\n";
	for (i = 0; i<n; i++)
		cout << setprecision(2) << setw(7) << w[i];
	cout << endl << "数组排序过程演示:\n";
	sortp(w, n);
	cout << endl << "排序后数组:\n";
	for (i = 0; i<n; i++)
		cout << setprecision(2) << setw(7) << w[i];
	cout << endl; 
	cin.get();
}
