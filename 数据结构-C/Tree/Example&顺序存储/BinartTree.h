/*******************************二叉树的顺序表示**********************/
#include<stdio.h>                  
#include<malloc.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#define ERROR -1
#define OK 1


#define CHAR 0
/***************************结点类型选择*************************************/
#if CHAR
typedef  char TElemType;
TElemType Nil = ' ';
#else
typedef int TElemType;
TElemType Nil = 0;
#endif // CHAR

void visit(TElemType e)
{
	/*printf("%c", e);*/
	printf("%2d", e);
}
/****************************************************************/

//
typedef int Status;
#define MAX_TREE_SIZE 100
typedef TElemType SqBiTree[MAX_TREE_SIZE];


struct position
{
	int level;//层
	int order;//序号（按满二叉树计算）//所属层的位置序号（1开始）
};

/*******************/
#define ClearBiTree InitBiTree
#define DestroyBiTree InitBiTree

void InitBiTree(SqBiTree T)
{
	int i;
	for (i = 0; i < MAX_TREE_SIZE; i++)
		T[i] = Nil;
}

/**********************按层序次序输入二叉树结点的值****************/
void CreateBiTree(SqBiTree T)
{
	int i = 0;
	InitBiTree(T);
#if CHAR//值为非零，结点类型为字符
	int n;
	char s[MAX_TREE_SIZE];
	printf("请按层次输入结点的值(字符)，空格表示空结点，结点数<=%d:\n", MAX_TREE_SIZE);
	gets_s(s);
	n = strlen(s);
	for (; i < n; i++)
		T[i] = s[i];
#else
	printf("请按层次输入结点的值(整型)，0表示空结点，输入999结束，结点数<=%d:\n", MAX_TREE_SIZE);
	while (1)
	{
		scanf("%d", &T[i]);
		if (T[i] == 999)//输入结束
		{
			T[i] = Nil;
			break;
		}
		i++;
	}
#endif // CHAR
	for(i=1;i<MAX_TREE_SIZE;i++)
		if (T[i] !=Nil&&T[(i + 1) / 2 - 1] == Nil)//结点不空但无双亲(结点有问题)
		{
			printf("出现无双亲的非根结点%c\n",T[i]);
			printf("出现无双亲的非根结点%d\n", T[i]);
			exit(EXIT_FAILURE);
		}
}

Status BiTreeEmpty(SqBiTree T)
{
	if (T[0] == Nil)//根结点
		return true;
	else
		return false;
}

int BiTreeDepth(SqBiTree T)
{
	int i;
	if (T[0] == Nil)
		return 0;
	for (i = MAX_TREE_SIZE - 1; i >= 0; i--)
		if (T[i] != Nil)//找到最后一个结点，其序号为空
			break;
	return (int)(log(i + 1) / log(2) + 1.1);
}
/*************************用e返回根结点*******************/
Status Root(SqBiTree T, TElemType &e)
{
	if (BiTreeEmpty(T))
		return ERROR;
	else
	{
		e = T[0];
		return OK;
	}
}
/**********************返回处于位置e（层，本层的序号）的结点的值****************/
TElemType Value(SqBiTree T, position e)
{
	return T[int(pow(2, e.level - 1) + e.order - 2)];
}

/************给处于位置e（层，本层的序号）的结点赋新值value***********/
Status Assign(SqBiTree T, position e, TElemType value)
{
	int i = int(pow(2, e.level - 1) + e.order - 2);
	if (i != 0 && value != Nil&&T[(i + 1) / 2 - 1] == Nil)
		return ERROR;
	else if (value == Nil && (T[i * 2 + 1] != Nil || T[i * 2 + 2] != Nil))
		return ERROR;
	T[i] = value;
	return OK;
}
/*************诺e是T的非根结点，则返回它的双亲，否则返回空*********/
TElemType Parent(SqBiTree T, TElemType e)
{
	int i;
	if (T[0] ==Nil)
		return Nil;
	for (i = 1; i <= MAX_TREE_SIZE - 1; i++)
		if (T[i] == e)
			return T[(i + 1) / 2 - 1];//返回双亲结点的值
	return Nil;
}
/********************返回e的左孩子，诺e无左孩子，则返回空****************/
TElemType LeftChild(SqBiTree T, TElemType e)
{
	int i;
	for (i = 0; i <= (MAX_TREE_SIZE - 2) / 2; i++)
		if (T[i] == e)
			return T[i * 2 + 1];//返回e的左孩子的值
	return Nil;
}


