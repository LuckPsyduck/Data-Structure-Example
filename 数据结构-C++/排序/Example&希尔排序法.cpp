// 希尔排序法.cpp : 定义控制台应用程序的入口点。
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

class xier
{
public:
	xier(sqlist a, int m) :n(m)
	{
		for (int i = 1; i<n; i++) 
			b[i] = a[i];//初始化
	}

	void shellsort()
	{
		int i, j, gap, k; 
		rec x; 
		gap = n / 2;//步长
		while (gap>0)
		{
			for (i = gap + 1; i<n; i++)//分组
			{
				j = i - gap;                //组中的另外一个元素
				while (j>0)
					if (b[j].key>b[j + gap].key)//组中的元素之间的插入排序
					{
						x = b[j]; 
						b[j] = b[j + gap];
						b[j + gap] = x;
						j = j - gap;
					}
					else 
						j = 0;

					for (k = 1; k<n; k++)
						cout << setw(4) << b[k].key;
					cout << endl;
			}
			gap = gap / 2;//换步长 //例如10个元素的话，则为 5 2 1
		}// 5个组，每组两个元素， 2个组 每个组5个元素 1个组 10个元素
	}

	void output()
	{
		for (int i = 1; i<n; i++)
			cout << setw(4) << b[i].key;
		cout << endl;
	}

private:sqlist b; int n;
};

void main()
{
	sqlist a1; int i, n = MAXI;
	srand((unsigned int)time(0));
	for (i = 1; i<n; i++)
	{
		a1[i].key = rand() % 100;
		a1[i].data = rand() % 80;
	}
	xier px(a1, n);
	cout << "排序前数组:\n";
	px.output();
	cout << "数组排序过程演示:\n";
	px.shellsort();
	cout << "排序后数组:\n";
	px.output(); 
	cin.get();
}



