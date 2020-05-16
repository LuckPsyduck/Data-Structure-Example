/*******************************线性表的链式表示**********************/
#include<stdio.h>                  
#include<malloc.h>
#include<stdlib.h>
#include<math.h>
#define ERROR -1
#define OK 1

#define LIST_INIT_SIZE 10 //初始分配量
#define LIST_INCREMENT 2 //分配增量

typedef  int ElemType;
typedef int Status;

struct LNode
{
	ElemType data;
	LNode *next;
};
typedef LNode *LinkList;

/**/
void InitList(LinkList &L)
{
	L = (LinkList)malloc(sizeof(LNode));/*产生头结点，并使L指向头结点*/
	if (!L)
		exit(EXIT_FAILURE);
	L->next = NULL;
}
/***************************销毁线性表L*****************************/
void DestroyList(LinkList &L)
{
	LinkList q;
	while (L)
	{
		q = L->next;
		free(L);
		L = q;
	}
}
/*******************************将L重置为空*****************************/
void ClearList(LinkList L)
{
	LinkList p = L->next;//p指向第一个结点
	L->next = NULL;
	DestroyList(p);
}

Status ListEmpty(LinkList L)
{
	if (L->next)
		return false;
	else
		return true;
}

int ListLength(LinkList L)
{
	int i = 0;
	LinkList p = L->next;
	while (p)
	{
		i++;
		p = p->next;
	}
	return i;
}
/**********************当第i个元素存在时，其值赋给e并返回*******************/
Status GetElem(LinkList L, int i, ElemType &e)
{
	int j = 1;
	LinkList p = L->next;
	while (p&&j<i)
	{
		j++;
		p = p->next;
	}
	if (!p || j > i)
		return ERROR;
	e = p->data;
	return OK;
}
/*************返回L中第一个与e满足关系compare()的数据元素的位序，诺不存在，则返回0***************/
int LocateElem(LinkList L, ElemType e, Status(*compare)(ElemType, ElemType))
{
	int i = 0;
	LinkList p = L->next;
	while (p)
	{
		i++;
		if (compare(p->data, e))
			return i;
		p = p->next;
	}
	return 0;
}

Status PriorElem(LinkList L, ElemType cur_e, ElemType &pre_e)
{
	LinkList q, p = L->next;
	while (p->next)
	{
		q = p->next;
		if (q->data == cur_e)
		{
			pre_e = p->data;
			return OK;
		}
		p = q;
	}
	return ERROR;//操做失败
}

Status NextElem(LinkList L, ElemType cur_e, ElemType &next_e)
{
	LinkList p = L->next;
	while (p->next)
	{
		if (p->data == cur_e)
		{
			next_e = p->next->data;
			return OK;
		}
		p = p->next;
	}
	return ERROR;
}
/**********************第i个元素之前插入****************************/
Status ListInsert(LinkList L, int i, ElemType e)
{
	int j = 0;
	LinkList s, p = L;
	while (p&&j < i - 1)
	{
		j++;
		p = p->next;
	}
	if (!p || j > i - 1)
		return ERROR;
	s = (LinkList)malloc(sizeof(LNode));
	s->data = e;
	s->next = p->next;
	p->next = s;
	return OK;
}
/******************************删除第i个元素，并由e返回其值************/
Status ListDelete(LinkList L, int i, ElemType &e)
{
	int j = 0;
	LinkList q, p = L;
	while (p->next&&j < i - 1)
	{
		j++;
		p = p->next;
	}
	if (!p->next || j > i - 1)
		return ERROR;
	q = p->next;
	p->next = q->next;
	e = q->data;
	free(q);
	return OK;
}

void ListTraverse(LinkList L, void(*visit)(ElemType))
{
	LinkList p = L->next;
	while (p)
	{
		visit(p->data);
		p = p->next;
	}
	printf("\n");
}


/*逆位序（结点插在表头）输入n个元素的值，建立带表头结点的单链线性表L*/

void CreateList(LinkList &L, int n)
{
	int i;
	LinkList p/*, q*/;
	L = (LinkList)malloc(sizeof(LNode));
	L->next = NULL;
	printf("'请输入%3d个数据\n", n);
	for (i = n; i > 0; --i)
	{
		p = (LinkList)malloc(sizeof(LNode));//生成新结点
		scanf("%d", &p->data);
		p->next = L->next;//将新结点插在表头
		L->next = p;//头结点指向新结点
	}
}

/*正位序（结点插在表尾）输入n个元素的值，建立带表头结点的单链线性表*/
void CreateList1(LinkList &L, int n)
{
	int i;
	LinkList p=NULL,q;
	L = (LinkList)malloc(sizeof(LNode));
	L->next = NULL;
	q = L;//q指向空表头的头结点
	printf("'请输入%3d个数据\n", n);
	for (i = 1; i <= n; i++)
	{
		p = (LinkList)malloc(sizeof(LNode));
		scanf("%d", &p->data);
		q->next = p;//将新结点插在表尾
		q = q->next;//q指向尾结点
	}
	p->next = NULL;//最后结点的指针域为空
}

/*************非递减排列****************/

void MergeList(LinkList La, LinkList &Lb, LinkList &Lc)
{
	LinkList pa = La->next, pb = Lb->next, pc;
	Lc = pc = La;//用La的头结点作为Lc的头结点
	while (pa&&pb)
		if (pa->data <= pb->data)
		{
			pc->next = pa;
			pc = pa;//pc指向表LC的最后一个结点，相当于指向现在Lc的最后一个
			pa = pa->next;
		}
		else
		{
			pc->next = pb;
			pc = pb;//pc指向表Lc的最后一个结点
			pb = pb->next;
		}
	pc->next = pa ? pa : pb;//插入剩余段
	free(Lb);
	Lb = NULL;
}