TElemType RightChild(SqBiTree T, TElemType e)
{
	int i;
	for (i = 0; i <= (MAX_TREE_SIZE - 3) / 2; i++)//从T的第一个结点到最后一个可能有右孩子的结点
		if (T[i] == e)
			return T[i * 2 + 2];
	return Nil;
}

TElemType LeftSibling(SqBiTree T, TElemType e)
{
	int i;
	if (T[0] == Nil)
		return Nil;
	for (i = 1; i <= MAX_TREE_SIZE - 1; i++)
		if (T[i] == e&&i % 2 == 0)//找到e且其序号是偶数（右孩子）
			return T[i - 1];//返回e的左兄弟的值
	return Nil;
}

TElemType RightSibling(SqBiTree T, TElemType e)
{
	int i;
	if (T[0] == Nil)
		return Nil;
	for (i = 1; i <= MAX_TREE_SIZE - 2; i++)
		if (T[i] == e&&i % 2)//找到e且其序号为奇数（左孩子）
			return T[i + 1];//返回右兄弟的值
	return Nil;
}

/*************把从q的j结点开始的子树移为从T的i结点开始的子树*****************/
void Move(SqBiTree q, int j, SqBiTree T, int i)
{
	if (i >= MAX_TREE_SIZE)
		exit(EXIT_FAILURE);
	if (q[2 * j + 1] != NULL)//q的左子树不空
		Move(q, (2 * j + 1), T, (2 * i + 1));//把q的j结点的左子树移为T的i结点的左子树
	if (q[2 * j + 2] != NULL)//q的右子树不空
		Move(q, (2 * j + 2), T, (2 * i + 2));//把q的j结点的右子树移为T的i结点的右子树
	T[i] = q[j];//结点
	q[j] = Nil;
}

/*根据LR为0或1，插入c为T中p结点的左或右子树，P结点的原有左子树或右子树则为c的右子树*/
void InsertChild(SqBiTree T, TElemType p, int LR, SqBiTree c)
{
	int j, k;
	for (j = 0; j<int(pow(2, BiTreeDepth(T))) - 1; j++)//查找p的序号
		if (T[j] == p)//j为p的序号
			break;
	k = 2 * j + 1 + LR;//k为p的左孩子或右孩子的序号
	if (T[k] != Nil)//p原来的左孩子或右孩子不空
		Move(T, k, c, 2);//把从T的k结点开始的子树移为c的右子树
	Move(c, 0, T, k);//把树c移为从T的k结点开始的子树
}



/*********************队列**************************/


typedef int QElemType;

typedef struct QNode
{
	QElemType data;
	QNode *next;
}*QueuePtr;

struct LinkQueue
{
	QueuePtr front, rear;
};

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


/*****************二叉树的操作*****************************************************************************/

/*********************根据LR为0或1，删除T中p所指结点的左或右子树********************/
Status DeleteChild(SqBiTree T, position p, int LR)
{
	int i;//先删除树的结点，再删除根
	Status k = OK;//队列不为空
	LinkQueue q;
	InitQueue(q);//初始化，用于存放待删除的结点

	i = (int)pow(2, p.level - 1) + p.order - 2;//将层，本层的序号转换为数组的序号
	if (T[i] == Nil)
		return ERROR;
	i = i * 2 + 1 + LR;//待删除子树的根结点在数组中的序号(子结点)
	while (k!=-1)//
	{
		if (T[2 * i + 1] != Nil)//左结点不为空
			EnQueue(q, 2 * i + 1);//入队
		if (T[2 * i + 2] != Nil)//右结点不为空 
			EnQueue(q, 2 * i + 2);
		T[i] = Nil;//删除此结点 
		k = DeQueue(q, i);//出队结点的序号，其值赋给1，成功（队列不空）返回ok,否则返回error
	}
	return OK;
}

