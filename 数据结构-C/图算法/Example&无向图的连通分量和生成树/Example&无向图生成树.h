#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define ERROR 0
#define OK 1
#define TRUE 1
#define FALSE 0
/*********************************************************************/
#define MAX_NAME 9//顶点名称字符串的最大长度+1
struct VertexType
{
	char name[MAX_NAME];//顶点名称
};

void Visit(VertexType ver)
{
	printf("%s ", ver.name);
}

void Input(VertexType &ver)
{
	scanf("%s", ver.name);
}

void InputFromFile(FILE *f, VertexType &ver)
{
	fscanf(f, "%s", ver.name);
}
/*********************************************************************/
typedef int VRType;
struct InfoType		//弧(边)的相关信息
{
	VRType weight;
};

void InputArc(InfoType *&arc)
{
	arc = (InfoType *)malloc(sizeof(InfoType));
	scanf("%d", &arc->weight);
}

void OutputArc(InfoType *arc)
{
	printf(": %d ", arc->weight);
}

void InputArcFromFile(FILE *f, InfoType *&arc)
{
	arc = (InfoType *)malloc(sizeof(InfoType));
	fscanf(f, "%d", &arc->weight);
}

/**********************************************************/
typedef VertexType TElemType;
typedef struct CSNode
{
	TElemType data;
	CSNode *firstchild, *nextsibling;
}CSNode,*CSTree;

void PreOrderTraverse(CSTree T, void(*Visit)(TElemType))
{
	if (T)
	{
		Visit(T->data);
		PreOrderTraverse(T->firstchild, Visit);
		PreOrderTraverse(T->nextsibling, Visit);
	}
}


/***************************************/
#define MAX_VERTEXT_NUM 20		//最大顶点数
enum GraphKind { DG, DN, UDG, UDN };//有向图 网 无向图 网

struct ElemType
{
	int adjvex;//该弧所指向的顶点的位置
	InfoType *info;//该弧相关信息(包括网的权值)的指针
};
struct ArcNode//表结点,存弧的信息
{
	ElemType data;
	ArcNode *nextarc;//指向下一条弧的指针
};
typedef struct//头结点，存顶点的信息
{
	VertexType data;//顶点信息
	ArcNode *firstarc;//第一个表结点的地址,指向第1条依复该顶点的弧的指针
}VNode, AdjList[MAX_VERTEXT_NUM];

struct ALGraph
{
	AdjList vertices;
	int vexnum, arcnum;
	GraphKind kind;//图的种类
};
#define LNode ArcNode
#define next nextarc
typedef ArcNode *LinkList;

/***************************链表的基本操作*************************************/
typedef int Status;
#define DestroyList ClearList

void InitList(LinkList &L)
{
	L = NULL;
}

void ClearList(LinkList &L)
{
	LinkList p;
	while (L)
	{
		p = L;
		L = L->next;
		free(p);
	}
}

Status ListEmpty(LinkList L)
{
	if (L)
		return false;
	else
		return true;
}

int ListLength(LinkList L)
{
	int i = 0;
	LinkList p = L;
	while (p)
	{
		i++;
		p = p->next;
	}
	return i;
}

Status GetElem(LinkList L, int i, ElemType &e)
{
	int j = 1;
	LinkList p = L;
	if (i < 1)
		return ERROR;
	while (j<i&&p)
	{
		j++;
		p = p->next;
	}
	if (j == i&&p)
	{
		e = p->data;
		return OK;
	}
	return ERROR;
}

int LocateElem(LinkList L, ElemType e, Status(*compare)(ElemType, ElemType))
{
	int i = 0;
	LinkList p = L;
	while (p)
	{
		i++;
		if (compare(p->data, e))
			return i;
		p = p->next;
	}
	return 0;
}

Status ListInsert(LinkList &L, int i, ElemType e)
{
	int j = 1;
	LinkList s, p = L;
	if (i < 1)
		return ERROR;
	s = (LinkList)malloc(sizeof(LNode));
	s->data = e;
	if (i == 1)
	{
		s->next = L;
		L = s;
	}
	else
	{
		while (p&&j<i - 1)
		{
			j++;
			p = p->next;
		}
		if (!p)
			return ERROR;
		s->next = p->next;
		p->next = s;
	}
	return OK;
}

Status ListDelete(LinkList &L, int i, ElemType &e)
{
	int j = 1;
	LinkList q, p = L;
	if (!L)
		return ERROR;
	else if (i == 1)
	{
		L = p->next;
		e = p->data;
		free(p);
	}
	else
	{
		while (p->next&&j<i - 1)
		{
			j++;
			p = p->next;
		}
		if (!p->next || j > i - 1)
			return ERROR;
		q = p->next;
		p->next = q->next;
		e = q->data;
		free(q);
	}
	return OK;
}

