// 最小生成树.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"最小生成树.h"

int main()
{
	MGraph g;
	char filename[13];
	printf("请输入文件名:\n");
	scanf("%s", filename);
	CreateFormFile(g, filename, 0);
	Display(g);
	MinSpanTree_PRIM(g, g.vexs[0]);
    return 0;
}

