#pragma once
#include<iomanip>
#include<iostream>
#include<stdlib.h>

#define LEN 20
typedef int ElemType;

//单循环链表中结点的类型
typedef struct Lnode 
{
	ElemType data;   //值域
	Lnode* next;     //指针域
}LNode;

class CirLinkList
{
public:
	CirLinkList() ;
	~CirLinkList() { delete head; }

private:
	LNode *head;//指向表头的指针
	LNode *curr;//当前结点指针
	int count;// 单循环链表的结点个数

public:
	//创建有序或无序的带头结点的单循环链表
	LNode *CreateCLinkL(int, int, int mark = 0);

	//清空单循环链表
	void ClearCList();

	//求单循环链表长度
	int CListSize();

	//检查单循环链表是否为空
	bool CListEmpty();

	//返回指向第pos个结点的指针
	LNode * Index(int pos);

	//返回单循环链表中指定序号的结点值
	ElemType GetElem(int pos);

	//遍历单循环链表
	LNode * TraverseCList();

	//当前指针curr指向pos结点并返回curr
	LNode * Reset(int pos = 0);

	//当前指针curr指向下一结点并返回
	LNode * Next();

	// 判单循环链表当前指针curr==head 否
	bool EndOCList();

	//判单循环链表当前指针curr->next是否到达表尾
	bool EndCList();

	//删除单循环链表当前指针curr->next所指结点并返回其值
	ElemType DeleteNext();

	//从单循环链表中查找元素
	bool FindCList(ElemType& item);

	//更新单循环链表中的给定元素
	bool UpdateCList(const ElemType &item, ElemType &e);

	//向链表中第pos个结点后插入域值为item的新结点
	void InsertCList(const ElemType& item, int pos);

	//从链表中删除第pos个结点并返回被删结点的data
	ElemType DeleteCList(int pos);
};

