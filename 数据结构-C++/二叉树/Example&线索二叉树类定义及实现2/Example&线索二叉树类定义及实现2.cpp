// 线索二叉树类定义及实现2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<iomanip>
#include<stdlib.h>
#include<conio.h>
#include"TBSTree.h"

using namespace std;
void main()
{
	THNode<char> *q, *p;
	TBSTree<char> t;

	q = t.MakeCharT(q, 2);
	cout << "线索二叉树的中序正向遍历序列为:\n";
	t.InThread(q);
	t.ThInorder(q);
	TBSTree<char> d;
	p = d.MakeCharT(p, 1);
	cout << "\n线索二叉树的中序正向遍历序列为:\n";
	d.InThread(p);
	d.ThInorder(p);
	cout << endl;
}











