#pragma once

#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<iomanip>

typedef int ElemType;

struct LNode
{
	ElemType data;
	LNode* next;
};

template<class T>
class LHList
{
	LNode** HT;
	int m;
	//求一个元素的散列地址
	int HashAddress(T item, int m)
	{
		return item % m;
	}
public:
	//构造函数,初始化散列表
	LHList(int MaxSize);

	//析构函数,清除一个散列表
	~LHList();

	//基于开放地址法的建散列表
	void CreateHashTable(T A[], int n);

	//向散列表插入一个元素
	void Insert(T item);

	//从散列表中查找一个元素
	T *Search(T item);

	//从散列表中删除一个元素
	bool Delete(T item);

	//显示输出散列表中的所有元素
	void PrintHashList();
};

