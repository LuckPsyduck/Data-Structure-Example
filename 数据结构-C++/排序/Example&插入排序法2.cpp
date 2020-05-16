// 插入排序法2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<iomanip>
#include<stdlib.h>
#include<time.h>

using namespace std;

#define MAXI 11
typedef int KeyType;
typedef int ElemType;

struct rec 
{
	KeyType key;
	ElemType data;
};

typedef rec sqlist[MAXI];

class charu
{
public:
	charu(sqlist a, int m) :n(m)
	{
		for (int i = 1; i<n; i++)//初始化
			b[i] = a[i];
	}

	void insertsort()
	{
		int i, j, k;
		for (i = 2; i<n; i++)//车轮比较法
		{
			b[0] = b[i];                          //标记 将比较的值放在b[0]
			j = i - 1;             //下标从i=1开始
			while (b[0].key<b[j].key)//从第2个数开始于第一个数比较，将第一个数放在正确的位置，
			{                   //在从第三个开始与前两个比较，将第三个放在正确的位置,依次类推
				b[j + 1] = b[j]; 
				j--;
			}

			b[j + 1] = b[0];
			for (k = 1; k<n; k++)
				cout << setw(4) << b[k].key;
			cout << endl;
		}
	}
	void output()
	{
		for (int i = 1; i<n; i++)
			cout << setw(4) << b[i].key;
		cout << endl;
	}
private:
	sqlist b;
	int n;
};

void main()
{
	sqlist a1; int i, n = MAXI;
	srand((unsigned int)time(0));
	for (i = 1; i<n; i++)
	{
		a1[i].key = rand() % 80;
		a1[i].data = rand() % 100;
	}
	charu px(a1, n);
	cout << "排序前数组:\n";
	px.output();
	cout << "数组排序过程演示:\n";
	px.insertsort();
	cout << "排序后数组:\n";
	px.output();
	cin.get();
}