void ListTraverse(LinkList L, void(*visit)(ElemType))
{
	LinkList p = L;
	while (p)
	{
		visit(p->data);
		p = p->next;
	}
	printf("\n");
}

/*****************************************************************/

//查找表L中与e满足equal()条件的结点，诺找到，则返回指向该结点的指针，p指向该结点的前驱
//如果该结点是首元结点，则p=NULL
LinkList Point(LinkList L, ElemType e, Status(*equal)(ElemType, ElemType), LinkList &p)
{
	int j, i = LocateElem(L, e, equal);//查找表L中与e满足equal()条件的结点
	if (i)
	{
		if (i == 1)
		{
			p = NULL;
			return L;
		}
		p = L;//不是首元结点，则p指向第一个1个结点
		for (j = 2; j < i; j++)//p指向所找结点的前驱
			p = p->next;
		return p->next;//返回所找到结点的指针
	}
	return NULL;
}

/*************************图的邻接表存储**************************************/
int LocateVex(ALGraph G, VertexType u)//诺G中存在顶点u(顶底名字相同)，则返回该顶点在图中的位置(序号)
{
	int i;
	for (i = 0; i < G.vexnum; i++)
		if (strcmp(u.name, G.vertices[i].data.name) == 0)
			return i;
	return -1;
}

void CreateGraph(ALGraph &G)//
{
	int i, j, k;
	VertexType v1, v2;//顶点类型
	ElemType e;//表结点的元素类型(存储弧的信息)
	char s[3] = "边";
	printf("请输入图的类型(有向图:0 有向网:1 无向图:2 无向网:3): ");
	scanf("%d", &G.kind);
	if (G.kind < 2)
		strcpy(s, "弧");
	printf("请输入图的顶点数,边数: ");
	scanf("%d,%d", &G.vexnum, &G.arcnum);
	printf("请输入%d个顶点的值(<%d个字符): \n", G.vexnum, MAX_NAME);
	for (i = 0; i < G.vexnum; i++)
	{
		Input(G.vertices[i].data);//输入顶点信息
		G.vertices[i].firstarc = NULL;
	}
	printf("请输入%d条%s的", G.arcnum, s);
	switch (G.kind)
	{
	case DG:printf("弧尾 弧头: \n"); break;
	case DN:printf("弧尾 弧头 弧的信息: \n"); break;
	case UDG:printf("顶点1 顶点2: \n"); break;
	case UDN:printf("顶点1 顶点2 边的信息:\n"); break;
	default:
		break;
	}
	for (k = 0; k < G.arcnum; ++k)
	{
		scanf("%s %s", v1.name, v2.name);
		i = LocateVex(G, v1);//弧尾
		j = LocateVex(G, v2);//弧头
		e.info = NULL;			//给待插表结点e赋值，设图无弧(边)信息
		if (G.kind % 2)//网
			InputArc(e.info);
		e.adjvex = j;//弧头
		ListInsert(G.vertices[i].firstarc, 1, e);//将e插在第一个i个元素(出弧)的表头//则出 入点变成一对
		if (G.kind >= 2)//无向
		{
			e.adjvex = i;
			ListInsert(G.vertices[j].firstarc, 1, e);//插在第j个表头(入，出变成一对)
		}
	}
}

void CreateFromFile(ALGraph &G, char *filename)//由文件构造G
{
	int i, k, j;
	VertexType v1, v2;
	ElemType e;
	FILE *f;
	f = fopen(filename, "r");
	fscanf(f, "%d", &G.kind);
	fscanf(f, "%d", &G.vexnum);
	for (i = 0; i < G.vexnum; ++i)
	{
		InputFromFile(f, G.vertices[i].data);
		G.vertices[i].firstarc = NULL;
	}
	fscanf(f, "%d", &G.arcnum);
	for (k = 0; k < G.arcnum; k++)
	{
		fscanf(f, "%s %s", v1.name, v2.name);
		i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		e.info = NULL;
		if (G.kind % 2)
			InputArcFromFile(f, e.info);
		e.adjvex = j;
		ListInsert(G.vertices[i].firstarc, 1, e);
		if (G.kind >= 2)
		{
			e.adjvex = i;
			ListInsert(G.vertices[j].firstarc, 1, e);
		}
	}
	fclose(f);
}

VertexType GetVex(ALGraph G, int v)//v是G的顶点，返回v的值
{
	if (v >= G.vexnum || v < 0)
		exit(EXIT_FAILURE);
	return G.vertices[v].data;
}

Status PutVex(ALGraph &G, VertexType v, VertexType value)//v是G的顶点，对v赋新值
{
	int k = LocateVex(G, v);//k为顶点v在G中的序号
	if (k != -1)
	{
		G.vertices[k].data = value;
		return OK;
	}
	return ERROR;
}

