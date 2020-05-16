/*******************************二叉链表结构*******************************/
#include<stdio.h>                  
#include<malloc.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#define ERROR -1
#define OK 1

typedef int Status;
typedef char TElemType;//结点元素类型

#define Nil ' '                       //char
/*#define Nil 0 */                       //int

typedef struct BiNode
{
	TElemType data;
	BiNode *lchild, *rchild;
}BiTNode,*BiTree;

/*******************二叉链表的基本操作*************************************/
#define ClearBiTree DestroyBiTree
void InitBiTree(BiTree &T)
{
	T = NULL;
}

void DestroyBiTree(BiTree &T)
{
	if (T)
	{
		DestroyBiTree(T->lchild);
		DestroyBiTree(T->rchild);
		free(T);
		T = NULL;
	}
}

void PreOrderTraverse(BiTree T, void(Visit)(TElemType))
{
	if (T)
	{
		Visit(T->data);
		PreOrderTraverse(T->lchild,Visit);
		PreOrderTraverse(T->rchild,Visit);
	}
}

void InOrderTraverse(BiTree T, void(Visit)(TElemType))
{
	if (T)
	{
		InOrderTraverse(T->lchild, Visit);
		Visit(T->data);
		InOrderTraverse(T->rchild, Visit);
	}
}

/**************************二叉链表的基本操作******************************/
Status BiTreeEmpty(BiTree T)
{
	if (T)
		return false;
	else
		return true;
}

int BiTreeDepth(BiTree T)
{
	int i, j;
	if (!T)
		return 0;
	i = BiTreeDepth(T->lchild);
	j = BiTreeDepth(T->rchild);
	return i > j ? i + 1 : j + 1;//加上根的一层
}

TElemType Root(BiTree T)
{
	if (BiTreeEmpty(T))
		return Nil;
	else
		return T->data;
}

TElemType Value(BiTree p)
{
	return p->data;
}

void Assign(BiTree p, TElemType value)
{
	p->data = value;
}
/**************************链队列*************************/
typedef BiTree QElemType;

typedef struct QNode
{
	QElemType data;
	QNode *next;
}*QueuePtr;

struct LinkQueue
{
	QueuePtr front, rear;
};


/**************************链队列基本操作*************************/
void InitQueue(LinkQueue &Q)
{
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));//头结点
	if (!Q.front)
		exit(EXIT_FAILURE);
	Q.front->next = NULL;
}

void DestroyQueue(LinkQueue &Q)
{
	while (Q.front)
	{
		Q.rear = Q.front->next;
		free(Q.front);
		Q.front = Q.rear;
	}
}

void ClearQueue(LinkQueue &Q)
{
	DestroyQueue(Q);
	InitQueue(Q);
}

Status QueueEmpty(LinkQueue Q)
{
	if (Q.front->next == NULL)
		return true;
	else
		return false;
}

int QueueLength(LinkQueue Q)
{
	int i = 0;
	QueuePtr p = Q.front;
	while (Q.rear != p)
	{
		i++;
		p = p->next;
	}
	return i;
}
/******************返回队头元素**********************/
Status GetHead(LinkQueue Q, QElemType &e)
{
	QueuePtr p;
	if (Q.front == Q.rear)
		return ERROR;
	p = Q.front->next;//队头元素
	e = p->data;
	return OK;
}
/*******************插入队尾元素***************************/
void EnQueue(LinkQueue &Q, QElemType e)
{
	QueuePtr p;
	p = (QueuePtr)malloc(sizeof(QNode));
	if (!p)
		exit(EXIT_FAILURE);
	p->data = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;//p变成尾结点
}
/********************删除队头元素，用e返回***************************/
Status DeQueue(LinkQueue &Q, QElemType &e)
{
	QueuePtr p;
	if (Q.front == Q.rear)
		return ERROR;
	p = Q.front->next;
	e = p->data;
	Q.front->next = p->next;//相当于第二个
	if (Q.rear == p)
		Q.rear = Q.front;
	free(p);
	return OK;
}

void QueueTraverse(LinkQueue Q, void(*visit)(QElemType))
{
	QueuePtr p = Q.front->next;//队头结点
	while (p)
	{
		visit(p->data);
		p = p->next;
	}
	printf("\n");
}


/******************二叉树队列******************/
//返回二叉树T中指向元素为s的结点的指针
BiTree Point(BiTree T, TElemType s)
{
	LinkQueue q;
	QElemType a;
	if (T)
	{
		InitQueue(q);
		EnQueue(q, T);//根入队
		while (!QueueEmpty(q))
		{
			DeQueue(q, a);//出队，队列元素赋给a
			if (a->data == s)
				return a;
			if (a->lchild)
				EnQueue(q, a->lchild);
			if (a->rchild)
				EnQueue(q, a->rchild);
		}
	}
	return NULL;
}
//
TElemType LeftChild(BiTree T, TElemType e)
{
	BiTree a;
	if (T)
	{
		a = Point(T, e);
		if (a&&a->lchild)
			return a->lchild->data;
	}
	return Nil;
}

TElemType RightChild(BiTree T, TElemType e)
{
	BiTree a;
	if (T)
	{
		a = Point(T, e);
		if (a&&a->rchild)
			return a->rchild->data;
	}
	return Nil;
}
//根据LR为0或1，删除T中p所指结点的左子树或右子树
Status DeleteChild(BiTree p, int LR)
{
	if (p)
	{
		if (LR == 0)
			ClearBiTree(p->lchild);
		else
			ClearBiTree(p->rchild);
		return OK;
	}
	return ERROR;
}

