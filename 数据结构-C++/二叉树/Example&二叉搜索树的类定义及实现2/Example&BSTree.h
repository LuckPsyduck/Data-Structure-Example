#pragma once
#include<iostream>
#include<iomanip>
#include<stdlib.h>
#include<conio.h>

template<class T> class BSTree;

template<class T> 
struct TNode
{
private:
	TNode<T>  *left;    //左子树指针
	TNode<T>  *right;   //右子树指针
public:
	friend class BSTree<T>;
	T data;//数据域
		 
	TNode() :left(NULL), right(NULL) { }  //构造函数
	TNode(T item, TNode<T> *left1, TNode<T> *right1)
		:data(item), left(left1), right(right1) { }
};

template<class T> 
class BSTree
{
private:
	int size;
public:

	//构造函数,把树根指针置空
	BSTree(TNode<T> *&root) { root = NULL; size = 0; }

	//被ClearBST()所调用的函数
	void DeleteTree(TNode<T> *&root);

	//释放空间
	void FreeBST(TNode<T> *&root);

	//求二叉搜索树中所有结点数
	int BSTSize();

	//判断二叉搜索树是否为空
	int BSTEmpty(TNode<T> *&root);

	//取根指针
	TNode<T> *GetRoot(TNode<T> *&root);

	//从二叉搜索树中查找元素
	TNode<T> *BSTLocate(TNode<T> *&root, T item);

	//向二叉搜索树中插入元素
	void BSTInsert(TNode<T> *&root, T item);

	//从二叉搜索树中删除元素
	void BSTDelete(TNode<T> *&root, T item);

	//中序遍历输出二叉搜索树中的所有结点
	void Inorder(TNode<T> *&root);

	//求二叉搜索树的深度
	int BSTreeDepth(TNode<T> *&root);

	//求二叉搜索树中所有结点数
	int BSTreeCount(TNode<T> *&root);

	//求二叉搜索树中所有叶子结点数
	int BSTreeLeafCount(TNode<T> *&root);

	//清除二叉搜索树，使之变为一棵空树
	void ClearBSTree(TNode<T> *&root);
};
