#include "stdafx.h"
#include "BSTree.h"
using namespace std;
template class BSTree<ElemType>;

//初始化二叉树,即把树根指针置空
template<class T>
void BSTree<T>::InitBSTree(BSTree<T> *&BST)
{
	BST = NULL;
}

//判断二叉树是否为空
template<class T>
bool BSTree<T>::BSTreeEmpty(BSTree<T> *&BST)
{
	return BST == NULL;
}

//从二叉搜索树中查找元素
template<class T>
bool BSTree<T>::Find(BSTree<T> *&BST, T item)
{
	if (BST == NULL) 
		return false;
	else 
	{
		if (item.grade == BST->data.grade)
		{
			item = BST->data;
			return true;
		}
		else if (item.grade<BST->data.grade)//递归查找左子树
			return Find(BST->left, item);
		else								//递归查找右子树
			return Find(BST->right, item);
	}
}

//更新二叉搜索树中的结点值
template<class T>
bool BSTree<T>::Update(BSTree<T> *&BST, const T item, T newc)
{
	if (BST == NULL)
		return false;
	else 
	{
		if (item.grade == BST->data.grade)
		{
			Insert(BST, newc);//将其插入合理的位置
			Delete(BST, item);//加原值给删除
			return true;
		}
		else if (item.grade<BST->data.grade)
			return Update(BST->left, item, newc);
		else
			return Update(BST->right, item, newc);
	}
}

//向二叉搜索树中插入元素
template<class T>
void BSTree<T>::Insert(BSTree<T> *&BST, const T &item)
{
	if (BST == NULL)
	{
		BSTree<T> *p = new BSTree;
		p->data = item;
		p->left = p->right = NULL;
		BST = p;
	}
	else if (item.grade<BST->data.grade)
		Insert(BST->left, item);  //向左子树中插入元素
	else
		Insert(BST->right, item);//向右子树中插入元素
}

