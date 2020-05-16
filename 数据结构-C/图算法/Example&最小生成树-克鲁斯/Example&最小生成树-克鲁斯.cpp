// 最小生成树-克鲁斯.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"克鲁斯算法.h"

int main()
{
	MGraph g;
	char filename[13];
	printf("请输入数据的文件名:\n");
	scanf("%s", filename);
	CreateFormFile(g, filename, 0);
	Display(g);
	Kruskal(g);
    return 0;
}

