// 线索二叉树类定义及实现3.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


//线索二叉树类相关操作的测试TBSTree2M.cpp
#include<iostream>
#include<iomanip>
#include<stdlib.h>
#include<conio.h>
#include"TBSTree.h"
#include"ITBSTree.h"
using namespace std;

void main()
{
	THNode<char> *q, *p;
	q = MakeCharT(q, 2);
	ITBSTree<char> t(q);
	t.CreatInThread();
	cout << "二叉树的中序正向遍历序列为:\n";
	t.First();
	cout << "\n二叉树的中序反向遍历序列为:\n";
	t.Last();
	p = MakeCharT(p, 1);

	ITBSTree<char> d(p);
	d.CreatInThread();
	cout << "\n二叉树的中序正向遍历序列为:\n";
	d.First();
	cout << "\n二叉树的中序反向遍历序列为:\n";
	d.Last();
	cout << endl;
}












