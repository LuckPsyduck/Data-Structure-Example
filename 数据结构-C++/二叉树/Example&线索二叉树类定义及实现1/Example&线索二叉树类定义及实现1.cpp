// 线索二叉树类定义及实现.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include"TBSTree.h"
#include"ITBSTree.h"
#include<iostream>
#include<iomanip>
#include<stdlib.h>
#include<conio.h>

using namespace std;

void main()
{
	THNode<char> *q, *p, *r;
	q = MakeCharT(q, 3);
	ITBSTree<char> t(q);
	t.CreatInThread();

	cout << "线索二叉树的中序正向遍历序列为:\n";
	for (t.First(); !t.EndOfNext(); t.Next())
		cout << t.Data() << "  ";

	cout << "\n线索二叉树的中序反向遍历序列为:\n";
	for (t.Last(); !t.EndOfPrior(); t.Prior())
		cout << t.Data() << "  ";

	p = MakeCharT(p, 2);
	ITBSTree<char> d(p);
	d.CreatInThread();

	cout << "\n线索二叉树的中序正向遍历序列为:\n";
	for (d.First(); !d.EndOfNext(); d.Next())
		cout << d.Data() << "  ";

	cout << "\n线索二叉树的中序反向遍历序列为:\n";
	for (d.Last(); !d.EndOfPrior(); d.Prior())
		cout << d.Data() << "  ";
	r = MakeCharT(r, 1);
	ITBSTree<char> h(r);
	h.CreatInThread();

	cout << "\n线索二叉树的中序正向遍历序列为:\n";
	for (h.First(); !h.EndOfNext(); h.Next())
		cout << h.Data() << "  ";

	d.InsertR(p, r);
	cout << "\n插入结点后线索二叉树的中序正向遍历序列为:\n";
	for (d.First(); !d.EndOfNext(); d.Next())
		cout << d.Data() << "  ";
	cout << endl;
	//cin.get();
}





















