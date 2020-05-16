/*******************************线性表的顺序表示**********************/
#include<stdio.h>                  
#include<malloc.h>
#include<stdlib.h>
#include<math.h>
#define ERROR -1
#define OK 1

typedef  int ElemType;
typedef int Status;

/***********************线性表的动态分配顺序存储结构*********************************/
#define LIST_INIT_SIZE 10 //初始分配量
#define LIST_INCREMENT 2 //分配增量
struct SqList
{
	ElemType *elem;//存储空间的基址
	int length;//当前长度
	int listsize;//当前分配的存储容量(sizeof(ElemType)为单位)
};
/*************************************************************************************/

/****************顺序存储的线性表的基本操作********************************/
void InitList(SqList &L)
{
	L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!L.elem)
		exit(EXIT_FAILURE);
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
}
void DestroyList(SqList &L)
{
	free(L.elem);
	L.elem = NULL;
	L.length = 0;
	L.listsize = 0;
}
//将表为空
void ClearList(SqList &L)
{
	L.length = 0;
}

Status ListEmpty(SqList L)
{
	if (L.length == 0)
		return true;
	else
		return false;
}

int ListLength(SqList L)
{
	return L.length;
}
//用e返回第i个元素的值（1<=i<=Listlength(L)）
Status GetElem(SqList L, int i, ElemType &e)
{
	if (i<1 || i>L.length)
		return ERROR;
	e = *(L.elem + i - 1);
	return OK;
}
//返回L中第一个与e满足关系compare（）的数据元素位置
int LocateElem(SqList L, ElemType e, Status(*compare)(ElemType, ElemType))
{
	int i = 1;
	ElemType *p = L.elem;
	while (i < L.length && !compare(*p++, e))
		++i;
	if (i <= L.length)
		return i;
	else
		return 0;
}
//当cur_e是L的数据元素，且不是第一个，则用pre_e返回它的前驱
Status PriorElem(SqList L, ElemType cur_e, ElemType &pre_e)
{
	int i = 2;
	ElemType *p = L.elem + 1;
	while (i <= L.length&&*p != cur_e)
	{
		p++;
		i++;
	}
	if (i > L.length)
		return ERROR;
	else
	{
		pre_e = *--p;
		return OK;
	}
}

Status NextElem(SqList L, ElemType cur_e, ElemType &next_e)
{
	int i = 1;
	ElemType *p = L.elem;
	while (i < L.length && *p != cur_e)
	{
		p++;
		i++;
	}
	if (i == L.length)
		return ERROR;
	else
	{
		next_e = *++p;
		return OK;
	}
}
//在L中第i个位置之前插入新的元素e,L的长度加1（1<=i<=ListLength(L)+1)
Status ListInsert(SqList &L, int i, ElemType e)
{
	ElemType *newbase, *q, *p;
	if (i<1 || i>L.length + 1)
		return ERROR;
	if (L.length == L.listsize)
	{
		newbase = (ElemType *)realloc(L.elem, (L.listsize + LIST_INCREMENT) * sizeof(ElemType));
		if (!newbase)
			exit(EXIT_FAILURE);
		L.elem = newbase;
		L.listsize += LIST_INCREMENT;
	}
	q = L.elem + i - 1;
	for (p = L.elem + L.length - 1; p >= q; --p)
		*(p + 1) = *p;
	*q = e;
	++L.length;
	return OK;
}
//删除第i个元素
Status ListDelete(SqList &L, int i, ElemType &e)
{
	ElemType *p, *q;
	if (i<1 || i>L.length)
		return ERROR;
	p = L.elem + i - 1;
	e = *p;
	q = L.elem + L.length - 1;
	for (++p; p <= q; ++p)
		*(p - 1) = *p;
	L.length--;
	return OK;
}
//对每个元素调用visit()
void ListTraverse(SqList L, void(*visit)(ElemType))
{
	ElemType *p = L.elem;
	int i;
	for (i = 1; i <= L.length; i++)
		visit(*p++);
	printf("\n");
}
/*************************************************************************************/