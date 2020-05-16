/*******************************双向链表**********************/
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

struct DuLNode
{
	ElemType data;
	DuLNode *next,*prior;
};
typedef DuLNode *DuLinkList;

/**/
void InitList(DuLinkList &L)
{
	L = (DuLinkList)malloc(sizeof(DuLNode));/*产生头结点，并使L指向头结点*/
	if (L)
		L->next = L->prior = L;
	else
		exit(EXIT_FAILURE);
}

//将L重置为空
void ClearList(DuLinkList L)
{
	DuLinkList p=L->next;//p指向第一个结点

	while (p != L)//p未指向头结点
	{
		p = p->next;
		free(p->prior);//释放p的前驱结点
	}
	L->next = L->prior=L;//头结点的指针域均指向自身
}


//销毁线性表L
void DestroyList(DuLinkList &L)
{
	ClearList(L);
	free(L);//释放头结点
	L = NULL;
}

Status ListEmpty(DuLinkList L)
{
	if (L->next==L&&L->prior==L)
		return true;
	else
		return false;
}

int ListLength(DuLinkList L)
{
	int i = 0;
	DuLinkList p = L->next;//p指向第一个结点
	while (p != L)//p未指向头结点
	{
		i++;
		p = p->next;
	}
	return i;
}
//当第i个元素存在时，其值赋给e并返回
Status GetElem(DuLinkList L, int i, ElemType &e)
{
	int j = 1;
	DuLinkList p = L->next;//p指向第一个结点

	while (p != L&&j < i)//直到p指向第一个元素或P指向头结点
	{
		j++;
		p = p->next;
	}
	if (p == L || j > i)
		return ERROR;
	e = p->data;
	return OK;
}
//返回L中第一个与e满足关系compare()的数据元素的位序，诺不存在，则返回0
int LocateElem(DuLinkList L, ElemType e, Status(*compare)(ElemType, ElemType))
{
	int i = 0;
	DuLinkList p = L->next;//p指向第一个元素
	while (p != L)//p未指向头结点
	{
		i++;
		if (compare(p->data, e))
			return i;
		p = p->next;
	}
	return 0;
}

Status PriorElem(DuLinkList L, ElemType cur_e, ElemType &pre_e)
{
	DuLinkList  p = L->next->next;//p指向第二个元素

	while (p != L)//p未指向头结点
	{
		if (p->data == cur_e)//p的指向值为cur_e的结点
		{
			pre_e = p->prior->data;//将p的前驱结点的值赋予pre_e
			return OK;
		}
		p = p->next;
	}
	return ERROR;//操做失败
}
//诺cur_e是L的数据元素，且不是最后一个，则用next_e返回它的后继
Status NextElem(DuLinkList L, ElemType cur_e, ElemType &next_e)
{
	DuLinkList p = L->next->next;//p指向第二个元素
	while (p != L)//p未指向头结点
	{
		if (p->prior->data == cur_e)//p所指的结点的前驱的值为cur_e
		{
			next_e = p->data;
			return OK;
		}
		p = p->next;
	}
	return ERROR;
}

//返回第i个元素的地址，i为0，返回头结点的地址
DuLinkList GetElemP(DuLinkList L, int i)
{
	int j;
	DuLinkList p = L;//指向头结点
	if (i<0 || i>ListLength(L))
		return NULL;
	for (j = 1; j <= i; j++)
		p = p->next;
	return p;
}
//第i个元素之前插入（1<=i<=length(L)+1）
Status ListInsert(DuLinkList &L, int i, ElemType e)
{
	DuLinkList p , s;

	if (i <1 || i > ListLength(L) + 1)
		return ERROR;
	
	p = GetElemP(L, i - 1);//在L中确定第i个结点前驱的位置指针p
	if (!p)
		return ERROR;

	s = (DuLinkList)malloc(sizeof(DuLNode));//生成新结点
	s->data = e;
	s->prior = p;//新结点的前驱为第i-1个结点
	s->next = p->next;//新结点的后继为第i个结点
	p->next->prior = s;//第i个结点的前驱指向新结点
	p->next = s;//第i-1个结点的后继指向新结点
	return OK;
}
//删除第i个元素，并由e返回其值
Status ListDelete(DuLinkList L, int i, ElemType &e)
{
	DuLinkList p ;
	if (i <1)
		return ERROR;
	p = GetElemP(L, i);//确定第i个元素的位置指针p
	if (!p)
		return ERROR;
	e = p->data;
	p->prior->next = p->next;//第i-1个结点的后继指向原第i+1个结点
	p->next->prior = p->prior;//原第i+1个结点的前驱指向第i-1个结点
	free(p);//释放第i个结点
	return OK;
}

void ListTraverse(DuLinkList L, void(*visit)(ElemType))
{
	DuLinkList p = L->next;//p指向首元结点
	while (p != L)//p不指向头结点
	{
		visit(p->data);
		p = p->next;
	}
	printf("\n");
}


void ListTraverseBack(DuLinkList L, void(*visit)(ElemType))
{
	DuLinkList p = L->prior;//p指向尾结点
	while (p != L)//p不指向头结点
	{
		visit(p->data);
		p = p->prior;
	}
	printf("\n");
}
