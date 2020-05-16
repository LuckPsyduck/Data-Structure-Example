/*******************************循环链表**********************/
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
	L->next = L;//头结点的指针域指向头结点
}
//将L重置为空
void ClearList(LinkList &L)
{
	LinkList p, q;
	L = L->next;//L指向头结点
	p = L->next;//p指向第一个结点
	while (p != L)
	{
		q = p->next;//q指向p的后继
		free(p);
		p = q;
	}
	L->next = L;//头结点的指针域指向自身
}


//销毁线性表L
void DestroyList(LinkList &L)
{
	ClearList(L);
	free(L);//释放L所指的结点
	L = NULL;
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
	LinkList p = L->next;//p指向头结点
	while (p!=L)
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
	LinkList p = L->next->next;//p指向第一个结点

	if (i<=0 || i>ListLength(L))//第i个元素不存在
		return ERROR;
	while (j<i)//顺时针向后查找，直到p指向第i个元素
	{
		j++;
		p = p->next;
	}
	e = p->data;
	return OK;
}
//返回L中第一个与e满足关系compare()的数据元素的位序，诺不存在，则返回0
int LocateElem(LinkList L, ElemType e, Status(*compare)(ElemType, ElemType))
{
	int i = 0;
	LinkList p = L->next->next;
	while (p !=L->next)//p未指向头结点
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
	LinkList q, p = L->next->next;
	q = p->next;//q指向p的后继
	while (q!=L->next)//p未到表尾
	{
		if (q->data == cur_e)//p的后继为cur_e
		{
			pre_e = p->data;//将p所指的元素的值赋值给pre_e
			return OK;
		}
		p = q;//p向后移
		q = q->next;
	}
	return ERROR;//操做失败
}

Status NextElem(LinkList L, ElemType cur_e, ElemType &next_e)
{
	LinkList p = L->next->next;
	while (p!=L)//p未到表尾
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
//第i个元素之前插入
Status ListInsert(LinkList &L, int i, ElemType e)
{
	LinkList p = L->next, s;
	int j = 0;//计数器初值为0
	if (i <= 0 || i > ListLength(L) + 1)
		return ERROR;
	while (j < i - 1)//寻找第i-1个结点
	{
		j++;
		p = p->next;
	}
	s = (LinkList)malloc(sizeof(LNode));//生成新结点
	s->data = e;
	s->next = p->next;
	p->next = s;
	if (p == L)//插在表尾
		L = s;//L指向新的尾结点
	return OK;
}
//删除第i个元素，并由e返回其值
Status ListDelete(LinkList &L, int i, ElemType &e)
{
	int j = 0;
	LinkList q, p = L->next;
	if (i <= 0 || i > ListLength(L))
		return ERROR;
	while (j < i - 1)//寻找第i-1个结点
	{
		j++;
		p = p->next;
	}
	q = p->next;//q指向待删除结点，p的后继
	p->next = q->next;//待删除结点的前驱指向待删除结点的后继
	e = q->data;
	if (L == q)//删除的是表尾元素
		L = p;//L指向新的表尾元素
	free(q);//释放待删除结点
	return OK;
}

void ListTraverse(LinkList L, void(*visit)(ElemType))
{
	LinkList p = L->next->next;//p指向首元结点
	while (p!=L->next)//p不指向头结点
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
	LinkList p, q;
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
	LinkList p = NULL, q;
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
			pc = pa;
			pa = pa->next;
		}
		else
		{
			pc->next = pb;
			pc = pb;
			pb = pb->next;
		}
	pc->next = pa ? pa : pb;//插入剩余段
	free(Lb);
	Lb = NULL;
}
