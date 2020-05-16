#pragma once

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

#define DestroyList ClearList

void InitList(LinkList &L)
{
	L = NULL;
}

void ClearList(LinkList &L)
{
	LinkList p;
	while (L)
	{
		p = L;
		L = L->next;
		free(p);
	}
}

Status ListEmpty(LinkList L)
{
	if (L)
		return false;
	else
		return true;
}

int ListLength(LinkList L)
{
	int i = 0;
	LinkList p = L;
	while (p)
	{
		i++;
		p=p->next;
	}
	return i;
}

Status GetElem(LinkList L, int i, ElemType &e)
{
	int j = 1;
	LinkList p = L;
	if (i < 1)
		return ERROR;
	while (j<i&&p)
	{
		j++;
		p = p->next;
	}
	if (j == i&&p)
	{
		e = p->data;
		return OK;
	}
	return ERROR;
}

int LocateElem(LinkList L, ElemType e, Status(*compare)(ElemType, ElemType))
{
	int i = 0;
	LinkList p = L;
	while (p)
	{
		i++;
		if (compare(p->data, e))
			return i;
		p = p->next;
	}
	return 0;
}

Status ListInsert(LinkList &L, int i, ElemType e)
{
	int j = 1;
	LinkList s, p = L;
	if (i < 1)
		return ERROR;
	s = (LinkList)malloc(sizeof(LNode));
	s->data = e;
	if (i == 1)
	{
		s->next = L;
		L = s;
	}
	else
	{
		while (p&&j<i-1)
		{
			j++;
			p = p->next;
		}
		if (!p)
			return ERROR;
		s->next = p->next;
		p->next = s;
	}
	return OK;
}

Status ListDelete(LinkList &L, int i, ElemType &e)
{
	int j = 1;
	LinkList q, p = L;
	if (!L)
		return ERROR;
	else if(i==1)
	{
		L = p->next;
		e = p->data;
		free(p);
	}
	else
	{
		while (p->next&&j<i-1)
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
	}
	return OK;
}

void ListTraverse(LinkList L, void(*visit)(ElemType))
{
	LinkList p = L;
	while (p)
	{
		visit(p->data);
		p = p->next;
	}
	printf("\n");
}

Status PriorElem(LinkList L, ElemType cur_e, ElemType &pre_e)
{
	LinkList q, p = L;
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
	return ERROR;
}

Status NextElem(LinkList L, ElemType cur_e, ElemType &next_e)
{
	LinkList p = L;
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