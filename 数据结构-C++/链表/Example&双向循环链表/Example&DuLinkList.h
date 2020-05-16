#pragma once
#include<iostream>
#include<stdlib.h>
#include<iomanip>

typedef int ElemType;
//双向链表结点的类型定义
typedef struct DuLNode {
	ElemType  data;
	struct DuLNode *prior;//左指针
	struct DuLNode *next;//右指针
}DuLNode;

#define LEN 20

class CDuLinkList
{
public:
	CDuLinkList();
	~CDuLinkList() { delete head; }

private:
	DuLNode *head;//指向表头的指针
	DuLNode *curr;//当前结点指针
	int count;// 双向循环链表的结点个数

public:

	//创建有序或无序的带头结点的双向循环链表
	DuLNode *CreateCLinkL(int, int, int mark = 0);

	//清空单循环链表
	void ClearCList();

	//求双向循环链表长度
	int CListSize();

	//检查双向循环链表是否为空
	bool CListEmpty();

	//返回指向第pos个结点的指针
	DuLNode *Index(int pos);

	//返回双向循环链表中指定序号的结点值
	ElemType GetElem(int pos);

	//遍历双向循环链表
	void TraverseCList();

	//当前指针curr指向pos结点并返回curr
	DuLNode *Reset(int pos = 0);

	//当前指针curr指向下一结点并返回
	DuLNode *Next();

	//当前指针curr指向上一结点并返回
	DuLNode *Prior();

	// 判双向循环链表当前指针curr==head 否
	bool EndOCList();

	//判双向循环链表当前指针curr->next是否到达表尾
	bool EndCList();

	//判双向循环链表当前指针curr->prior是否到达表尾
	bool PEndCList();

	//删除curr->next所指结点,并返回所删结点的data
	ElemType DeleteNt();

	//从双向循环链表中查找元素
	bool FindCList(ElemType& item);

	//更新双向循环链表中的给定元素
	bool UpdateCList(const ElemType &item, ElemType &e);

	//向链表中第pos个结点前插入域值为item的新结点
	void InsertCLfront(const ElemType& item, int pos);

	//向链表中第pos个结点后插入域值为item的新结点
	void InsertCLafter(const ElemType& item, int pos);

	//从链表中删除第pos个结点并返回被删结点的data
	ElemType DeleteCList(int pos);
};

