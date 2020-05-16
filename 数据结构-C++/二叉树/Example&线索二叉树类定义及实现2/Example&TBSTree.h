#pragma once
										//线索二叉树结点类型存储结构体
template<class T> class TBSTree;

template<class T> 
struct THNode
{
public:
	int lflag, rflag;	//标志域
	THNode<T> *left;	//第一个孩子结点指针域
	THNode<T> *right;	//下一个兄弟结点指针域
	T data;					//数据域
	friend class TBSTree<T>;	//线索二叉树类为友元
					
	THNode() :left(NULL), right(NULL), lflag(0), rflag(0) { }		//构造函数

	THNode(int la, int ra, T value, THNode<T> *fc = NULL, THNode<T> *ns = NULL)
		:data(value), left(fc), right(ns) {  lflag = la; rflag = ra;	}

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
public:
	//由结点构造线索二叉树
	THNode<T> *GetTreeNode(T item, THNode<T> *le = NULL, THNode<T> *ri = NULL, int lf = 0, int rf = 0);
						
	//创建特定线索二叉树
	THNode<T> *MakeCharT(THNode<T> *&, int);

	//构造二叉链表表示的二叉树(按先序次序输入结点值)
	void CreateBiTree(THNode<T> *&tr);

	//先序线索化二叉树
	void InThread1(THNode<T> *&);

	//中序线索化二叉树
	void InThread(THNode<T> *&);

	//后序线索化二叉树
	void InThread2(THNode<T> *&);

	//中序正向遍历线索二叉树
	void ThInorder(THNode<T> *&);
};

template<class T>
THNode<T> *TBSTree<T>::GetTreeNode(T item, THNode<T> *le, THNode<T> *ri, int lf, int rf)
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

template<class T>
THNode<T> *TBSTree<T>::MakeCharT(THNode<T> *&root, int num)
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

template<class T>
void TBSTree<T>::CreateBiTree(THNode<T> *&tr)//先序
{
	char ch;
	cin >> ch;
	if (ch == '#') 
		tr = NULL;
	else
	{
		tr = new THNode<T>;
		tr->lflag = tr->rflag = 0;
		if (!tr)
		{
			cerr << "内存分配失败!\n";
			exit(1);
		}
		tr->data = ch;
		CreateBiTree(tr->left);
		CreateBiTree(tr->right);
	}
}

template<class T>
void TBSTree<T>::InThread1(THNode<T> *&root)//先序遍历
{
	static THNode<T> *pre;
	if (root != NULL)
	{
		if (root->left == NULL)
			root->lflag = 1;//前继结点
		if (root->right == NULL)
			root->rflag = 1;

		if ((pre != NULL) && (root->lflag == 1))
			root->left = pre;
		if ((pre != NULL) && (pre->rflag == 1))
			pre->right = root;

		pre = root;//根
		if (root->lflag == 0)
			InThread(root->left);//左
		if (root->rflag == 0)
			InThread(root->right);//右
	}
}

template<class T>
void TBSTree<T>::InThread(THNode<T> *&root)//中序
{
	static THNode<T> *pre;
	if (root != NULL)
	{
		InThread(root->left);
		if (root->left == NULL)
			root->lflag = 1;
		if (root->right == NULL)
			root->rflag = 1;

		if ((pre != NULL) && (root->lflag == 1))
			root->left = pre;
		if ((pre != NULL) && (pre->rflag == 1))
			pre->right = root;

		pre = root;
		if (root->rflag == 0)
			InThread(root->right);
	}
}

template<class T>
void TBSTree<T>::InThread2(THNode<T> *&root)//后序   左右根
{
	static THNode<T> *pre;
	if (root != NULL)
	{
		InThread(root->left);
		InThread(root->right);
		if (root->left == NULL)
			root->lflag = 1;
		if (root->right == NULL)
			root->rflag = 1;

		if ((pre != NULL) && (root->lflag == 1))
			root->left = pre;
		if ((pre != NULL) && (pre->rflag == 1))
			pre->right = root;

		pre = root;
	}
}

template<class T>
void TBSTree<T>::ThInorder(THNode<T> *&root)
{
	THNode<T> *p;
	if (root == NULL) 
		return;
	p = root;
	while (p->lflag == 0)
		p = p->left;
	do
	{
		cout << p->data << "  ";
		if (p->rflag == 1)
			p = p->right;//这颗子树的最右结点
		else
		{
			p = p->right;
			while (p->lflag == 0)
				p = p->left;//回溯到左 就是左右根，回溯到上一层
		}
	} while (p != NULL);
}


