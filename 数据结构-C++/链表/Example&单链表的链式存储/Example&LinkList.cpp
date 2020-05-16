#include "stdafx.h"
#include "LinkList.h"


CLinkList::CLinkList()//不带形参构造函数
{
	head = new LNode;
	head->next = NULL;
}

CLinkList::CLinkList(int d1)//带一个形参构造函数
{
	head = new LNode;
	head->next = new LNode;
	head->next->data = d1;
	head->next->next = NULL;
}

//带三个形参构造函数 //n是初始化元素个数,m是基本数,mark=0不排序,mark>0升序,mark<0降序
CLinkList::CLinkList(int n, int m, int mark)
{
	int i, j;
	ElemType a[LEN + 1];
	for (i = 1; i <= n; i++)
		a[i] = (m + rand()) % 100;
	for (i = 1; i < n; i++)
		for (j = 1; j <= n - i; j++)//排序算法
		{
			int t;
			if (mark>0 && a[j]>a[j + 1] || mark<0 && a[j]<a[j + 1])
			{
				t = a[j + 1];
				a[j + 1] = a[j];
				a[j] = t;
			}
		}
	head = new LNode;
	LNode *p = head, *q;
	for (i = 1; i <= n; i++)//给链表赋值
	{
		q = new LNode;
		q->data = a[i];
		p->next = q;
		p = p->next;
	}
	p->next = NULL;
}

CLinkList::CLinkList(CLinkList& HL)//复制构造函数
{
	head = new LNode;
	head->next = NULL;
	LNode *p2 = HL.head->next, *p1 = head, *q;
	while (p2)
	{
		q = new LNode;
		q->data = p2->data;
		p1->next = q;
		p1 = q;  //给头结点                 //构造P1链表，相当于完全复制p2链表的
		p2 = p2->next;
	}
	p1->next = NULL;
}

CLinkList::~CLinkList()//析构函数
{
	LNode *p = head->next, *q;
	while (p)
	{
		q = p->next;
		free(p);
		p = q;
	}
}

void CLinkList::ClearList()//清空单链表
{
	LNode *p = head->next, *q;
	while (p)
	{
		q = p->next;
		free(p);
		p = q;
	}
	head->next = NULL;
}

int CLinkList::ListSize()//求单链表长度
{
	LNode *p = head->next;
	int i = 0;
	while (p)
	{
		i++;
		p = p->next;
	}
	return i;
}

bool CLinkList::ListEmpty()//检查单链表是否为空
{
	return ListSize() == 0;
}

//返回单链表中指定序号的结点值
ElemType CLinkList::GetElem(int pos)
{
	LNode *p = head->next;
	int i = 1;
	while (p)
	{
		if (i++ == pos)
			return p->data;
		p = p->next;
	}
	return head->data;
}

void CLinkList::TraverseList(void f(ElemType &))//遍历单链表
{
	LNode *p = head->next;
	while (p)
	{
		f(p->data);
		p = p->next;
	}
}

bool CLinkList::FindList(ElemType& item)//从单链表中查找元素
{
	LNode *p = head->next;
	while (p)
	{
		if (p->data == item)
			return 1;
		p = p->next;
	}
	return 0;
}

//更新单链表中的给定元素
bool CLinkList::UpdateList(const ElemType &item, ElemType e)
{
	LNode *p = head->next;
	bool flag = 0;
	while (p)
	{
		if (p->data == item)
		{
			p->data = e;
			flag = 1;
		}
		p = p->next;
	}
	return flag;
}

//向单链表插入元素
void CLinkList::InsertList(ElemType item, int mark)	//向单链表插入元素,mark=0插在表首,否则插在表尾
{
	LNode *q = new LNode;
	q->data = item;
	if (mark == 0)
	{
		q->next = head->next;
		head->next = q;
		return;
	}
	LNode *p = head;
	while (p->next)
	{
		p = p->next;
	}
	q->next = NULL;
	p->next = q;
}

//从单链表中删除元素
bool CLinkList::DeleteList(ElemType& item, int mark)//从单链表中删除元素 , mark为要删除的第几个元素
{
	if (ListEmpty() || mark<1 || mark>ListSize())
		return 0;
	LNode *p = head, *q;
	for (int i = 0; i<mark - 1; i++)
		p = p->next;
	item = p->next->data;
	q = p->next->next;
	free(p->next);
	p->next = q;
	return 1;
}

//对单链表进行有序排列mark>0升序,否则降序
void CLinkList::pailie(int mark)
{
	ElemType a[LEN + 1];
	LNode *p = head->next;
	int k;
	for (k = 1; p != NULL; k++, p = p->next)
		a[k] = p->data;
	k--;
	for (int i = 1; i<k; i++)
		for (int j = 1; j <= k - i; j++)
		{
			int t;
			if (mark>0 && a[j]>a[j + 1] || mark<0 && a[j]<a[j + 1])
			{
				t = a[j + 1];
				a[j + 1] = a[j];
				a[j] = t;
			}
		}
	p = head->next;
	for (int j = 1; j <= k; j++, p = p->next)
		p->data = a[j];
}

//单链表la 和lb 的元素按值非递减排列,两个单链表
//合并后的链表也是一个有序的
void CLinkList::MergeList_L(CLinkList &la, CLinkList &lb)
{
	LNode *pa = la.head->next, *pb = lb.head->next, *p = head;
	while (pa && pb)
	{
		LNode *q = new LNode;
		if (pa->data <pb->data)
		{
			q->data = pa->data;
			pa = pa->next;
			p->next = q;
			p = q;
		}
		else
		{
			q->data = pb->data;
			pb = pb->next;
			p->next = q;
			p = q;
		}
	}
	while (pa)
	{
		LNode *q = new LNode;
		q->data = pa->data;
		pa = pa->next;
		p->next = q;
		p = q;
	}
	while (pb)
	{
		LNode *q = new LNode;
		q->data = pb->data;
		pb = pb->next;
		p->next = q;
		p = q;
	}
	p->next = NULL;
}

//对单链表进行有序输出,mark=0不排序,mark>0升序,mark<0降序
void CLinkList::OrderOutputList(int mark)
{
	ElemType a[LEN + 1];
	LNode *p = head->next;
	int k;
	for (k = 1; p != NULL; k++, p = p->next)
		a[k] = p->data;
	k--;
	for (int i = 1; i<k; i++)
		for (int j = 1; j <= k - i; j++)
		{
			int t;
			if (mark>0 && a[j]>a[j + 1] || mark<0 && a[j]<a[j + 1])
			{
				t = a[j + 1];
				a[j + 1] = a[j];
				a[j] = t;
			}
		}
	for (int j = 1; j <= k; j++)
		cout << a[j] << "  ";
}
