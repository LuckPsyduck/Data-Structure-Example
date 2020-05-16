#pragma once
#include"图的数组.h"

struct side//图的边信息存储结构
{
	int a, b;//两顶点
	VRType weight;
};

void Kruskal(MGraph G)
{
	int set[MAX_VERTEX_NUM], senumber = 0, sb, i, j, k;
	side se[MAX_VERTEX_NUM*(MAX_VERTEX_NUM - 1) / 2];//存储边信息，然后将其排序，依次取出，不符合的排除
													 //不符合的是由对称性引起的，所有边只能算一次	
	for(i=0;i<G.vexnum;i++)		//查找所有的边，并根据权值升序插到se中														
		for(j=i+1;j<G.vexnum;j++)//无向网，只考虑上三角
			if (G.arcs[i][j].adj < INFINITY)//i,j之间有边
			{
				k = senumber - 1;
				while (k >= 0)
					if (se[k].weight > G.arcs[i][j].adj)
					{
						se[k + 1] = se[k];
						k--;
					}
					else
						break;
				se[k + 1].a = i;//按照权值顺序进行装入，形成有序
				se[k + 1].b = j;
				se[k + 1].weight = G.arcs[i][j].adj;
				senumber++;
			}
	printf("i se[i].a se[i].b se[i].weight\n");
	for (i = 0; i < senumber; i++)//0-9
		printf("%d %4d %7d %9d\n", i, se[i].a, se[i].b, se[i].weight);
	for (i = 0; i < G.vexnum; i++)//初始化
		set[i] = i;
	printf("最小代价生成树的各条边为:\n");
	j = 0;//j指示se当前要并入最小生成树的边的序号，初值为0
	k = 0;//k指示当前构成最小生成树的边数
	while (k<G.vexnum-1)//最小生成树该有G.vexnum-1条边(从0开始)
	{
		if (set[se[j].a] != set[se[j].b])//j边所指的2顶点不属于同一个集合
		{
			printf("(%s-%s)\n", G.vexs[se[j].a].name, G.vexs[se[j].b].name);
			sb = set[se[j].b];
			for (i = 0; i < G.vexnum; i++)
				if (set[i] == sb)	//所有与顶点se[j].b在同一个集合中
					set[i] = set[se[i].a];	//将此顶点并入到顶点se[j].a所在的集合,从而避免二次输出
			k++;	//当前构成最小生成树的边数+1//只是循环查找的次数
		}
		j++;	//j指示se下一个要并入最小生成树的边序号
	}
}

