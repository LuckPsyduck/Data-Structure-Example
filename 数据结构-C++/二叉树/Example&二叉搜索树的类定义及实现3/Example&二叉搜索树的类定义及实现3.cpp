// 二叉搜索树的类定义及实现2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"BSTree.h"
using namespace std;

void main()
{
	ElemType b[10] = { { "1001",72 },{ "1002",84 },{ "1009",83 },{ "1010",75 },
	{ "1012",87 },{ "1013",79 },{ "1019",91 },{ "1020",84 } };

	ElemType m = { "1014",89 }, m2 = { "1016",90 };
	int n, m1 = 8;
	char f[20] = ".\\file.txt";
	BSTree<ElemType> t, *B;
	t.InitBSTree(B);
	t.CreateBSTree(B, b, m1);
	n = t.BSTreeCount(B);
	cout << "二叉搜索树的所有结点数=" << n << endl;
	if (!t.BSTreeEmpty(B))
		cout << "二叉搜索树非空!\n";
	else
		cout << "二叉搜索树为空!\n";
	cout << "中序遍历:"; t.Inorder(B); 
	cout << endl;

	n = t.BSTreeDepth(B);
	cout << "二叉搜索树的深度=" << n << endl;

	n = t.BSTreeLeafCount(B);
	cout << "二叉搜索树的所有叶子结点数=" << n << endl;

	cout << "按二叉搜索树的广义表:\n(";
	t.PrintBSTree(B); cout << ')' << endl;

	t.Insert(B, m);
	cout << "中序遍历:";
	t.Inorder(B); 
	cout << endl;
	if (t.Find(B, m)) 
		cout << "查找成功!\n";
	else
		cout << "查找不成功!\n";

	m = b[6];
	if (t.Update(B, m, m2))
		cout << "更新成功!\n";
	else 
		cout << "更新不成功!\n";

	cout << "中序遍历:"; 
	t.Inorder(B); 
	cout << endl;

	n = t.BSTreeCount(B);
	cout << "二叉搜索树的所有结点数=" << n << endl;

	n = t.BSTreeDepth(B);
	cout << "二叉搜索树的深度=" << n << endl;

	if (t.Delete(B, m))
		cout << "删除成功!\n";
	else 
		cout << "删除不成功!\n";

	cout << "中序遍历:";
	t.Inorder(B); 
	cout << endl;

	n = t.BSTreeDepth(B);
	cout << "二叉搜索树的深度=" << n << endl;

	n = t.BSTreeCount(B);
	cout << "二叉搜索树的所有结点数=" << n << endl;

	cout << "输出所有成绩:\n";
	t.WriteFile(f, B);
	t.ReadFile(f, B);
	cin.get();
}



