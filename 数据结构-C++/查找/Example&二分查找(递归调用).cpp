// 二分查找(递归调用).cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include<iostream>
#include<iomanip>
#include<stdlib.h>
using namespace std;

double a[10] = { 1.1,1.3,1.5,1.7,1.9,2.1,2.3,2.5,2.7,2.9 };//已序

void binsrch(int s, int r, double x)
{
	int m;
	m = (s + r) / 2;
	
	if (s > r)
	{
		cout << x << "在序列中未找到!\n";
		exit(-1);
	}
	else if (a[m] == x)
		cout << x << "在序列中找到!\n";
	else if (x > a[m])
		binsrch(m + 1, r, x);
	else
		binsrch(s, m - 1, x);
}

void main()
{
	double x;
	int s = 0, r = 9;
	cout << "输入x:"; 
	cin >> x;
	cout << "查找结果:\n";
	binsrch(s, r, x);
}




