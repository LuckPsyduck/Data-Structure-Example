// 最短路径(弗洛依德算法).cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"弗洛依德.h"

int main()
{
	MGraph g;
	int i, j, k;
	PathMatrix p;
	DistancMatrix d;
	CreateDN(g);
	for (i = 0; i < g.vexnum; i++)
		g.arcs[i][i].adj = 0;
	Display(g);
	ShortestPath_FLOYD(g, p, d);
	printf("d矩阵:\n");
	for (i = 0; i < g.vexnum; i++)
	{
		for (j = 0; j < g.vexnum; j++)
			printf("%6d", d[i][j]);
		printf("\n");
	}
	printf("p矩阵:\n");
	for(i=0;i<g.vexnum;i++)
		for(j=0;j<g.vexnum;j++)
			if (i != j)
			{
				printf("由%s 到 %s 经过: ", g.vexs[i].name, g.vexs[j].name);
				for (k = 0; k < g.vexnum; k++)
					if (p[i][j][k] == 1)
						printf("%s ", g.vexs[k].name);
				printf("\n");
			}
    return 0;
}

