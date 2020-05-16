#pragma once
#include<iostream>
#include<iomanip>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
//将函数声明在类中，定义在程序中，直接调用类的成员函数
#define EQUAL 1
#define LIST_INIT_SIZE 30
#define LISTINCREMENT 10

typedef struct STU {
	char name[10];
	char stuno[8];
	int age;
	int score;
}ElemType;

//线性表的动态分配顺序存储结构 
class CLineList
{
public:
	CLineList();
	~CLineList();
private:
	ElemType *elem;//存储空间基址
	int length;   //当前长度
	int listsize;//当前分配的存储容量以一数据元素存储长度为单位
	
public:
	//初始化顺序表
	void init(CLineList *);

	//删除顺序表
	void DestroyList(CLineList &L) { free(&L); }

	//将顺序表置为空表
	void ClearList() { length = 0; }

	//判断顺序表是否为空表
	bool ListEmpty()
	{
		if (length == 0) 
			return true;
		else 
			return false;
	}

	//判断顺序表是否为满
	bool ListFull()
	{
		return length == listsize;
	}

	//决定返回表中元素pre_e的前驱
	ElemType PriorElem(ElemType cur_e, ElemType &pre_e);

	// 决定返回表中元素next_e的后继
	ElemType NextElem(ElemType cur_e, ElemType &next_e);

	//删除顺序表中第i 个元素
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
	bool ListInsert(int, ElemType);

	//顺序表的联合算法
	void UnionList(CLineList *, CLineList *);

	//对线性表按升序或降序输出
	void printlist(int);
};

