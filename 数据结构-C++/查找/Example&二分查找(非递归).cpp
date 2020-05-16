// 二分查找(非递归).cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<iomanip>
#include<stdlib.h>
using namespace std;

void binsrch(int a[], int n, int x)
{
	int mid, top = 0, bot = n - 1, find = 0, m = 0;
	do 
	{
		m = m + 1;
		mid = (top + bot) / 2;
		if (a[mid] == x)
		{
			cout << x << "在序列中找到!\n";
			find = 1;
		}
		else if (x < a[mid])
			bot = mid - 1;
		else if (x > a[mid]) 
			top = mid + 1;
	} while ((top <= bot) && (find == 0));
	if (find == 0)  
		cout << x << "在序列中未找到!\n";
	cout << "查找次数:" << m << endl;
}

void main()
{
	int b[] = { 1,3,5,7,9,10,12,15,17,19 };
	int x, n = sizeof(b)/sizeof(b[0]);
	cout << "输入要查找的x:"; 
	cin >> x;
	cout << "查找结果:\n";
	binsrch(b, n, x);
}



