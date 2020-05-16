#include "stdafx.h"
#include "BTree.h"

template class BTree<char>;//模板类必须要做的一件事

using namespace std;


// 根据字符数组a的二叉树广义表建立对应的二叉树存储结构
template<class T>
void BTree<T>::CreateBTree(char *a)
{
	BTree<T> *s[80];//s数组作为存储二叉树中根结点指针的栈
	int top = -1;      //top作为s栈的栈顶指针
	left = NULL;       //先将left作为树根指针给予置空
	BTree<T> *p = NULL;//定义p为指向二叉树结点的指针
					   //用k作为处理结点的左子树和右子树的标记,k=1处理左子树,k=2处理右子树
	int k;
	istrstream ins(a);//把字符串a定义为输入字符串流对象ins
	char ch;
	ins >> ch;//从ins流对象顺序读入一个字符，
	while (ch != '@')
	{//每循环一次处理一个读入的字符,直到扫描到'@'字符为止
		switch (ch)
		{
		case '(':top++; s[top] = p; k = 1; break;
		case ')':top--; break;
		case ',':top++; k = 2; break;
		default:p = new BTree<T>;
			p->data = ch; p->left = p->right = NULL;
			cout << setw(2) << p->data;
			if (left == NULL)
				left = p;
			else {
				if (k == 1) 
					s[top]->left = p;
				else 
					s[top]->right = p;
			}
		}
		ins >> ch;
	}
}
//按任一种遍历次序输出二叉树中的所有结点
template<class T>
void BTree<T>::TraverseBTree(int mark)
{
	Traverse(left, mark);
}

//用于遍历的递归函数
template<class T>
void BTree<T>::Traverse(BTree<T> *&BT, int mark)
{
	if (mark == 1) 
	{ //先序遍历
		if (BT != NULL)
		{
			cout << BT->data << ' ';
			Traverse(BT->left, mark);
			Traverse(BT->right, mark);
		}
	}
	else
		if (mark == 2)//中序遍历
		{
			if (BT != NULL)
			{
				Traverse(BT->left, mark);
				cout << BT->data << ' ';
				Traverse(BT->right, mark);
			}
		}
		else
			if (mark == 3) 
			{//后序遍历
				if (BT != NULL)
				{
					Traverse(BT->left, mark);
					Traverse(BT->right, mark);
					cout << BT->data << ' ';
				}
			}
			else
				if (mark == 4) //按层遍历
				{
					const int MaxLength = 80;
					BTree<T> *Q[MaxLength];
					//定义存储二叉树结点指针的数组空间作为队列使用
					int front = 0, rear = 0;
					//定义队首指针和队尾指针,初始均置0表示空队
					BTree<T> *p;
					if (BT != NULL)
					{
						rear = (rear + 1) % MaxLength;  //后移队尾指针
						Q[rear] = BT;
					}              //将树根结点指针进队
					while (front != rear)
					{//当队列非空时执行循环
						front = (front + 1) % MaxLength;
						//后移队首指针
						p = Q[front];
						//删除队首结点
						cout << p->data << ' ';
						//输出队首结点的值
						if (p->left != NULL)
						{//若结点存在左孩子，则左孩子结点指针进队
							rear = (rear + 1) % MaxLength;
							Q[rear] = p->left;
						}
						if (p->right != NULL)
						{//若结点存在右孩子,则右孩子结点指针进队
							rear = (rear + 1) % MaxLength;
							Q[rear] = p->right;
						}
					}
				}
				else
				{
					cerr << "mark的值无效!遍历失败!" << endl; 
					exit(1);
				}
}

//求二叉树的深度
template<class T>
int BTree<T>::BTreeDepth()
{
	return Depth(left);
}

//用于求二叉树深度的递归函数
template<class T>
int BTree<T>::Depth(BTree<T> *&BT)
{
	if (BT == NULL)
		return 0;//对于空树,返回0并结束递归
	else
	{//计算左子树的深度
		int dep1 = Depth(BT->left);
		//计算右子树的深度
		int dep2 = Depth(BT->right);
		//返回树的深度
		if (dep1>dep2)
			return dep1 + 1;
		else 
			return dep2 + 1;
	}
}

//求二叉树中所有结点数
template<class T>
int BTree<T>::BTreeCount()
{
	return Count(left);
}

//用于求二叉树中所有结点数的递归函数
template<class T>
int BTree<T>::Count(BTree<T> *&BT)
{
	if (BT == NULL) 
		return 0;
	else
		return Count(BT->left) + Count(BT->right) + 1;
}

//求二叉树中所有叶子结点数
template<class T>
int BTree<T>::BTreeLeafCount()
{
	return LeafCount(left);
}

//用于求二叉树中所有叶子结点数的递归函数
template<class T>
int BTree<T>::LeafCount(BTree<T> *&BT)
{
	if (BT == NULL)
		return 0;
	else if (BT->left == NULL && BT->right == NULL)
		return 1;
	else 
		return LeafCount(BT->left) + LeafCount(BT->right);
}

//按照二叉树的广义表表示输出整个二叉树
template<class T>
void BTree<T>::PrintBTree()
{
	Print(left);
}

//用于输出整个二叉树的递归函数
template<class T>
void BTree<T>::Print(BTree<T> *&BT)
{
	if (BT == NULL) 
		return;//树为空时返回
	else {//否则执行如下操作
		cout << BT->data;//输出根结点的值
		if (BT->left != NULL || BT->right != NULL)
		{
			if (BT->left != NULL)
				cout << '(';  //输出左括号
			Print(BT->left);//输出左子树
			if (BT->right != NULL)
				cout << ',';//若右子树不为空则输出逗号分隔符
			Print(BT->right);//输出右子树
			if (BT->left != NULL&&BT->right != NULL)
				cout << ')';
		} //输出右括号
	}
}

//析构函数,清除二叉树
template<class T>
BTree<T>::~BTree()
{
	Clear(left);
}
//用于清除二叉树的递归函数
template<class T>
void BTree<T>::Clear(BTree<T> *&BT)
{
	if (BT != NULL)
	{ //当二叉树非空时进行如下操作
		Clear(BT->left); //删除左子树
		Clear(BT->right);//删除右子树
		delete BT;       //删除根结点
		BT = NULL;
	}        //置根指针为空
}


