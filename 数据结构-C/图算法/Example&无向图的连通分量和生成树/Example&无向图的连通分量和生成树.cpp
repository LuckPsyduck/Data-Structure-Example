// 无向图的连通分量和生成树.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"无向图生成树.h"

int main()
{
	Graph g;
	CSTree t;
	printf("请选择无向图:\n");
	CreateGraph(g);
	Display(g);
	DFSForest(g, t);
	printf("先序遍历生成深林:\n");
	PreOrderTraverse(t, Visit);
	printf("\n");
    return 0;
}

