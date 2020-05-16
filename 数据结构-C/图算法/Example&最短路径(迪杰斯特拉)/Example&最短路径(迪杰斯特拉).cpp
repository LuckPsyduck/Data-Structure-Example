// 最短路径(迪杰斯特拉).cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"迪杰斯特拉.h"

int main()
{
	int i, j;
	MGraph g;
	PathMatrix p;
	ShortPathTable d;
	CreateDN(g);
	Display(g);
	ShortestPath_DIJ(g, 0, p, d);

	printf("最短路径数组p[i][j]如下:\n");
	for (i = 0; i < g.vexnum; ++i)
	{
		for (j = 0; j < g.vexnum; ++j)
			printf("%2d", p[i][j]);
		printf("\n");
	}
	printf("%s到各顶点的最短路径长度为:\n", g.vexs[0].name);
	for (i = 0; i < g.vexnum; ++i)
		if (i != 0)
			printf("%s--%s: %d\n", g.vexs[0].name, g.vexs[i].name, d[i]);
    return 0;
}

