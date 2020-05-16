#pragma once

//线索二叉树结点类型存储结构体
template<class T> class TBSTree;
template<class T> class ITBSTree;

template<class T> 
struct THNode
{
public:
	int lflag, rflag;	//标志域
	THNode<T> *left;	//第一个孩子结点指针域
	THNode<T> *right;	//下一个兄弟结点指针域
	T data;					//数据域
	friend class TBSTree<T>;					//线索二叉树类为友元
	friend class ITBSTree<T>;						//派生类
						
	THNode() :left(NULL), right(NULL), lflag(0), rflag(0) { }	 //构造函数

	THNode(int la, int ra, T value, THNode<T> *fc = NULL, THNode<T> *ns = NULL)
	:data(value), left(fc), right(ns){ lflag = la; rflag = ra; }

	//访问指针域的成员函数
	THNode<T>* &FirstChild()
	{
		return left;
	}
	THNode<T>* &NextSibling()
	{
		return right;
	}
};

//线索二叉树类
template<class T>
class TBSTree
{
protected:
	THNode<T> *root;	//根结点指针
	THNode<T> *curr;	//当前结点指针
	int nextC;
	int priorC;
public:
						//构造函数与析构函数
	TBSTree() { root = curr = NULL; }
	TBSTree(THNode<T> *&tree)
	{
		root = tree;
		curr = root;
		if (tree == NULL)
		{
			nextC = 1;
			priorC = 1;
		}
		else 
		{ 
			nextC = 0; 
			priorC = 0; 
		}
	}
	//纯虚函数
	virtual void First() = 0;
	virtual void Last() = 0;

	//数据检索与修改成员函数
	T &Data();
};

//线索二叉树类的实现
template<class T>
T &TBSTree<T>::Data()
{
	if (root == NULL)
	{
		cout << "二叉树空!\n"; 
		exit(1);
	}
	return curr->data;
}

//由结点构造线索二叉树的类外一般函数
template<class T>
THNode<T> *GetTreeNode(T item, THNode<T> *le = NULL,
	THNode<T> *ri = NULL, int lf = 0, int rf = 0)
{
	THNode<T> *p = new THNode<T>;
	p->data = item; 
	p->left = le;
	p->right = ri;
	p->lflag = lf; 
	p->rflag = rf;
	if (p == NULL)
	{
		cerr << "内存分配失败!\n";
		exit(1);
	}
	return p;
}

//创建特定线索二叉树的类外一般函数
template<class T>
THNode<T> *MakeCharT(THNode<T> *&root, int num)
{
	THNode<T> *b, *c, *d, *e, *f, *g, *null = NULL;
	if (num == 1)
	{
		e = GetTreeNode('R');
		f = GetTreeNode('W');
		d = GetTreeNode('P', e, f);
		g = GetTreeNode('Q');
		b = GetTreeNode('N', d, g);
		c = GetTreeNode('O');
		root = GetTreeNode('M', b, c);
	}
	else {
		g = GetTreeNode('G');
		d = GetTreeNode('D', null, g);
		b = GetTreeNode('B', d);
		e = GetTreeNode('E');
		f = GetTreeNode('F');
		c = GetTreeNode('C', e, f);
		root = GetTreeNode('A', b, c);
	}
	return root;
}

