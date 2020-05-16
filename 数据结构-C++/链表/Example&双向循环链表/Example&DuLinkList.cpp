#include "stdafx.h"
#include "DuLinkList.h"
using namespace std;

//构造函数
CDuLinkList::CDuLinkList()
{
	head = new DuLNode;
	head->prior = head;
	head->next = head;
	curr = NULL;
	count = 0;
}

//创建有序或无序的带头结点的双向循环链表
DuLNode *CDuLinkList::CreateCLinkL(int n, int m, int mark)
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
	DuLNode *p;
	head = new DuLNode;
	head->prior = NULL;
	head->next = curr = p = new DuLNode;
	curr->prior = head;//将其连接起来

	for (int i = 0; i < n; i++)
	{
		if (mark == 1)
			p->data = a[i];//升序
		else
			if (mark == -1) 
				p->data = a[n - 1 - i];//降序
			else
				p->data = rand() % 100;//无序
			if (i < n - 1)
			{
				curr = curr->next = new DuLNode;
				curr->prior = p;
				p = curr;
			}
			count++;
	}
	head->prior = curr;
	curr->next = head;
	return head;
}

//清空双向循环链表
void CDuLinkList::ClearCList()
{
	DuLNode *cp, *np;
	cp = head->next;
	while (cp != head)
	{
		np = cp->next; 
		delete cp;
		cp = np;
	}
	head = NULL;
}

//求双向循环链表长度
int CDuLinkList::CListSize()
{
	DuLNode* p = head->next;
	int i = 0;
	while (p != head)
	{
		i++; 
		p = p->next;
	}
	return i;
}

//检查双向循环链表是否为空
bool CDuLinkList::CListEmpty()
{
	return head->next == head;
}

//返回指向第pos个结点的指针
DuLNode *CDuLinkList::Index(int pos)
{
	if (pos < 1)
	{
		cerr << "pos is out range!" << endl;
		exit(1);
	}
	DuLNode* p = head->next;
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

//返回双向循环链表中指定序号的结点值
ElemType CDuLinkList::GetElem(int pos)
{
	if (pos < 1)
	{
		cerr << "pos is out range!" << endl;
		exit(1);
	}
	DuLNode* p = head->next;
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

//遍历双向循环链表
void CDuLinkList::TraverseCList()
{
	DuLNode *p = head->next;
	while (p != head)
	{
		cout << setw(4) << p->data;
		p = p->next;
	}
	cout << endl;
}

//当前指针curr指向pos结点并返回curr
DuLNode *CDuLinkList::Reset(int pos)
{
	DuLNode* p = curr = head->next;
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
DuLNode *CDuLinkList::Next()
{
	curr = curr->next;
	return curr;
}

//当前指针curr指向上一结点并返回
DuLNode *CDuLinkList::Prior()
{
	curr = curr->prior;
	return curr;
}

// 判双向循环链表当前指针curr==head 否
bool CDuLinkList::EndOCList()
{
	return curr == head;
}

//判双向循环链表当前指针curr->next是否到达表尾
bool CDuLinkList::EndCList()
{
	return curr->next == head;
}

//判双向循环链表当前指针curr->prior是否到达表尾
bool CDuLinkList::PEndCList()
{
	return curr->prior == head;
}

//删除curr->next所指结点,并返回所删结点的data
ElemType CDuLinkList::DeleteNt()
{
	DuLNode *p = curr->next;
	curr->next = p->next;
	curr->next->next->prior = p->prior;
	ElemType data = p->data;
	delete p;
	count--;
	return data;
}

//从双向循环链表中查找元素
bool CDuLinkList::FindCList(ElemType& item)
{
	DuLNode* p = head->next;
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

//更新双向循环链表中的给定元素
bool CDuLinkList::UpdateCList(const ElemType &item, ElemType &e)
{
	DuLNode* p = head->next;
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

//向链表中第pos个结点前插入域值为item的新结点
void CDuLinkList::InsertCLfront(const ElemType& item, int pos)
{
	DuLNode *newP = new DuLNode;
	newP->data = item;
	DuLNode* p = head->next;
	int i = 0;
	while (p != head)
	{
		i++;
		if (i == pos)
			break;
		p = p->next;
	}
	newP->prior = p->prior;//画出链表图来解释
	p->prior->next = newP;
	newP->next = p;
	p->prior = newP;
	count++;
}

//向链表中第pos个结点后插入域值为item的新结点
void CDuLinkList::InsertCLafter(const ElemType& item, int pos)
{
	DuLNode *newP = new DuLNode;
	newP->data = item;
	DuLNode* p = head->next;
	int i = -1;
	while (p != head)
	{
		i++;
		if (i == pos)
			break;
		p = p->next;
	}
	newP->prior = p->prior;
	p->prior->next = newP;
	newP->next = p;
	p->prior = newP;
}

//从链表中删除第pos个结点并返回被删结点的data
ElemType CDuLinkList::DeleteCList(int pos)
{
	if (pos < 1)
	{
		cerr << "pos is out range!" << endl;
		exit(1);
	}
	DuLNode *p = head->next;
	ElemType data;
	int i = 0;
	while (p != head)
	{
		i++;
		if (i == pos)
			break;
		p = p->next;
	}
	if (p != head)
	{
		data = p->data;
		p->prior->next = p->next;
		p->next->prior = p->prior;
		delete[] p;
		count--; 
		return data;
	}
	else return pos;
}

