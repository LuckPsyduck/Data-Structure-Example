// 拓扑结构(有向无环图).cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"拓扑排序.h"

int main()
{
	ALGraph f;
	printf("请选择有向图:\n");
	CreateGraph(f);
	Display(f);
	TopologicalSort(f);
    return 0;
}