//从二叉搜索树中删除元素
template<class T>
bool BSTree<T>::Delete(BSTree<T> *&BST, T item)
{														//从二叉搜索树中查找值为item的结点,指针t指向待比较的结点，
														//指针s指向t的双亲结点,从树根结点开始比较
	BSTree<T> *t = BST, *s = NULL;
	while (t != NULL) 
	{
		if (item.grade == t->data.grade) 
			break;
		else if (item.grade < t->data.grade) 
		{
			s = t; 
			t = t->left;
		}
		else 
		{
			s = t; 
			t = t->right;
		}
	}
	//若没有找到待删除的结点，则返回假
	if (t == NULL)
		return false;
	//分三种不同情况删除已查找到的t结点
	if (t->left == NULL && t->right == NULL)//对t结点(即待删除的结点)为叶子结点的情况进行处理
	{ 
		if (t == BST) 
			BST = NULL;
		else if (t == s->left) //s为t的父亲结点
			s->left = NULL;
		else  
			s->right = NULL;
		delete t;
	}
	else if (t->left == NULL || t->right == NULL)//对t结点为单分支结点的情况进行处理
	{ 
		if (t == BST)//删除树根结点
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
	else if (t->left != NULL && t->right != NULL)
		{											//对t结点为双分支结点的情况进行处理
													 //p初始指向t结点,q初始指向p结点的左子树的根结点
		BSTree<T> *p = t, *q = t->left;
		//查找t结点的中序前驱结点，查找结束后q结点为t结点
		//的中序前驱结点,p结点为q结点的双亲结点
		while (q->right != NULL)
		{
			p = q;
			q = q->right;
		}
		//q结点的值赋给t结点
		t->data = q->data;
		//删除右子树为空的q结点,使它的左子树链接到它所在的链接位置
		if (p == t) //可以画图分析
			t->left = q->left;
		else
			p->right = q->left;
		delete q;//回收q结点
	}
	return true;	//删除结束后返回真
}

//利用数组建立一棵二叉搜索树
template<class T>
void BSTree<T>::CreateBSTree(BSTree<T> *&BST, T a[], int n)
{
	BST = NULL;
	for (int i = 0; i<n; i++)
		Insert(BST, a[i]);
}

//中序遍历输出二叉搜索树中的所有结点
template<class T>
void BSTree<T>::Inorder(BSTree<T> *&BST)
{
	if (BST != NULL)
	{
		Inorder(BST->left);
		cout << BST->data.grade << ' ';
		Inorder(BST->right);
	}
}

//求二叉搜索树的深度
template<class T>
int BSTree<T>::BSTreeDepth(BSTree<T> *&BST)
{
	if (BST == NULL) 
		return 0;			//对于空树,返回0并结束递归
	else
	{  
		int dep1 = BSTreeDepth(BST->left);//计算左子树的深度
		int dep2 = BSTreeDepth(BST->right);//计算右子树的深度
		if (dep1>dep2)//返回树的深度
			return dep1 + 1;	
		else 
			return dep2 + 1;//加根结点
	}
}

//求二叉搜索树中所有结点数
template<class T>
int BSTree<T>::BSTreeCount(BSTree<T> *&BST)
{
	if (BST == NULL) 
		return 0;
	else
		return BSTreeCount(BST->left) + BSTreeCount(BST->right) + 1;
}

//求二叉搜索树中所有叶子结点数
template<class T>
int BSTree<T>::BSTreeLeafCount(BSTree<T> *&BST)
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
void BSTree<T>::PrintBSTree(BSTree<T> *&BST)
{
	if (BST == NULL)
		return;  //树为空时返回
	else 
	{//否则执行如下操作
		cout << BST->data.grade;  //输出根结点的值
		if (BST->left != NULL || BST->right != NULL)
		{
			if (BST->left != NULL)
				cout << '(';  //输出左括号
			PrintBSTree(BST->left);  //输出左子树
			if (BST->right != NULL)
				cout << ',';  //若右子树不为空则输出逗号分隔符
			PrintBSTree(BST->right);  //输出右子树
			if (BST->left != NULL&&BST->right != NULL)
				cout << ')';
		} //输出右括号
	}
}

//清除二叉搜索树,使之变为一棵空树
template<class T>
void BSTree<T>::ClearBSTree(BSTree<T> *&BST)
{
	if (BST != NULL)
	{//当二叉树非空时进行如下操作
		ClearBSTree(BST->left);  //删除左子树
		ClearBSTree(BST->right); //删除右子树
		delete BST;              //删除根结点
		BST = NULL;
	}               //置根指针为空
}

//把BST二叉搜索树按照先根遍历的次序存储到文件fn中
template<class T>
void BSTree<T>::WriteFile(char* fn, BSTree<T>* BST)
{													//把由fn所指字符串作为文件名的文件定义
													//为输出文件流ofs,并按二进制方式打开
	ofstream ofs(fn, ios::out | ios::binary);
	if (!ofs)
	{ 
		cout << "File not open!" << endl; 
		exit(1); 
	}
	
	PreorderWrite(ofs, BST);//调用PreorderWrite函数向文件输出二叉搜索树
	ofs.close();//关闭文件流对象所对应的文件
}

//向ofs文件流所对应的文件中按先根遍历次序写入
//一棵二叉搜索树BST的递归算法,它由WriteFile函数调用
template<class T>
void BSTree<T>::PreorderWrite(ofstream& ofs, BSTree<T>* BST)
{
	if (BST != NULL)
	{
		ofs.write((char*)BST, sizeof(*BST));
		PreorderWrite(ofs, BST->left);
		PreorderWrite(ofs, BST->right);
	}
}
//把fn文件中按先根遍历存储的二叉搜索树恢复到内存中
template<class T>
void BSTree<T>::ReadFile(char* fn, BSTree<T>*& BST)
{
	ifstream ifs(fn, ios::in | ios::binary);//把fn文件定义为输入文件流ifs，并按二进制方式打开
	if (!ifs) 
	{ 
		cout << "File not open!" << endl; 
		exit(1); 
	}
	ifs.seekg(0, ios::end);//把文件指针移到结束位置
	int b = sizeof(BSTree);//求出二叉搜索树中每个结点的大小
	int n = ifs.tellg() / b; //当前为最后的位置             //求出文件中所存二叉树的结点数并赋给n

	//如果文件为空，则把BST置空后返回
	if (n == 0) 
	{
		ifs.close(); 
		BST = NULL;
		return; 
	}
	//将文件指针移到文件开始位置,以便从头开始读取每个结点
	ifs.seekg(0);

	//用文件中的第一个结点构成树根结点
	BST = new BSTree<T>;
	ifs.read((char*)BST, b);//存入缓冲区，最大字节数，从文件读取
	cout << setw(4) << BST->data.grade;

	//分别从文件中读取左、右子树
	PreorderRead(ifs, BST->left, b);
	PreorderRead(ifs, BST->right, b);
	//关闭ifs对应的磁盘文件
	ifs.close();
}

//从ifs文件流所对应的文件中按先根遍历次序读出
//一棵二叉搜索树的递归算法,它由ReadFile函数调用
template<class T>
void BSTree<T>::PreorderRead(ifstream& ifs, BSTree<T>* BST, int& b)
{
	if (BST != NULL) 
	{
		BST = new BSTree<T>;
		ifs.read((char*)BST, b);
		cout << setw(4) << BST->data.grade;//根
		PreorderRead(ifs, BST->left, b);//左
		PreorderRead(ifs, BST->right, b);//右
	}
}


