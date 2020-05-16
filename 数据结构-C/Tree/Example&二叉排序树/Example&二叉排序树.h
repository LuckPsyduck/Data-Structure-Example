/****************************动态表查找*****(二叉排序树)***********************/
/*通过中序和先序（中序和后序）遍历二叉排序树，就可以确定二叉排序树的形态*/
#include<stdio.h>
#include<stdlib.h>

#define ERROR -1
#define OK 1

typedef int Status;


/****************************数值比较的约定*******************************/
#define EQ(a,b)((a)==(b))
#define LT(a,b)((a)<(b))
#define LQ(a,b)((a)<=(b))
/*************************************************************************/

/*******************树的基本操作**************************/
typedef int KeyType;

struct ElemType
{
	KeyType key;
	int others;
};

typedef struct BiTNode
{
	ElemType data;
	BiTNode *lchild, *rchild;
}BiTNode,* BiTree;

/***********二叉树操作与二叉排序树相同的操作定义***********/
#define InitDSTable InitBiTree
#define DestroyDSTable DestroyBiTree
#define TraverseDSTable InOrderTraverse//两者一样

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
//按关键字顺序遍历二叉排序树或平衡二叉树与中序遍历二叉树的操作相同
void InOrderTraverse(BiTree T, void(*Visit)(ElemType))
{
	if (T)
	{
		InOrderTraverse(T->lchild, Visit);
		Visit(T->data);
		InOrderTraverse(T->rchild, Visit);
	}
}
//递归查找关键字为key的数据元素
BiTree SearchBST(BiTree T, KeyType key)
{
	if (!T || EQ(key, T->data.key))
		return T;
	else if LT(key, T->data.key)
		return SearchBST(T->lchild, key);
	else
		return SearchBST(T->rchild, key);
}

//确定树的形态
void PostOrderTraverse(BiTree T, void (*Visit)(ElemType e))
{
	if (T)
	{
		Visit(T->data);
		PostOrderTraverse(T->lchild, Visit);
		PostOrderTraverse(T->rchild, Visit);
	}
}


/********************二叉排序树的基本操作*************************/
/*
在根指针T所指二叉排序树中递归遍历的查找其关键字等于key的数据元素，诺查找成功，则指针p指向该数据元素结点，并返回TRUE，否则指针\
p指向查找路径上访问的最后一个结点,并返回FALSE ，指针f指向T的双亲，其初始值为null。
*/
Status SearchBST(BiTree &T, KeyType key,BiTree f,BiTree &p)
{
	if (!T)
	{
		p = f;//p指向查找路径的最后一个结点
		return false;
	}
	else if EQ(key, T->data.key)
	{
		p = T;//p指向数据元素的结点
		return true;
	}
	else if LT(key, T->data.key)
		return SearchBST(T->lchild, key, T, p);
	else
		return SearchBST(T->rchild, key, T, p);
}
//诺二叉树中没有关键字等于Key的，则插入并返回TRUE，否则返回FALSE
Status InsertBST(BiTree &T, ElemType e)
{
	BiTree p, s;
	if (!SearchBST(T, e.key, NULL, p))//p指向查找路径上访问的最后一个叶子结点(p为叶子结点，很重要)
	{
		s = (BiTree)malloc(sizeof(BiTNode));
		s->data = e;
		s->lchild = s->rchild = NULL;
		if (!p)
			T = s;//待插入的结点为根节点
		else if LT(e.key, p->data.key)
			p->lchild = s;//待插入的结点为p所指结点的左孩子
		else
			p->rchild = s;
		return true;
	}
	else
		return false;
}
//从二叉排序树中删除P所指的结点，并重接它的左或右子树
void Delete(BiTree &p)
{
	BiTree s, q = p;//q指向待删除结点
	if (!p->rchild)
	{
		p = p->lchild;//直接继承
		free(p);
	}
	else if (!p->lchild)
	{
		p = p->rchild;//直接继承
		free(p);
	}
	else//左右子树都存在
	{
		s = p->lchild;//s指向待删除结点的左孩子
		while (s->rchild)//找到最右,即待删除结点的前驱(中序遍历的性质，对于二叉排序树，则由小到大)
		{
			q = s;//q指向其待删除结点前驱的双亲
			s = s->rchild;
		}
		p->data = s->data;//替换元素的值（直接用最接近的值替换（直接前驱或直接后继））
		if (q != p)//待删除结点的左右子树均不为空，且左孩子有右子树
			q->rchild = s->lchild;
		else//待删除结点的左右子树不为空，但左孩子没有右子树(q p重合)
			q->lchild = s->lchild;
		free(s);
	}
}
//诺二叉排序树T中存在关键字等于Key的数据元素时，则删除该数据元素的结点，并返回TRUE，否则返回FALSE
Status DeleteBST(BiTree &T, KeyType key)
{
	if (!T)
		return false;
	else
	{
		if EQ(key, T->data.key)
			Delete(T);//删除该结点(重点)
		else if LT(key, T->data.key)
			DeleteBST(T->lchild, key);
		else
			DeleteBST(T->rchild, key);
		return true;
	}
}

/************************数据元素类型基本操作*************************/
void Visit(ElemType c)
{
	printf("(%d,%d)", c.key, c.others);
}

void InputFromFile(FILE *f, ElemType &c)
{
	fscanf(f, "%d%d", &c.key, &c.others);
}

void InputKey(KeyType &k)
{
	scanf("%d", &k);
}