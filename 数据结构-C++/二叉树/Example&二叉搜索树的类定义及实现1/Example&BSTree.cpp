#include "stdafx.h"
#include "BSTree.h"

template class CBSTree<char>;//模板类实例化声明，必不可少

using namespace std;

//初始化二叉树,即把树根指针置空
template<class T>
void CBSTree<T>::InitBSTree(CBSTree<T> *&BST)
{
	BST = NULL;
}

//判断二叉树是否为空
template<class T>
bool CBSTree<T>::BSTreeEmpty(CBSTree<T> *&BST)
{
	return BST == NULL;
}

//从二叉搜索树中查找元素
template<class T>
bool CBSTree<T>::Find(CBSTree<T> *&BST, T item)
{
	if (BST == NULL)
		return false;
	else 
	{
		if (item == BST->data)
		{
			item = BST->data;
			return true;
		}
		else if (item<BST->data)//递归查找左子树
			return Find(BST->left, item);
		else                  //递归查找右子树
			return Find(BST->right, item);
	}
}

//更新二叉搜索树中的结点值
template<class T>
bool CBSTree<T>::Update(CBSTree<T> *&BST, const T item, T newc)//替换
{
	if (BST == NULL) 
		return false;
	else 
	{
		if (item == BST->data) 
		{
			BST->data = newc;
			return true;
		}
		else if (item<BST->data)
			return Update(BST->left, item, newc);
		else
			return Update(BST->right, item, newc);
	}
}

//向二叉搜索树中插入元素
template<class T>
void CBSTree<T>::Insert(CBSTree<T> *&BST, const T &item)
{
	if (BST == NULL)
	{
		CBSTree<T> *p = new CBSTree<T>;
		p->data = item;
		p->left = p->right = NULL;
		BST = p;
	}
	else if (item == BST->data) 
		return;
	else if (item<BST->data)
		Insert(BST->left, item);  //向左子树中插入元素
	else
		Insert(BST->right, item);//向右子树中插入元素
}

//从二叉搜索树中删除元素
// 从二叉搜索树中查找值为item的结点, 指针t指向待比较的结点指针,s指向t的双亲结点,从树根结点开始比较														
template<class T>
bool CBSTree<T>::Delete(CBSTree<T> *&BST, T item)
{													
	CBSTree<T> *t = BST, *s = NULL;
	while (t != NULL) //寻找待比较结点
	{
		if (item == t->data)
			break;
		else if (item<t->data)
		{
			s = t;//s指向带比较结点的双亲
			t = t->left;
		}
		else 
		{ 
			s = t;
			t = t->right;
		}
	}
	if (t == NULL) //若没有找到待删除的结点，则返回假
		return false;

	//分三种不同情况删除已查找到的t结点
	if (t->left == NULL && t->right == NULL)//对t结点(即待删除的结点)为叶子结点的情况进行处理
	{ 
		if (t == BST)
			BST = NULL;
		else if (t == s->left) 
			s->left = NULL;
		else 
			s->right = NULL;
		delete t;
	}
	else if (t->left == NULL || t->right == NULL)//对t结点为单分支结点的情况进行处理
	{ 
		if (t == BST) //删除树根结点
		{  
			if (t->left == NULL) 
				BST = t->right;
			else  
				BST = t->left;
		}
		else //删除非树根结点时,分四种情况进行处理
		{
			if (t == s->left && t->left != NULL)
				s->left = t->left;
			else if (t == s->left && t->right != NULL)
				s->left = t->right;
			else if (t == s->right && t->left != NULL)
				s->right = t->left;
			else if (t == s->right && t->right != NULL)
				s->right = t->right;
		}
		delete t;  //回收t结点,即t指针所指向的结点
	}
	else if (t->left != NULL && t->right != NULL)//对t结点为双分支结点的情况进行处理
	{												//p初始指向t结点,q初始指向p结点的左子树的根结点
		CBSTree<T> *p = t, *q = t->left;								
		while (q->right != NULL)//查找t结点的中序前驱结点，查找结束后q结点为t结点的中序前驱结点,p结点为q结点的双亲结点
		{ 
			p = q;
			q = q->right; 
		}
		t->data = q->data;//q结点的值赋给t结点
		if (p == t)       //删除右子树为空的q结点,使它的左子树链接到它所在的链接位置
			t->left = q->left;//可以画图研究
		else 
			p->right = q->left;
		delete q;//回收q结点
	}
	return true;//删除结束后返回真
}

//利用数组建立一棵二叉搜索树
template<class T>
void CBSTree<T>::CreateBSTree(CBSTree<T> *&BST, T a[], int n)
{
	BST = NULL;
	for (int i = 0; i<n; i++)
		Insert(BST, a[i]);
}

//中序遍历输出二叉搜索树中的所有结点
template<class T>
void CBSTree<T>::Inorder(CBSTree<T> *&BST)
{
	if (BST != NULL) 
	{
		Inorder(BST->left);
		cout << BST->data << ' ';
		Inorder(BST->right);
	}
}

//求二叉搜索树的深度
template<class T>
int CBSTree<T>::BSTreeDepth(CBSTree<T> *&BST)
{
	if (BST == NULL) //对于空树,返回0并结束递归
		return 0;
	else
	{  
		int dep1 = BSTreeDepth(BST->left);//计算左子树的深度
		int dep2 = BSTreeDepth(BST->right);//计算右子树的深度
		if (dep1>dep2) //返回树的深度
			return dep1 + 1;
		else 
			return dep2 + 1;
	}
}

//求二叉搜索树中所有结点数
template<class T>
int CBSTree<T>::BSTreeCount(CBSTree<T> *&BST)
{
	if (BST == NULL) 
		return 0;
	else
		return BSTreeCount(BST->left) + BSTreeCount(BST->right) + 1;
}

//求二叉搜索树中所有叶子结点数
template<class T>
int CBSTree<T>::BSTreeLeafCount(CBSTree<T> *&BST)
{
	if (BST == NULL) 
		return 0;
	else if (BST->left == NULL && BST->right == NULL)
		return 1;
	else 
		return BSTreeLeafCount(BST->left) + BSTreeLeafCount(BST->right);
}

//按照二叉树的广义表表示输出二叉搜索树
template<class T>
void CBSTree<T>::PrintBSTree(CBSTree<T> *&BST)
{
	if (BST == NULL) return;//树为空时返回
	else {//否则执行如下操作
		cout << BST->data;//输出根结点的值
		if (BST->left != NULL || BST->right != NULL)
		{
			if (BST->left != NULL)
				cout << '(';//输出左括号
			PrintBSTree(BST->left);//输出左子树
			if (BST->right != NULL)
				cout << ',';//若右子树不为空则输出逗号分隔符
			PrintBSTree(BST->right);//输出右子树
			if (BST->left != NULL&&BST->right != NULL)
				cout << ')';
		}//输出右括号
	}
}

//清除二叉搜索树,使之变为一棵空树
template<class T>
void CBSTree<T>::ClearBSTree(CBSTree<T> *&BST)
{
	if (BST != NULL)//当二叉树非空时进行如下操作
	{
		ClearBSTree(BST->left);   //删除左子树
		ClearBSTree(BST->right);  //删除右子树
		delete BST;               //删除根结点
		BST = NULL;				//置根指针为空
	}
}             

