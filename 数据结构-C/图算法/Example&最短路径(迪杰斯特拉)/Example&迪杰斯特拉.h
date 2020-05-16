#pragma once
#include"图的数组.h"

typedef Status PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//路径矩阵
typedef VRType ShortPathTable[MAX_VERTEX_NUM];//最短路径表

void ShortestPath_DIJ(MGraph G, int v0,PathMatrix P, ShortPathTable D)
{			//用Dijkstra算法求有向网G中的v0到其余顶点v的最短路径P[v]及带权长度D[v]
			//当P[v][w]为TRUE，则w是从v0到v当前求得最短路径上的顶点
			//final[v]为TRUE,当且仅当v属于S，即求得从v0到v的最短路径	
	int v, w, i,j;
	VRType min;
	Status final[MAX_VERTEX_NUM];//辅助矩阵，为真表示该顶点到v0的最短距离已经求出，初值为假

	for (v = 0; v < G.vexnum; ++v)
	{
		final[v] = FALSE;
		D[v] = G.arcs[v0][v].adj;//D[]存放v0到v的最短距离，初值为v0到v的直接距离
		for (w = 0; w < G.vexnum; ++w)
			P[v][w] = FALSE;//p[][]初值为FALSE，没有路径

		if (D[v] < INFINITY)//v0到v有直接路径
			P[v][v0] = P[v][v] = TRUE;
		//一维数组p[v][]表示源点v0到v最短路径通过的顶点，目前通过v0和v两个顶点
	}
	D[v0] = 0;//v0到v0的距离为0
	final[v0] = TRUE;//v0并入S，相当于修改标志
	for (i = 1; i < G.vexnum; ++i)//每次求得v0到某个顶点v的最短路径，并将v并入S
	{
		min = INFINITY;
		for (w = 0; w < G.vexnum; ++w)
			if (!final[w] && D[w] < min)//在S集之外的顶点(其final[]=FALSE)中
			{					//找出离v0最近的顶点w,并将其值赋给v，距离赋给min
				v = w;
				min = D[w];
			}
		final[v] = TRUE;//v入集合S

		for(w=0;w<G.vexnum;++w)//根据新并入的顶点，更新不在S集中的顶点到v0的距离和路径数组
			if (!final[w] && min < INFINITY&&G.arcs[v][w].adj < INFINITY && (min + G.arcs[v][w].adj < D[w]))
			{										//w不属于S集且v0-v-w的距离<v0-w的距离
				D[w] = min + G.arcs[v][w].adj;		//更新D[w]
				for (j = 0; j < G.vexnum; j++)
					P[w][j] = P[v][j];		//修改P[w],v0到w经过的顶点包括v0到v经过的顶点再加上顶点w
				P[w][w] = TRUE;				//更新路径
			}
	}
}