#pragma once

#include<iostream>
#include<iomanip>
#include<stdlib.h>
using namespace std;

#define LEN 30
//定义ElemType为int
typedef int ElemType;

//单链表中结点的类型
typedef struct LNode {
	ElemType data;//值域
	LNode *next;  //指针域
}LNode;

class CLinkList
{
	LNode *head;
public:
	//不带形参构造函数
	CLinkList();

	//带一个形参构造函数
	CLinkList(int);

	//带三个形参构造函数,n是初始化元素个数,m是基
	//本数,mark=0不排序,mark>0升序,mark<0降序
	CLinkList(int n, int m, int mark = 0);

	//复制构造函数
	CLinkList(CLinkList& HL);

	//析构函数
	~CLinkList();

	//清空单链表
	void ClearList();

	//求单链表长度
	int ListSize();

	//检查单链表是否为空
	bool ListEmpty();

	//返回单链表中指定序号的结点值
	ElemType GetElem(int pos);

	//遍历单链表
	void TraverseList(void f(ElemType &));

	//从单链表中查找元素
	bool FindList(ElemType& item);

	//更新单链表中的给定元素
	bool UpdateList(const ElemType& item, ElemType e);

	//向单链表插入元素,mark=0插在表首,否则插在表尾
	void InsertList(ElemType item, int mark);

	//从单链表中删除元素 , mark为要删除的第几个元素
	bool DeleteList(ElemType& item, int mark);

	//对单链表进行有序排列 mark>0升序,否则降序
	void pailie(int mark = 1);//Sort

	//单链表la 和lb 的元素按值非递减排列,两个单链表
	//合并后的链表也是一个有序的
	void MergeList_L(CLinkList &la, CLinkList &lb);

	//对单链表进行有序输出,mark=0不排序,mark>0升序,mark<0降序
	void OrderOutputList(int mark = 0);
};