int FirstAdjVex(ALGraph G, int v)//v是G 中的某个顶点序号，返回v中的第一个邻接顶点的序号
{
	ArcNode *p = G.vertices[v].firstarc;//p指向顶点v的第一个邻接顶点序号
	if (p)//顶点v有邻接顶点
		return p->data.adjvex;//返回v的第一个邻接顶点的序号
	else
		return -1;
}

Status Equalvex(ElemType a, ElemType b)
{
	if (a.adjvex == b.adjvex)//表结点的顶位置(序号)相同
		return OK;
	else
		return ERROR;
}

int NextAdjVex(ALGraph G, int v, int w)//v是G中某个顶点的序号，w是v的邻接顶点的序号，返回v的(相对于w的)下一个邻接顶点的序号
{															//诺w是v的最后一个邻接顶点，则返回-1
	LinkList p, p1;
	ElemType e;//表结点的元素类型(存储弧的信息)
	e.adjvex = w;
	p = Point(G.vertices[v].firstarc, e, Equalvex, p1);//p指向顶点v的链表中邻接顶点为w的结点
	if (!p || !p->next)//未找到w或w是最后一个邻接点
		return -1;
	else
		return p->next->data.adjvex;
}

void InsertVex(ALGraph &G, VertexType v)//在图G中增添新顶点v(不增添与顶点相关的弧,让InsertArc()去做)
{
	G.vertices[G.vexnum].data = v;
	G.vertices[G.vexnum].firstarc = NULL;
	G.vexnum++;
}

Status InsertArc(ALGraph &G, VertexType v, VertexType w)//在G中增添弧<v,w>,诺G是无向的，则还增添对称弧<w,v>
{
	ElemType e;//表结点的元素类型(存储弧的信息)
	int i, j;
	char s1[3] = "边", s2[3] = "-";
	if (G.kind < 2)//有向
	{
		strcpy(s1, "弧");
		strcpy(s2, "~");//矢量方向 例如A指向B
	}
	i = LocateVex(G, v);//弧尾或边的序号
	j = LocateVex(G, w);//弧头或边的序号
	if (i < 0 || j < 0)
		return ERROR;
	G.arcnum++;
	e.adjvex = j;//弧头表结点的值
	e.info = NULL;
	if (G.kind % 2)//网
	{
		printf("请输入 %s %s %s %s 的信息: ", s1, v.name, s2, w.name);
		InputArc(e.info);
	}
	ListInsert(G.vertices[i].firstarc, 1, e);//将e插在弧尾的表头//形成一对
	if (G.kind >= 2)//无向
	{
		e.adjvex = i;//弧尾表结点
		ListInsert(G.vertices[j].firstarc, 1, e);//将e插在弧头的表头
	}
	return OK;
}

Status DeleteArc(ALGraph &G, VertexType v, VertexType w)//在G中删除弧<v,w>,诺无向，则还删除对称弧<w,v>
{
	int i, j, n;
	ElemType e;
	i = LocateVex(G, v);//i是顶点v(弧尾)的序号
	j = LocateVex(G, w);//j是顶点w(弧头)的序号
	if (i < 0 || j < 0 || i == j)
		return ERROR;
	e.adjvex = j;//弧头表结点的值
	n = LocateElem(G.vertices[i].firstarc, e, Equalvex);//在弧尾链表中找弧头表结点，将其在链表中的位序赋给n
	if (n)
	{
		ListDelete(G.vertices[i].firstarc, n, e);//在弧尾链表中删除弧头表结点，并用e返回其值
		G.arcnum--;
		if (G.kind % 2)//网
			free(e.info);
		if (G.kind >= 2)//无向，删除对称弧<w,v>
		{
			e.adjvex = i;//弧尾表结点的值
			n = LocateElem(G.vertices[j].firstarc, e, Equalvex);//在弧头链表中找到弧尾表结点，将其位序赋给n
			ListDelete(G.vertices[j].firstarc, n, e);//在弧头链表中删除弧尾表结点
		}
		return OK;
	}
	else
		return ERROR;
}

Status DeleteVex(ALGraph &G, VertexType v)//删除G中顶点v及相关的弧(边)
{
	int i, k;
	LinkList p;
	k = LocateVex(G, v);//k为待删除顶点v的序号
	if (k < 0)
		return ERROR;
	for (i = 0; i < G.vexnum; i++)
		DeleteArc(G, v, G.vertices[i].data);//删除由顶点v出发的所有弧
	if (G.kind < 2)//有向
		for (i = 0; i < G.vexnum; i++)
			DeleteArc(G, G.vertices[i].data, v);//删除发向顶点v的所有弧
	for (i = 0; i < G.vexnum; i++)
	{
		p = G.vertices[i].firstarc;//p指向弧结点的单链表
		while (p)//未到表尾
		{
			if (p->data.adjvex > k)
				p->data.adjvex--;//序号-1 因为前移
			p = p->next;//p指向下一结点
		}
	}
	for (i = k + 1; i < G.vexnum; i++)
		G.vertices[i - 1] = G.vertices[i];//顶点v后面的顶点依次前移
	G.vexnum--;
	return OK;
}

