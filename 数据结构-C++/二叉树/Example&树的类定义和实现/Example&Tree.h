#pragma once
#include<iostream>
#include<iomanip>
#include<stdlib.h>
#include<conio.h>


//树的孩子兄弟表示法为存储结构的结构体Tree.h

template<class T> class CTree;

template<class T> struct TreeNode
{
	friend class CTree<T>;//树类为友元
private:
	TreeNode<T> *firstChild;//第一个孩子结点指针域
	TreeNode<T> *nextSibling;//下一个兄弟结点指针域

public:
	T data;//数据域

		   //构造函数
	TreeNode(T value, TreeNode<T> *fc = NULL, TreeNode<T> *ns = NULL)
		:data(value), firstChild(fc), nextSibling(ns) {}

	//访问指针域的成员函数
	TreeNode<T>* &FirstChild()
	{
		return firstChild;
	}

	TreeNode<T>* &NextSibling()
	{
		return nextSibling;
	}
};

template<class T>
class CTree
{
private:
	TreeNode<T> *root;//根结点指针
	TreeNode<T> *curr;//当前结点指针

					  //显示以t为先根结点的树的数据域
	void PreOrderTree(TreeNode<T> *&t);

	//显示以t为后根结点的树的数据域
	void PosOrderTree(TreeNode<T> *&t);

	//使当前结点为t所指结点
	int Current(TreeNode<T> *&t);

	//在树root中回溯查找结点s的双亲结点
	TreeNode<T> *SearchParent(TreeNode<T> *&root, TreeNode<T> *&s);
public:
	//构造函数与析构函数
	CTree() { root = curr = NULL; }
	~CTree() { DeleteSubTree(root); }

	//使根结点为当前结点
	int Root();

	//使当前结点的双亲结点为当前结点
	int Parent();

	//使当前结点的第一个孩子结点为当前结点
	int FirstChild();

	//使当前结点的兄弟结点为当前结点
	int NextSibling();

	//把valve插入到当前结点的最后一个结点
	void InsertChild(T value);

	//删除以t为根结点的子树
	void DeleteSubTree(TreeNode<T> *&t);

	//删除当前结点的第i个孩子结点
	int DeleteChild(int i);

	//删除以root为根结点的子树的第i个孩子结点
	int DeleteChild1(int i);

	//按先根遍历次序显示树的数据域值
	void DisplayTree();

	//按后根遍历次序显示树的数据域值
	void DisplayTree1();
};

