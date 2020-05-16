// 堆排序.cpp : 定义控制台应用程序的入口点。
//
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

class duifa 
{
public:
	duifa(sqlist b)
	{
		for (int i = 1; i<M; i++) 
			r[i] = b[i];
	}
	void output()
	{
		for (int i = 1; i<M; i++)
			cout << setw(4) << r[i].key;
		cout << endl;
	}
	//完全二叉树结构
	void sift(int s, int m)//由下往上进行调整,调整每个结点(有叶子的)
	{
		int j; rec x;
		x = r[s];
		for (j = 2 * s; j <= m; j *= 2)//j为左结点
		{
			if (j<m && (r[j].key<r[j + 1].key))//左右结点比较
				++j;//j指向大的右结点
			if (!(x.key<r[j].key)) 
				break;
			r[s] = r[j]; //最大的给根结点
			s = j;
		}
		r[s] = x;//元素互换
	}

	void heapsort(int m)
	{
		int i; rec w;
		for (i = m / 2; i>0; --i) //给树根结点,由下往上给出
			sift(i, m);//构造堆,将最大的选出放在[1]
		for (i = m; i>=1; --i)
		{
			w = r[i]; 
			r[i] = r[1];
			r[1] = w;
			output();
			sift(1, i - 1);
		}
	}

private:sqlist r;
};
void main()
{
	sqlist a; int i;
	srand(time(0));
	for (i = 1; i<M; i++)//从下标1开始
		a[i].key = rand() % 80;
	duifa dx(a);
	cout << "排序前数组:\n";
	dx.output();
	cout << "数组排序的过程演示:\n";
	dx.heapsort(M-1);
	cout << "排序后数组:\n";
	dx.output(); 
	cin.get();
}