void(*VisitFunc)(TElemType);//函数变量

/*****************递归先序遍历二叉树T中序号为e的子树，preordertraverse()调用*******************/
void PreTraverse(SqBiTree T, int e)
{
	VisitFunc(T[e]);//返回树T中序号为e的结点
	if (T[2 * e + 1] != Nil)
		PreTraverse(T, 2 * e + 1);
	if (T[2 * e + 2] != Nil)
		PreTraverse(T, 2 * e + 2);
}

/******************先序遍历T，对每个结点调用函数Visit一次且仅一次*******************/
void PreOrderTraverse(SqBiTree T, void(*Visit)(TElemType))
{
	VisitFunc = Visit;
	if (!BiTreeEmpty(T))//树不空
		PreTraverse(T, 0);//递归先序遍历树T中序号为0的树（树T自身）
	printf("\n");
}

/***********递归中序遍历二叉树T中序号为e的结点的左子树，inordertraverse()调用****************/
void InTraverse(SqBiTree T, int e)
{
	if (T[2 * e + 1] != Nil)
		InTraverse(T, 2 * e + 1);//左子树
	VisitFunc(T[e]);//访问树T中序号为e的结点
	if (T[2 * e + 2] != Nil)
		InTraverse(T, 2 * e + 2);//右子树
}

/***********************中序遍历T，对每个结点调用函数visit一次且仅一次************************/
void InOrderTraverse(SqBiTree T, void(*Visit)(TElemType))
{
	VisitFunc = Visit;
	if (!BiTreeEmpty(T))
		InTraverse(T, 0);
	printf("\n");
}

/*************************递后序遍历二叉树T中序号为e的子树，postordertraverse()调用************/
void PostTraverse(SqBiTree T, int e)
{
	if (T[2 * e + 1] != Nil)
		PostTraverse(T, 2 * e + 1);
	if (T[2 * e + 2] != Nil)
		PostTraverse(T, 2 * e + 2);
	VisitFunc(T[e]);
}

/******************后序遍历T，对每个结点调用函数Visit一次且仅一次*****************/
void PostOrderTraverse(SqBiTree T, void(*Visit)(TElemType))
{
	VisitFunc = Visit;
	if (!BiTreeEmpty(T))
		PostTraverse(T, 0);
	printf("\n");
}

/***************层次遍历二叉树T*************************/
void LevelOrderTraverse(SqBiTree T, void(*Visit)(TElemType))
{
	int i = MAX_TREE_SIZE - 1, j;
	while (T[i] == Nil)
		i--;//找到最后一个非空结点的序号
	for (j = 0; j <= i; j++)
		if (T[j] != Nil)
			Visit(T[j]);
	printf("\n");
}

/**************************************逐层，按本层序号输出二叉树************************/
void print(SqBiTree T)
{
	int j, k;
	position p;
	TElemType e;
	for (j = 1; j <= BiTreeDepth(T); j++)//j为当前层
	{
		printf("第%d层: ", j);
		p.level = j;
		for (k = 1; k <= pow(2, j - 1); k++)
		{
			p.order = k;//当前结点所在本层的顺序
			e = Value(T, p);//该结点的值赋给e
			if (e != Nil)
				//printf("%d: %c", k, e);//输出在本层的顺序及值//字符型结点
			printf("  %d  : %d  ", k, e);//输出在本层的顺序及值//字符型结点
		}
		printf("\n");
	}
}
