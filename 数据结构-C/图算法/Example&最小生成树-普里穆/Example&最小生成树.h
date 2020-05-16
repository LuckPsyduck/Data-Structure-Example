#pragma once
#include"图的数组.h"

typedef struct
{
	int adjvex;
	VRType lowcost;
}minside[MAX_VERTEX_NUM];

int Minimum(minside SZ, MGraph G)//求SZ.lowcost 的最小正值，并返回其在SZ序号
{
	int i = 0, j, k, min;
	while (!SZ[i].lowcost)//找到第一个不为0的SZ[i].lowcost
		i++;
	min = SZ[i].lowcost;
	k = i;
	for(j=i+1;j<G.vexnum;j++)//向后查找
		if (SZ[j].lowcost > 0 && SZ[j].lowcost < min)//找到新的更小的值
		{
			min = SZ[j].lowcost;
			k = j;
		}
	return k;
}

void MinSpanTree_PRIM(MGraph G, VertexType u)//从u出发构造G的最小生成树T
{
	int i, j, k;
	minside closedge;
	k = LocateVex(G, u);//顶底的序号
	for (j = 0; j < G.vexnum; j++)//辅助数组初始化
	{
		closedge[j].adjvex = k;
		closedge[j].lowcost = G.arcs[k][j].adj;
	}
	closedge[k].lowcost = 0;//初始，相当于自己与自己的自己的距离

	printf("最小代价生成树的各条边为:\n");
	for (i = 1; i < G.vexnum; i++)//选择剩余的G.vexnum-1个顶点
	{
		k = Minimum(closedge, G);//找出最小生成树T的下一个结点
		printf("(%s-%s)\n", G.vexs[closedge[k].adjvex].name, G.vexs[k].name);
		closedge[k].lowcost = 0;//将其值修改，相当于修改标记
		for(j=0;j<G.vexnum;j++)
			if (G.arcs[k][j].adj < closedge[j].lowcost)//新顶点并入后，重新选择最小边
			{                                           //就是将下一个顶点中小于数组中的权值的权值给更新进来，替换掉
				closedge[j].adjvex = k;					//数组中较大的权值,就是更新数组
				closedge[j].lowcost = G.arcs[k][j].adj;
			}
	}
}