void PostOrderTraverse(BiTree T, void(Visit)(TElemType))
{
	if (T)
	{
		PostOrderTraverse(T->lchild, Visit);
		PostOrderTraverse(T->rchild, Visit);
		Visit(T->data);
	}
}
//层序遍历
void LevelOrderTraverse(BiTree T, void(*Visit)(TElemType))
{
	LinkQueue q;
	QElemType a;
	if (T)
	{
		InitQueue(q);
		EnQueue(q, T);
		while (!QueueEmpty(q))
		{
			DeQueue(q, a);
			Visit(a->data);
			if (a->lchild != NULL)
				EnQueue(q, a->lchild);
			if (a->rchild != NULL)
				EnQueue(q, a->rchild);
		}
		printf("\n");
	}
}

void CreateBiTree(BiTree &T)
{
	TElemType ch;
	scanf("%c", &ch);//输入结点的值
	if (ch == Nil)
		T = NULL;
	else
	{
		T = (BiTree)malloc(sizeof(BiTNode));//生成根结点
		if (!T)
			exit(EXIT_FAILURE);
		T->data = ch;
		CreateBiTree(T->lchild);
		CreateBiTree(T->rchild);
	}
}
//当e为非根结点时，返回双亲，否则返回空
TElemType Parent(BiTree T, TElemType e)
{
	LinkQueue q;
	QElemType a;
	if (T)
	{
		InitQueue(q);
		EnQueue(q, T);
		while (!QueueEmpty(q))
		{
			DeQueue(q, a);
			if (a->lchild&&a->lchild->data == e || a->rchild&&a->rchild->data == e)
				return a->data;
			else
			{
				if (a->lchild)
					EnQueue(q, a->lchild);
				if (a->rchild)
					EnQueue(q, a->rchild);
			}
		}
	}
	return Nil;
}

TElemType LeftSibling(BiTree T, TElemType e)
{
	TElemType a;
	BiTree p;
	if (T)
	{
		a = Parent(T, e);
		if (a != Nil)
		{
			p = Point(T, e);
			if (p->lchild&&p->rchild&&p->rchild->data == e)
				return p->lchild->data;
		}
	}
	return Nil;
}
TElemType RightSibling(BiTree T, TElemType e)
{
	TElemType a;
	BiTree p;
	if (T)
	{
		a = Parent(T, e);
		if (a != Nil)
		{
			p = Point(T, e);
			if (p->lchild&&p->rchild&&p->lchild->data == e)
				return p->rchild->data;
		}
	}
	return Nil;
}

Status InsertChild(BiTree p, int LR, BiTree c)
{
	if (p)
	{
		if (LR == 0)//把二叉树c插为p所指结点的左子树
		{
			c->rchild = p->lchild;//p所指结点的原有左子树成为c的右子树
			p->lchild = c;//二叉树成为p的左子树
		}
		else
		{
			c->rchild = p->rchild;//p所指结点的原有右子树为c的右子树
			p->rchild = c;//二叉树为p的右子树
		}
		return OK;
	}
	return ERROR;
}

/*******************顺序栈*********************/
typedef BiTree SElemType;

#define STACK_INIT_SIZE 10//初始分配量
#define STACK_INCREMENT 2//分配增量

struct SqStack
{
	SElemType *base;
	SElemType *top;
	int stacksize;//已分配的存储空间，以元素为单位
};

void InitStack(SqStack &S)
{
	S.base = (SElemType*)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if (!S.base)
		exit(EXIT_FAILURE);
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
}

void DestroyStack(SqStack &S)
{
	free(S.base);
	S.top = S.base = NULL;
	S.stacksize = 0;
}

Status ClearStack(SqStack S)
{
	if (S.top == S.base)
		return true;
	else
		return false;
}

Status StackEmpty(SqStack S)
{
	if (S.top == S.base)
		return true;
	else
		return false;
}

int StackLength(SqStack S)
{
	return S.top - S.base;
}
/****************************返回栈顶元素***********************/
Status GetTop(SqStack S, SElemType &e)
{
	if (S.top > S.base)
	{
		e = *(S.top - 1);
		return OK;
	}
	else
		return ERROR;
}

void Push(SqStack &S, SElemType e)
{
	if (S.top - S.base == S.stacksize)
	{
		S.base = (SElemType *)realloc(S.base, (S.stacksize + STACK_INCREMENT) * sizeof(SElemType));
		if (!S.base)
			exit(EXIT_FAILURE);
		S.top = S.base + S.stacksize;
		S.stacksize += STACK_INCREMENT;
	}
	*(S.top)++ = e;
}

Status Pop(SqStack &S, SElemType &e)
{
	if (S.top == S.base)
		return ERROR;
	e = *--S.top;
	return OK;
}

void StackTraverse(SqStack S, void(*visit)(SElemType))
{
	while (S.top>S.base)
	{
		visit(*S.base++);
	}
	printf("\n");
}


void InOrderTraverse1(BiTree T, void(*Visit)(TElemType))
{
	SqStack S;
	InitStack(S);
	while (T||!StackEmpty(S))
	{
		if(T)
		{ 
			Push(S, T);
			T = T->lchild;
		}
		else
		{
			Pop(S, T);
			Visit(T->data);
			T = T->rchild;
		}
	}
	printf("\n");
}

void InOrderTraverse2(BiTree T, void(*Visit)(TElemType))
{
	SqStack S;
	BiTree p;
	InitStack(S);
	Push(S, T);

	while (!StackEmpty(S))
	{
		while (GetTop(S,p)&&p)
			Push(S, p->lchild);
		Pop(S, p);
		if (!StackEmpty(S))
		{
			Pop(S, p);
			Visit(p->data);
			Push(S, p->rchild);
		}
	}
	printf("\n");
}