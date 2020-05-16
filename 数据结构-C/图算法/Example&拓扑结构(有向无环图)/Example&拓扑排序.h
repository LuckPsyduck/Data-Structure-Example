#pragma once
#include"图存储结构.h"

void FindInDegree(ALGraph G, int indegree[])//求顶底的入度
{
	int i;
	ArcNode *p;
	for (i = 0; i < G.vexnum; i++)
		indegree[i] = 0;
	for (i = 0; i < G.vexnum; i++)
	{
		p = G.vertices[i].firstarc;//P指向顶点的邻接表的头指针
		while (p)//p不为空
		{
			indegree[p->data.adjvex]++;//将p所指的邻接顶点的入度+1,弧头+1
			p = p->nextarc;
		}
	}
}//则将所有顶点的入度都求出来了，被指则+1

Status TopologicalSort(ALGraph G)
{
	int i, k, count = 0;//已输出顶点数
	int indegree[MAX_VERTEXT_NUM];//入度的数组，存放各顶点的当前入度
	SqStack S;
	ArcNode *p;
	FindInDegree(G, indegree);

	InitStack(S);//初始化零入度顶点的栈S
	for (i = 0; i < G.vexnum; i++)
		if (!indegree[i])//当其入度为0
			Push(S, i);
	while (!StackEmpty(S))//当其不为空
	{
		Pop(S, i);//弹出赋给i
		printf("%s ", G.vertices[i].data.name);
		++count;//已输出的顶点数
		for (p = G.vertices[i].firstarc; p; p = p->nextarc)//对i的每个邻接顶点
		{
			k = p->data.adjvex;//序号 
			if (!(--indegree[k]))//入度-1,为0则入栈
				Push(S, k);
		}
	}
	if (count < G.vexnum)//没有完全输出
	{
		printf("此有向图有回路!\n");
		return ERROR;
	}
	else
	{
		printf("为一个拓扑序列!\n");
		return OK;
	}
}