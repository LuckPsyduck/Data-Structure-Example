// 深度优先搜索(图的遍历).cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"深度和广度优先搜索.h"

int main()
{
	Graph g;
	char filename[13];
	printf("请输入文件名:\n");
	scanf("%s", filename);
	CreateFromFile(g, filename, 0);
	printf("深度优先搜索遍历的结果:\n");
	DFSTraverse(g, Visit);
	printf("广度优先搜索遍历的结果:\n");
	BFSTraverse(g, Visit);
    return 0;

}

