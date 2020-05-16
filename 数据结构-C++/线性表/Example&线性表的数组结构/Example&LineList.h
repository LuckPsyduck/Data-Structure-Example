#pragma once

#include<malloc.h>
#include<string.h>
#include<iostream>
#include<iomanip>

#define MaxListSize 20
#define EQUAL 1

typedef struct STU
{
	char name[10];
	char stuno[10];
	int age;
	int score;
}ElemType;

class CLineList
{
public:
	CLineList();
	~CLineList();
private:
	//线性表的数组表示
	ElemType elem[MaxListSize];
	int length;
	int MaxSize;
public:
	//初始化顺序表
	void init(CLineList **L, int ms);
	//删除顺序表
	void DestroyList(CLineList &L) { free(&L); }
	//将顺序表置为空表
	void ClearList() { length = 0; }
	//判断顺序表是否为空表
	bool ListEmpty()
	{
		return length == 0;
	}
	//判断顺序表是否为满
	bool ListFull()
	{
		return length == MaxSize;
	}
	//决定返回表中元素pre_e的前驱
	ElemType PriorElem(ElemType cur_e, ElemType &pre_e);
	// 决定返回表中元素next_e的后继
	ElemType NextElem(ElemType cur_e, ElemType &next_e);
	//从线性表中删除表头、表尾或等于给定值的元素
	bool ListDelete(int, ElemType &e);
	//遍历顺序表
	void ListTraverse();
	//返回顺序表的长度
	int ListLength();
	// 获取顺序表中第i 个元素
	void GetElem(int, ElemType *);
	// 判断顺序表两元素是否相等
	bool EqualList(ElemType *, ElemType *);
	// 判断顺序表两元素是否不等
	bool Less_EqualList(ElemType *, ElemType *);
	//顺序表的查找算法
	bool LocateElem(ElemType, int);
	//更新线性表中的给定元素
	bool UpdateList(ElemType& e, ElemType);
	//顺序表的合并算法
	void MergeList(CLineList *, CLineList *);
	//顺序表的插入算法
	bool ListInsert(int, ElemType &);
	//顺序表的联合算法
	void UnionList(CLineList *, CLineList *);
	//对线性表按升序或降序输出
	void printlist(int);
};

