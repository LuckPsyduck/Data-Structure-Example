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


Status TopologicalOrder(ALGraph &G, SqStack &T)//TW为拓扑序列顶点栈，S为零入度顶点栈
{
	int i, k, count = 0;//已入栈顶点数，初值为0
	int indegree[MAX_VERTEXT_NUM];//存放各顶点当前入度数
	SqStack S;
	ArcNode *p;
	FindInDegree(G, indegree);
	InitStack(S);
	printf("拓扑序列: ");
	for (i = 0; i < G.vexnum; i++)
		if (!indegree[i])
			Push(S, i);//将i入零入度顶点栈
	InitStack(T);
	for (i = 0; i < G.vexnum; i++)//初始化ve=0
		G.vertices[i].data.ve = 0;
	while (!StackEmpty(S))//当零入度顶点栈S不空
	{
		Pop(S, i);
		Visit(G.vertices[i].data);
		Push(T, i);//j号顶点入逆拓扑排序栈T(栈底元素为拓扑排序的第1个元素)
		++count;
		for (p = G.vertices[i].firstarc; p; p = p->nextarc)
		{
			k = p->data.adjvex;//序号为k
			if (--indegree[k] == 0)
				Push(S, k);
			//顶点i事件的最早发生时间+<i,k>的权值>顶点k事件的最早发生时间
			if (G.vertices[i].data.ve + p->data.info->weight > G.vertices[k].data.ve)
				G.vertices[k].data.ve = G.vertices[i].data.ve + p->data.info->weight;
			//k事件的最早发生的时间=i事件的最早发生的时间+<i,k>的权值
		}
	}
	if (count < G.vexnum)
	{
		printf("此时有向网有回路!\n");
		return ERROR;
	}
	else
		return OK;
}

Status CriticalPath(ALGraph &G)//输出各项关键活动
{
	SqStack T;
	int i, k, j;
	ArcNode *p;
	if (!TopologicalOrder(G, T))//产生有向环
		return ERROR;
	j = G.vertices[0].data.ve;

	for (i = 1; i < G.vexnum; i++)//找ve最大的值，然后用于逆向减，得到vl
		if (G.vertices[i].data.ve > j)
			j = G.vertices[i].data.ve;

	for (i = 0; i < G.vexnum; i++)
		G.vertices[i].data.vl = j;
	while (!StackEmpty(T))//按拓扑逆序求各顶点的v1的值
		for (Pop(T, j), p = G.vertices[j].firstarc; p; p = p->nextarc)
		{//弹出栈T的元素，赋给j,p指向顶点j的后继事件(出弧)顶点k
			k = p->data.adjvex;//后继事件顶点的序号
			if (G.vertices[k].data.vl - p->data.info->weight < G.vertices[j].data.vl)
				//事件j的最迟发生时间>其直接后继事件k的最迟发生时间-<j,k>的权值
				G.vertices[j].data.vl = G.vertices[k].data.vl - p->data.info->weight;//逆向减，
			//事件j的最迟发生时间=事件k的最迟发生时间-<j,k>的权值
			//由于k已逆拓扑有序，故G.vertices[k].data.v1不在改变
		}
	printf("\ni  ve  vl\n");
	for (i = 0; i < G.vexnum; i++)
	{
		printf("%d", i);
		Visitel(G.vertices[i].data);//输出ve,vl
		if (G.vertices[i].data.ve == G.vertices[i].data.vl)//最早发生的时间=最迟发生的时间
			printf("关键路径经过的顶点:");
		printf("\n");
	}

	printf("j  k  权值  ee  el\n");//求ee,el和关键活动
	for(j=0;j<G.vexnum;++j)
		for (p = G.vertices[j].firstarc; p; p = p->nextarc)
		{
			k = p->data.adjvex;
			p->data.info->ee = G.vertices[j].data.ve;//ee=弧尾的ve//最早开始时间

			p->data.info->el = G.vertices[k].data.vl - p->data.info->weight;//el=弧头的最迟开始时间-弧边的权值

			printf("%s--%s", G.vertices[j].data.name, G.vertices[k].data.name);
			OutputArcel(p->data.info);
			if (p->data.info->ee == p->data.info->el)
				printf("关键活动!");
			puts("\n");
		}
	return OK;
}