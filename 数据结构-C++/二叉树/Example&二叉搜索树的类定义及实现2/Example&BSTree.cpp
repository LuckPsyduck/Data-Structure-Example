#include "stdafx.h"
#include "BSTree.h"
using std::setw;
using std::cout;
using std::cin;
template class BSTree<char>;

//二叉搜索树类的实现
template<class T>
void BSTree<T>::DeleteTree(TNode<T> *&root)
{
	if (root == NULL)
		return;
	if (root->left != NULL)
		DeleteTree(root->left);
	if (root->right != NULL)
		DeleteTree(root->right);
	free(root);
}

template<class T>
void BSTree<T>::FreeBST(TNode<T> *&root)
{
	DeleteTree(root);
}

template<class T>
int BSTree<T>::BSTSize()
{
	return(size);
}

template<class T>
int BSTree<T>::BSTEmpty(TNode<T> *&root)
{
	if (root == NULL)
		return(1);
	else
		return(0);
}

template<class T>
TNode<T> *BSTree<T>::GetRoot(TNode<T> *&root)
{
	return(root);
}

template<class T>
TNode<T> *BSTree<T>::BSTLocate(TNode<T> *&root, T item)
{
	TNode<T> *t;
	t = root;
	while (t != NULL)
	{
		if (item == t->data) 
			break;
		else
			if (item < t->data)
				t = t->left;
			else
				t = t->right;
	}
	return(t);
}

template<class T>
void BSTree<T>::BSTInsert(TNode<T> *&root, T item)
{
	TNode<T> *t, *p, *newN;
	newN = new TNode<T>;
	newN->data = item;
	if (root == NULL)//创建根结点
	{
		root = newN;
		size++;
		return;
	}
	t = root;
	p = NULL;
	while (t != NULL)
	{
		p = t;
		if (item < t->data)
			t = t->left;
		else
			t = t->right;
	}
	if (item < p->data)
		p->left = newN;
	else
		p->right = newN;
	size++;
}

template<class T>
void BSTree<T>::BSTDelete(TNode<T> *&root, T item)
{
	TNode<T> *t, *p, *r, *pr;
	t = root;
	p = NULL;
	while (t != NULL)//寻找item
	{
		if (item == t->data)
			break;
		else
		{
			p = t;//p为t的父亲结点
			if (item<t->data)
				t = t->left;
			else
				t = t->right;
		}
	}
	if (t == NULL)
		return;
	if (t->left == NULL)
	{
		if (p == NULL)//t为根结点
			root = t->right;
		else if (p->left == t)
			p->left = t->right;
		else
			p->right = t->right;
		free(t);
	}
	else
	{
		pr = t;
		r = t->left;
		while (r->right != NULL)
		{
			pr = r;//父结点
			r = r->right;
		}
		t->data = r->data;
		if (pr == t)             //这种情况，画图分析
			pr->left = r->left;
		else
			pr->right = r->left;
		free(r);
	}
	size--;
}

template<class T>
void BSTree<T>::Inorder(TNode<T> *&root)
{
	if (root != NULL) 
	{
		Inorder(root->left);
		cout << setw(2) << root->data;
		Inorder(root->right);
	}
}

template<class T>
int BSTree<T>::BSTreeDepth(TNode<T> *&root)
{
	if (root == NULL)               //对于空树,返回0并结束递归
		return 0;
	else                           
	{  
		int dep1 = BSTreeDepth(root->left);     //计算左子树的深度
	
		int dep2 = BSTreeDepth(root->right);	//计算右子树的深度
		
		if (dep1 > dep2) //返回树的深度
			return dep1 + 1;
		else 
			return dep2 + 1;
	}
}

template<class T>
int BSTree<T>::BSTreeCount(TNode<T> *&root)
{
	if (root == NULL) 
		return 0;
	else
		return BSTreeCount(root->left) + BSTreeCount(root->right) + 1;
}

template<class T>
int BSTree<T>::BSTreeLeafCount(TNode<T> *&root)
{
	if (root == NULL) 
		return 0;
	else
		if (root->left == NULL && root->right == NULL)
			return 1;
		else
			return BSTreeLeafCount(root->left) + BSTreeLeafCount(root->right);
}

template<class T>
void BSTree<T>::ClearBSTree(TNode<T> *&root)
{
	DeleteTree(root);
	root = NULL;
	size = 0;
}


