#include "stdafx.h"
#include "CirLinkList.h"
using namespace std;

//构造函数
CirLinkList::CirLinkList()
{
	head = new LNode;
	curr = NULL;
	head->next = head;
	count = 0;
}

//创建有序或无序的带头结点的单循环链表
LNode *CirLinkList::CreateCLinkL(int n, int m, int mark)
{
	ElemType x, a[LEN];
	srand(m);
	for (int i = 0; i<n; i++) 
		a[i] = rand() % 100;
	for (int i = 0; i<n - 1; i++)
	{
		int k = i;
		for (int j = i + 1; j<n; j++)
			if (a[k]>a[j])
				k = j;
		if (k != i)
		{
			x = a[k];
			a[k] = a[i];
			a[i] = x;
		}
	}
	head = new LNode;
	head->next = curr = new LNode;

	for (int i = 0; i<n; i++) 
	{
		if (mark == 1) 
			curr->data = a[i];//升序
		else
			if (mark == -1)
				curr->data = a[n - 1 - i];//降序
			else 
				curr->data = rand() % 100;//无序
			if (i<n - 1) 
			{
				curr->next = new LNode;//不断的创建新结点
				curr = curr->next;
			}
			count++;
	}
	curr->next = head;//形成环
	return head;
}

//清空单循环链表
void CirLinkList::ClearCList()
{
	LNode *cp, *np;
	cp = head->next;
	while (cp != head)
	{
		np = cp->next;
		delete cp; 
		cp = np;
	}
	head = NULL;
}

//求单循环链表长度
int CirLinkList::CListSize()
{
	LNode* p = head->next;
	int i = 0;
	while (p != head)
	{
		i++; 
		p = p->next;
	}
	return i;
}

//检查单循环链表是否为空
bool CirLinkList::CListEmpty()
{
	return head->next == head;
}

//返回指向第pos个结点的指针
LNode *CirLinkList::Index(int pos)
{
	if (pos < 1)
	{
		cerr << "pos is out range!" << endl;
		exit(1);
	}
	LNode* p = head->next;
	int i = 0;
	while (p != head)
	{
		i++;
		if (i == pos) 
			break;
		p = p->next;
	}
	if (p != head)
		return p;
	else 
	{
		cerr << "pos is out range!" << endl;
		return NULL;
	}
}

//返回单循环链表中指定序号的结点值
ElemType CirLinkList::GetElem(int pos)
{
	if (pos<1)
	{
		cerr << "pos is out range!" << endl; 
		exit(1);
	}
	LNode* p = head->next;
	int i = 0;
	while (p != head)
	{
		i++;
		if (i == pos)
			break;
		p = p->next;
	}
	if (p != head)
		return p->data;
	else 
	{
		cerr << "pos is out range!" << endl;
		return pos;
	}
}

//遍历单循环链表
LNode *CirLinkList::TraverseCList()
{
	LNode *p = head->next;
	while (p != head)
	{
		cout << setw(4) << p->data;
		p = p->next;
	}
	cout << endl;
	return head;
}

//当前指针curr指向pos结点并返回curr
LNode *CirLinkList::Reset(int pos)//感觉curr多余，可以用p返回
{
	LNode* p = curr = head->next;
	int i = -1;
	while (p != head)
	{
		i++;
		if (i == pos) 
			break;
		p = p->next; 
		curr = curr->next;
	}
	return curr;
}

//当前指针curr指向下一结点并返回
LNode *CirLinkList::Next()
{
	curr = curr->next;
	return curr;
}

// 判单循环链表当前指针curr==head 否
bool CirLinkList::EndOCList()
{
	return curr == head;
}

//判单循环链表当前指针curr->next是否到达表尾
bool CirLinkList::EndCList()
{
	return curr->next == head;
}

//删除单循环链表当前指针curr->next所指结点并返回其值
ElemType CirLinkList::DeleteNext()
{
	LNode *p = curr->next;
	curr->next = p->next;
	ElemType data = p->data;
	delete p;
	count--;
	return data;
}

//从单循环链表中查找元素
bool CirLinkList::FindCList(ElemType& item)
{
	LNode* p = head->next;
	while (p != head)
		if (p->data == item)
		{
			item = p->data;
			return true;
		}
		else 
			p = p->next;
		return false;
}

//更新单循环链表中的给定元素
bool CirLinkList::UpdateCList(const ElemType &item, ElemType &e)
{
	LNode* p = head->next;
	while (p != head)  //查找元素
		if (p->data == item) 
			break;
		else
			p = p->next;

		if (p == head) 
			return false;
		else 
		{  //更新元素
			p->data = e; 
			return true;
		}
}

//向链表中第pos个结点后插入域值为item的新结点
void CirLinkList::InsertCList(const ElemType& item, int pos)
{
	LNode *newP = new LNode;
	newP->data = item;
	LNode* p = head->next;
	int i = 0;
	while (p != head)
	{
		i++;
		if (i == pos)
			break;
		p = p->next;
	}
	newP->next = p->next;//插值
	p->next = newP; 
	count++;
}

//从链表中删除第pos个结点并返回被删结点的data
ElemType CirLinkList::DeleteCList(int pos)
{
	if (pos < 1)
	{
		cerr << "pos is out range!" << endl;
		exit(1);
	}
	LNode *p = head->next;
	curr = head;
	ElemType data;
	int i = 0;
	while (p != head)
	{
		i++;
		if (i == pos)
			break;
		p = p->next; 
		curr = curr->next;
	}
	if (p != head)
	{
		data = p->data;
		curr->next = p->next;
		delete [] p; //
		count--; 
		return data;
	}
	else
		return pos;
}


