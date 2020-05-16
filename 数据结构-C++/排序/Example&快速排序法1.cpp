// 快速排序.cpp : 定义控制台应用程序的入口点。
//主要思想就是，找中间数，使左边的数全部小于所选择的数，右边的数全部大于中间的数，
//然后在将左边的区间重复，右边的区间重复，迭代过程

#include "stdafx.h"
#include<iostream>
#include<iomanip>
#include<stdlib.h>
#include<time.h>
using namespace std;

#define MAXI 10
typedef int KeyType;
typedef int ElemType;

struct rec 
{
	KeyType key; 
	ElemType data;
};

typedef rec sqlist[MAXI];

class kuaisu
{
public:
	kuaisu(sqlist a, int m) :n(m)
	{
		for (int i = 0; i<n; i++)
			b[i] = a[i];
	}

	void quicksort(int s, int t)//.左右
	{
		int i;
		if (s<t) 
		{
			i = part(s, t);//选出中间组员
			quicksort(s, i - 1);
			quicksort(i + 1, t);
		}
		else 
			return;
	}

	int part(int s, int t)
	{
		int i, j; 
		rec p;
		i = s; 
		j = t; 
		p = b[s];//作为base
		while (i<j)
		{
			while (i<j&&b[j].key >= p.key)//从right位置向前找，一直找到比（base）小的数
				j--;
			b[i] = b[j];
			while (i<j&&b[i].key <= p.key) //从left位置向后找，一直找到比（base）大的数
				i++;
			b[j] = b[i];
		}
		b[i] = p;//主员赋值
		output();
		return i;
	}

	void output()
	{
		for (int i = 0; i<n; i++)
			cout << setw(4) << b[i].key;
		cout << endl;
	}
private:
	sqlist b; int n;
};

void main()
{
	sqlist a1; int i, n = MAXI, low = 0, high = 9;
	srand(time(0));
	for (i = 0; i<n; i++)
		a1[i].key = rand() % 80;
	kuaisu px(a1, n);
	cout << "排序前数组:\n";
	px.output();
	cout << "数组排序的过程演示:\n";
	px.quicksort(low, high);
	cout << "排序后数组:\n";
	px.output(); 
	cin.get();
}



