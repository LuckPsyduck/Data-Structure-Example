#pragma once
#include<iostream>
#include<iomanip>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<iterator>

using std::ofstream;
using std::ifstream;
using std::ostream;


//定义学生记录类型
//定义二叉搜索树结点值的类型为学生记录类型

typedef struct student
{
	char num[6];//学号
	int grade; //成绩
}ElemType;//可以定义数据结构

template<class T>
class BSTree 
{
private:
	BSTree<T> *left;	//左子树指针
	BSTree<T> *right;	//右子树指针
public:
	T data;//数据域
		
	BSTree() :left(NULL), right(NULL) { }   //构造函数

	BSTree(T item, BSTree<T> *left1 = NULL, BSTree<T> *right1 = NULL)   //构造函数
		:data(item), left(left1), right(right1) { }
		
	BSTree<T> *&Left() { return left; }//对指针类型的引用
	BSTree<T> *&Right() { return right; }

	//初始化二叉搜索树，即把树根指针置空
	void InitBSTree(BSTree<T> *&BST);

	//判断二叉搜索树是否为空
	bool BSTreeEmpty(BSTree<T> *&BST);

	//从二叉搜索树中查找元素
	bool Find(BSTree<T> *&BST, T item);

	//更新二叉搜索树中的结点值
	bool Update(BSTree<T> *&BST, const T item, T newc);

	//向二叉搜索树中插入元素
	void Insert(BSTree<T> *&BST, const T &item);

	//从二叉搜索树中删除元素
	bool Delete(BSTree<T> *&BST, T item);

	//利用数组建立一棵二叉搜索树
	void CreateBSTree(BSTree<T> *&BST, T a[], int n);

	//中序遍历输出二叉搜索树中的所有结点
	void Inorder(BSTree<T> *&BST);

	//求二叉搜索树的深度
	int BSTreeDepth(BSTree<T> *&BST);

	//求二叉搜索树中所有结点数
	int BSTreeCount(BSTree<T> *&BST);

	//求二叉搜索树中所有叶子结点数
	int BSTreeLeafCount(BSTree<T> *&BST);

	//按照二叉搜索树的广义表表示输出二叉搜索树
	void PrintBSTree(BSTree<T> *&BT);

	//清除二叉搜索树，使之变为一棵空树
	void ClearBSTree(BSTree<T> *&BT);

	//把BST二叉搜索树按照先根遍历的次序存储到文件fn中
	void WriteFile(char* fn, BSTree *BST);

	//把fn文件中按先根遍历存储的二叉搜索树恢复到内存中
	void ReadFile(char* fn, BSTree* &BST);

	void PreorderWrite(ofstream& ofs, BSTree* BST);

	void PreorderRead(ifstream& ifs, BSTree* BST, int& b);

	friend ostream & operator<<(ostream& ostr, const ElemType& x)
	{
		ostr << x.num << ':' << x.grade; 
		return ostr;
	}
};


