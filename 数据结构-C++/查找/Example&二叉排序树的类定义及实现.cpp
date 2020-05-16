// 二叉排序树的类定义及实现.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include<stdlib.h>
using namespace std;

//二叉树的链式存储结构表示
typedef struct BinaryTree
{
	int data;
	struct BinaryTree *l;
	struct BinaryTree *r;
}*BiTree, BiNode;

//二叉树的类定义
class BiSearchT
{
private:
	BiTree root;
public:
	//构造函数
	BiSearchT() :root(NULL) {}

	//构造二叉链表表示的二叉树T
	int CreateSubTree(BiTree &t, int *all, int i);

	//先序遍历二叉树T
	int PreOrderTraverse(BiTree t, int(*Visit)(int e));

	//中序遍历二叉树T
	int InOrderTraverse(BiTree t, int(*Visit)(int e));

	//插入算法
	int InsertBST(BiTree *t, int e);

	//在二叉排序树中删除一个节点
	void Delete(BiTree *p);

	//二叉排序树的删除
	bool DeleteBST(BiTree *t, int key);

	//二叉排序树上的查找递归算法
	bool SearchBST(BiTree t, int key, BiTree f, BiTree *p);
};

//二叉排序树的类实现
//构造二叉链表表示的二叉树T
int BiSearchT::CreateSubTree(BiTree &t, int *all, int i)
{
	if ((all[i] == 0) || i>16)
	{
		t = NULL;
		return 1;
	}
	t = (BiNode *)malloc(sizeof(BiNode));
	if (t == NULL) 
		return 0;
	t->data = all[i];
	CreateSubTree(t->l, all, 2 * i);//左子树
	CreateSubTree(t->r, all, 2 * i + 1);//右子树
}

//先序遍历二叉树T
int BiSearchT::PreOrderTraverse(BiTree t, int(*Visit)(int d))
{
	if (t) 
	{
		if (Visit(t->data))//根左右
			if (PreOrderTraverse(t->l, Visit))
				if (PreOrderTraverse(t->r, Visit)) 
					return 1;
		return 0;
	}
	else 
		return 1;
}

//中序遍历二叉树T
int BiSearchT::InOrderTraverse(BiTree t, int(*Visit)(int d))
{
	if (t) 
	{
		if (InOrderTraverse(t->l, Visit))//左根右
			if (Visit(t->data))
				if (InOrderTraverse(t->r, Visit))
					return 1;
		return 0;
	}
	else 
		return 1;
}

//二叉排序树上的查找递归算法
bool BiSearchT::SearchBST(BiTree t, int key, BiTree f, BiTree *p)
{
	if (!t) 
	{
		*p = f; 
		return false; 
	}//递归的终结条件
	else if (key == t->data)
	{ 
		*p = t;
		return true; 
	}
	else if (key<t->data)
		SearchBST(t->l, key, t, p);//左子树查找
	else 
		SearchBST(t->r, key, t, p);//继续在右子树中查找
}

//插入算法
int BiSearchT::InsertBST(BiTree *t, int e) 
{
	BiTree p;
	BiTree s;
	if (!SearchBST(*t, e, NULL, &p))
	{
		s = (BiTree)malloc(sizeof(BiNode));
		s->data = e;
		s->l = s->r = NULL;
		if (!p)
			*t = s;
		else if (e < p->data)
			p->l = s;
		else
			p->r = s;
		return true;
	}
	else 
		return false;
}

//在二叉排序树中删除一个节点
void BiSearchT::Delete(BiTree *p) 
{
	BiTree q, s;
	if (!(*p)->r)//右子树不存在
	{
		q = (*p);
		(*p) = (*p)->l;
		free(q);
	}
	else if (!(*p)->l)//左子树不存在
	{
		q = (*p);
		(*p) = (*p)->r;
		free(q);
	}
	else//左右子树均存在
	{
		q = s = (*p)->l;
		while (s->r) 
			s = s->r;//找前驱
		s->r = (*p)->r;//将其后继挂到其前驱
		free(*p);
		(*p) = q;
	}
}

//二叉排序树的删除
bool BiSearchT::DeleteBST(BiTree *t, int key)
{
	if (*t != NULL)
	{
		if (key == (*t)->data)
			Delete(t);
		else
			if (key<(*t)->data)
				DeleteBST(&((*t)->l), key);
			else 
				DeleteBST(&((*t)->r), key);
			return true;
	}
	else 
		return false;
}

//输出二叉排序树的数据域值
int printelem(int d)
{
	cout << setw(4) << d;
	return 1;
}
//二叉排序树类的测试
void main()
{
	cout << "BinSortT.cpp运行结果:\n";
	BiTree root;
	BiTree sroot = NULL;
	BiTree croot = NULL;
	int all[16] = { 0,1,2,3,0,0,4,5,0,0,0,0,6,0,0,0 };
	int i, a[10] = { 45,23,12,3,33,27,56,90,120,62 };
	int n = 7, b[] = { 10,7,6,9,20,12,22 };
	BiSearchT my;
	my.CreateSubTree(root, all, 1);
	cout << "先序遍历(root,all):\n";
	my.PreOrderTraverse(root, printelem);
	cout << "\n中序遍历(root,all):\n";
	my.InOrderTraverse(root, printelem);

	for (i = 0; i<10; i++)
		my.InsertBST(&sroot, a[i]);
	cout << "\n中序遍历(sroot,a):\n";
	my.InOrderTraverse(sroot, printelem);
	for (i = 0; i<3; i++)
		my.DeleteBST(&sroot, a[i]);
	cout << "\nNow sroot has nodes:\n";
	my.InOrderTraverse(sroot, printelem);

	for (i = 0; i<n; i++)
		my.InsertBST(&croot, b[i]);
	cout << "\n中序遍历(croot,b):\n";
	my.InOrderTraverse(croot, printelem);
	my.InsertBST(&croot, 8);
	cout << "\n中序遍历(croot,b):\n";
	my.InOrderTraverse(croot, printelem);
	my.DeleteBST(&croot, 7);
	cout << "\n中序遍历(croot,b):\n";
	my.InOrderTraverse(croot, printelem);
}

