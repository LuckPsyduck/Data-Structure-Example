// 二叉搜索树的类定义及实现2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"BSTree.h"
using namespace std;

TNode<char> *q;

void main()
{
	int i;
	char test[50] = "abxycdMNefgzkl";
	BSTree<char> t(q);

	for (i = 0; test[i] != '\0'; i++)
		t.BSTInsert(q, test[i]);

	cout << "中序遍历二叉搜索树:\n";
	t.Inorder(q);

	cout << "\n二叉搜索树的结点数=" << t.BSTSize() << endl;
	cout << "二叉搜索树的结点数=" << t.BSTreeCount(q) << endl;
	cout << "二叉搜索树的深度=" << t.BSTreeDepth(q) << endl;
	cout << "二叉搜索树的叶子结点数=" << t.BSTreeLeafCount(q) << endl;
	cout << "Press any key and delete 'd'\n";
	cin.get();
	t.BSTDelete(q, 'd');

	cout << "中序遍历二叉搜索树:\n";
	t.Inorder(q);
	cout << "\n二叉搜索树的结点数=" << t.BSTSize() << endl;
	cout << "二叉搜索树的结点数=" << t.BSTreeCount(q) << endl;
	cout << "二叉搜索树的深度=" << t.BSTreeDepth(q) << endl;
	cout << "二叉搜索树的叶子结点数=" << t.BSTreeLeafCount(q) << endl;
	cin.get();
	t.FreeBST(q);
}


