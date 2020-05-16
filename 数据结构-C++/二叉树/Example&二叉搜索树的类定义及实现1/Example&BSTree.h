#pragma once
#include<iostream>
#include<iomanip>
#include<stdlib.h>


template<class T>
class CBSTree
{
private:
	CBSTree<T> *left;//左子树指针
	CBSTree<T> *right;//右子树指针
public:
	T data;//数据域

						//构造函数
	CBSTree() :left(NULL), right(NULL) { }
	CBSTree(T item, CBSTree<T> *left1 = NULL, CBSTree<T> *right1 = NULL)
		:data(item), left(left1), right(right1) { }
		
	CBSTree<T> *&Left() { return left; }
	CBSTree<T> *&Right() { return right; }

	//初始化二叉搜索树，即把树根指针置空
	void InitBSTree(CBSTree<T> *&BST);

	//判断二叉搜索树是否为空
	bool BSTreeEmpty(CBSTree<T> *&BST);

	//从二叉搜索树中查找元素
	bool Find(CBSTree<T> *&BST, T item);

	//更新二叉搜索树中的结点值
	bool Update(CBSTree<T> *&BST, const T item, T newc);

	//向二叉搜索树中插入元素
	void Insert(CBSTree<T> *&BST, const T &item);

	//从二叉搜索树中删除元素
	bool Delete(CBSTree<T> *&BST, T item);

	//利用数组建立一棵二叉搜索树
	void CreateBSTree(CBSTree<T> *&BST, T a[], int n);

	//中序遍历输出二叉搜索树中的所有结点
	void Inorder(CBSTree<T> *&BST);

	//求二叉搜索树的深度
	int BSTreeDepth(CBSTree<T> *&BST);

	//求二叉搜索树中所有结点数
	int BSTreeCount(CBSTree<T> *&BST);

	//求二叉搜索树中所有叶子结点数
	int BSTreeLeafCount(CBSTree<T> *&BST);

	//按照二叉搜索树的广义表表示输出二叉搜索树
	void PrintBSTree(CBSTree<T> *&BT);

	//清除二叉搜索树，使之变为一棵空树
	void ClearBSTree(CBSTree<T> *&BT);
};

