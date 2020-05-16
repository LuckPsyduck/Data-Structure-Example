#pragma once
#include"图的数组.h"

typedef char PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef VRType DistancMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

void ShortestPath_FLOYD(MGraph G, PathMatrix P, DistancMatrix D)
{//用Floyd算法求有向网G中各对顶点v和w之间的最短路径P[v][w][]及其带权长度D[v][w]
	//P[v][w][u]为TRUE，则u是从v到w当前求得最短路径上的顶点
	int u, v, w, i;
	for(v=0;v<G.vexnum;v++)
		for (w = 0; w < G.vexnum; w++)
		{
			D[v][w] = G.arcs[v][w].adj;//顶点v到w的直接距离
			for (u = 0; u < G.vexnum; u++)
				P[v][w][u] = FALSE;//路径初始矩阵
			if (D[v][w] < INFINITY)//从v到w有直接距离
				P[v][w][v] = P[v][w][w] = TRUE;//由v到w的路径经过v和w两点
		}//这条最短路径已经包括了v,w两点

	for(u=0;u<G.vexnum;u++)
		for(v=0;v<G.vexnum;v++)
			for(w=0;w<G.vexnum;w++)
				if (D[v][u] < INFINITY&&D[u][w] < INFINITY && (D[v][u] + D[u][w]) < D[v][w])
				{						//从v经过u到w的一条路径更短
					D[v][w] = D[v][u] + D[u][w];
					for (i = 0; i < G.vexnum; i++)
						P[v][w][i] = P[v][u][i] || P[u][w][i];
				}//将分段的最短路径的顶点合并
}				//从v到w的路径经过从v到u和从u到w的所有路径
				//利用贪婪算法，每步最优