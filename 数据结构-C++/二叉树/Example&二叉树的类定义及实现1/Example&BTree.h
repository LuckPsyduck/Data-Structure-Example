#pragma once
#include<iostream>
#include<iomanip>
#include<stdlib.h>
#include<strstream>

template<class T>
class CBTree
{
public:
	CBTree() { left = right = NULL; }
	~CBTree();
private:
	CBTree<T> *left;//左子树指针
	CBTree<T> *right;//右子树指针
public:
	T data;//数据域

	CBTree(T item, CBTree<T> *left1 = NULL, CBTree<T> *right1 = NULL)
		:data(item), left(left1), right(right1) { }

	CBTree<T> *&Left() { return left; }
	CBTree<T> *&Right() { return right; }

	//根据字符数组a的二叉树广义表建立对应的二叉树存储结构
	void CreateBTree(char* a);

	//判断二叉树是否为空
	bool BTreeEmpty() { return left == NULL; }

	//按任一种遍历次序输出二叉树中的所有结点
	void TraverseBTree(int mark);

	//用于遍历的递归函数
	void Traverse(CBTree<T> *&BT, int mark);

	//求二叉树的深度
	int BTreeDepth();

	//用于求二叉树深度的递归函数
	int Depth(CBTree<T> *&BT);

	//求二叉树中所有结点数
	int BTreeCount();

	//用于求二叉树中所有结点数的递归函数
	int Count(CBTree<T> *&BT);

	//求二叉树中所有叶子结点数
	int BTreeLeafCount();

	//用于求二叉树中所有叶子结点数的递归函数
	int LeafCount(CBTree<T> *&BT);

	//按照二叉树的一种表示方法输出整个二叉树
	void PrintBTree();

	//用于输出整个二叉树的递归函数
	void Print(CBTree<T> *&BT);

	//用于清除二叉树的递归函数
	void Clear(CBTree<T> *&BT);
};