void DestroyGraph(ALGraph &G)
{
	int i;
	for (i = G.vexnum - 1; i >= 0; i--)
		DeleteVex(G, G.vertices[i].data);//依次删除顶点及相关的弧
}

void Display(ALGraph &G)

{
	int i;
	ArcNode *p;
	char s1[3] = "边", s2[3] = "-";//无向
	if (G.kind < 2)//有向
	{
		strcpy(s1, "弧");
		strcpy(s2, "~");
	}
	switch (G.kind)
	{
	case DG:printf("有向图\n"); break;
	case DN:printf("有向网\n"); break;
	case UDG:printf("无向图\n"); break;
	case UDN:printf("无向网\n"); break;
	default:
		break;
	}
	printf("%d个顶点,依次是: ", G.vexnum);
	for (i = 0; i < G.vexnum; i++)
		Visit(GetVex(G, i));//访问第i个顶点
	printf("\n%d条%s:\n", G.arcnum, s1);
	for (i = 0; i < G.vexnum; i++)
	{
		p = G.vertices[i].firstarc;//p为指向序号为i的顶点的第1条弧
		while (p)
		{
			if (G.kind <= 1 || i < p->data.adjvex)//有向或无向两次中的一次
			{
				printf("%s%s%s\t", G.vertices[i].data.name, s2, G.vertices[p->data.adjvex].data.name);
				if (G.kind % 2)//网
					OutputArc(p->data.info);//输出弧边的信息
			}
			p = p->nextarc;//p指向下一个表结点
		}
		printf("\n");
	}
}

/*********************************************************************************/
bool visited[MAX_VERTEXT_NUM];
typedef ALGraph Graph;
void DFSTree(Graph G, int v, CSTree &T)//从第个顶点出发深度优先遍历图G，建立以T为根的生成树
{
	bool first = TRUE;//树T 还没有第一个孩子结点的标志
	int w;
	CSTree p, q=NULL;//孩子兄弟二叉链表结点的指针类型
	visited[v] = TRUE;//顶底v被访问的标志
	for (w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w))//w依次为v的邻接顶底
		if (!visited[w])
		{
			p = (CSTree)malloc(sizeof(CSNode));//分配孩子结点给p
			p->data = GetVex(G, w);//将顶点w的值赋给孩子结点的data域
			p->firstchild = NULL;//
			p->nextsibling = NULL;
			if (first)//顶点w是根的第一个未被访问的邻接顶底
			{
				T->firstchild = p;//顶点w是根的第1个孩子结点
				first = FALSE;//树T有第一个孩子结点的标志
			}
			else//顶点w是顶点v的其他未被访问的邻接顶底
				q->nextsibling = p;//是上一个邻接顶点的兄弟结点
			q = p;//
			DFSTree(G, w, q);//从第w个顶点出发深度优先遍历图，建立子生成树q
		}//完整的一次深度搜索完成会产生一个子生成树,以第一个未被建立的点作为根
}
/*此段程序结合图来分析，先选择一个点作为根结点，在选择一个邻接点做为左孩子，再以左孩子作为根结点建立树结构，当邻接左
孩子都找完了后，回退到上一层的根结点，找非邻接点(兄弟结点)作为右孩子，然后依次向上回溯，依次建立层根结点的非邻结点作
为右孩子，直到这棵树建立完成。
再找在树中未出现的顶点，再次深度优先查找建立树。
最后将所有子树建立成一棵树，孩子-兄弟表示法
*/
void DFSForest(Graph G, CSTree &T)//建立无向图G的深度优先生成深林的(最左)孩子(下一个)兄弟链表T
{
	CSTree p, q=NULL;
	int v;
	T = NULL;
	for (v = 0; v < G.vexnum; v++)
		visited[v] = FALSE;
	for(v=0;v<G.vexnum;v++)
		if (!visited[v])
		{
			p = (CSTree)malloc(sizeof(CSNode));//第v个顶点为新的生成树的根节点
			p->data = GetVex(G, v);
			p->firstchild = NULL;
			p->nextsibling = NULL;
			if (!T)//p所指的结点是第一棵生成树T的根结点
				T = p;
			else//p是其他生成树的根(前一棵树根的"兄弟")
				q->nextsibling = p;//上一层
			q = p;
			DFSTree(G, v, p);//建立以p为根的生成树
		}
}