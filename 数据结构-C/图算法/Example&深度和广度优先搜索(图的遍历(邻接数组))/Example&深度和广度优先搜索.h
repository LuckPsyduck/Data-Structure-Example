#pragma once
#include<stdlib.h>
#include<string.h>
#define TRUE 1
#define ERROR 0
#define FALSE 0
#define TRUE 1
#define OK 1

typedef int Status;
/**************************图的数组存储结构*************************/

#define INFINITY INT_MAX     //整型最大值替代无穷符号
#define MAX_VERTEX_NUM 26	//最大顶点数
typedef int VRType;           //定义顶点的关系类型为整型，与INFINITY的类型一致
enum GraphKind { DG, DN, UDG, UDN };//有向图 网  无向图 网

typedef char InfoType;//弧边的相关

typedef struct  //边弧的信息结构
{
	VRType adj;      //顶点关系结构 对无权，用1(是)0(否)表示是否相邻；对带权图为权值
	InfoType *info;   //该弧相关信息指针
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];


#define MAX_NAME 9//顶点名称字符串的最大长度+1
struct VertexType
{
	char name[MAX_NAME];//顶点名称
};

struct MGraph
{
	VertexType vexs[MAX_VERTEX_NUM];			//顶点向量
	AdjMatrix arcs;								//邻接矩阵
	int vexnum, arcnum;							 //顶点数和弧数
	GraphKind kind;								//图的种类标志
};
typedef MGraph Graph;
/******************顶点信息类型的定义及操作********************************/
//
//#define MAX_NAME 9//顶点名称字符串的最大长度+1
//
//struct VertexType
//{
//	char name[MAX_NAME];//顶点名称
//};
void Visit(VertexType ver)
{
	printf("%s ", ver.name);
}

void Input(VertexType &ver)
{
	scanf("%s", ver.name);
}

void InputFormFile(FILE *f, VertexType &ver)
{
	fscanf(f, "%s", ver.name);
}
/************************弧(边)的相关信息类型的定义及操作**********************************/

#define MAX_INFO 20 //弧边相关信息字符串的最大长度+1
/*typedef char InfoType;*/      //弧边的相关

void InputArc(InfoType * &arc)//与之配套的输入弧(边)的相关信息   //对指针的引用，改变其值
{
	char temp[MAX_INFO];
	int m;
	printf("请输入该弧的相关信息(<%d个字符):", MAX_INFO);
	gets_s(temp);
	m = strlen(temp);
	if (m)
	{
		arc = (char *)malloc((m + 1) * sizeof(char));
		strcpy(arc, temp);
	}
}

void InputArcFormFile(FILE * f, InfoType * &arc)//由文件输入弧(边)的相关信息
{
	char temp[MAX_INFO];
	fgets(temp, MAX_INFO, f);
	arc = (char *)malloc((strlen(temp) + 1) * sizeof(char));//加上\0
	strcpy(arc, temp);
}

void OutputArc(InfoType *arc)//输出配套的弧(边)的相关信息
{
	printf("%s\n", arc);
}

/*************************************t图的邻接矩阵存储基本操作********************************/

int LocateVex(MGraph G, VertexType u)//诺图中存在顶点u，则返回其在途中的位置(序号)
{
	int i;
	for (i = 0; i < G.vexnum; ++i)
		if (strcmp(u.name, G.vexs[i].name) == 0)
			return i;
	return -1;
}

void CreateDG(MGraph &G)//构造有向图G
{
	int i, j, k, IncInfo;		//IncInfo为0 则弧不含相关信息
	VertexType v1, v2;			//顶点类型
	printf("请输入有向图的顶点数，弧数，弧是否有相关信息(是:1 否:0):");
	scanf("%d,%d,%d", &G.vexnum, &G.arcnum, &IncInfo);
	printf("请输入%d个顶点的值(名称<%d个字符):\n", G.vexnum, MAX_NAME);

	for (i = 0; i < G.vexnum; i++)		//构造顶点向量
		Input(G.vexs[i]);

	for (i = 0; i < G.vexnum; i++)//初始化二维邻接矩阵(弧(边)的信息)
		for (j = 0; j < G.vexnum; j++)
		{
			G.arcs[i][j].adj = 0;//图，不相邻
			G.arcs[i][j].info = NULL;
		}
	printf("请输入%d条弧的弧尾 弧头:\n", G.arcnum);
	for (k = 0; k < G.arcnum; k++)
	{
		scanf("%s %s", v1.name, v2.name);
		getchar();//\0
		i = LocateVex(G, v1);//弧尾
		j = LocateVex(G, v2);//弧头
		G.arcs[i][j].adj = 1;//有向图
		if (IncInfo)//有相关信息
			InputArc(G.arcs[i][j].info);
	}
	G.kind = DG;//更改标志
}

void CreateDN(MGraph &G)//构造有向网
{
	int i, j, k, IncInfo;
	VRType w;//顶点关系类型
	VertexType v1, v2;//顶点类型
	printf("请输入有向网的顶点数，弧数，弧是否有相关信息(是:1 否:0):");
	scanf("%d,%d,%d", &G.vexnum, &G.arcnum, &IncInfo);
	printf("请输入%d个顶点的值(名称<%d个字符):\n", G.vexnum, MAX_NAME);
	for (i = 0; i < G.vexnum; i++)
		Input(G.vexs[i]);
	for (i = 0; i < G.vexnum; i++)
		for (j = 0; j < G.vexnum; j++)
		{
			G.arcs[i][j].adj = INFINITY;//网，不相邻
			G.arcs[i][j].info = NULL;
		}
	printf("请输入%d条弧的弧尾 弧头:\n", G.arcnum);
	for (k = 0; k < G.arcnum; k++)
	{
		scanf("%s %s %d%*c", v1.name, v2.name, &w);
		i = LocateVex(G, v1);//弧尾
		j = LocateVex(G, v2);//弧头
		G.arcs[i][j].adj = w;//有向网
		if (IncInfo)
			InputArc(G.arcs[i][j].info);
	}
	G.kind = DN;
}

void CreateUDG(MGraph &G)//构造无向图
{
	int i, j, k, IncInfo;
	VertexType v1, v2;		//顶点类型
	printf("请输入无向图的顶点数，弧数，弧是否有相关信息(是:1 否:0):");
	scanf("%d,%d,%d", &G.vexnum, &G.arcnum, &IncInfo);
	printf("请输入%d个顶点的值(名称<%d个字符):\n", G.vexnum, MAX_NAME);
	for (i = 0; i < G.vexnum; i++)
		Input(G.vexs[i]);
	for (i = 0; i < G.vexnum; i++)
		for (j = 0; j < G.vexnum; j++)
		{
			G.arcs[i][j].adj = 0;
			G.arcs[i][j].info = NULL;
		}
	printf("请输入%d条弧的顶点1 顶点 2:\n", G.arcnum);
	for (k = 0; k < G.arcnum; k++)
	{
		scanf("%s %s", v1.name, v2.name);
		getchar();
		i = LocateVex(G, v1);//顶点1的序号
		j = LocateVex(G, v2);//顶点2的序号
		G.arcs[i][j].adj = 1;//图
		if (IncInfo)
			InputArc(G.arcs[i][j].info);
		G.arcs[j][i] = G.arcs[i][j];//无向，两个单元的的信息相同
	}
	G.kind = UDG;
}

void CreateUDN(MGraph &G)//无向网
{
	int i, j, k, IncInfo;
	VRType w;		//顶点关系类型//权值
	VertexType v1, v2;
	printf("请输入有向网的顶点数，弧数，弧是否有相关信息(是:1 否:0):");
	scanf("%d,%d,%d", &G.vexnum, &G.arcnum, &IncInfo);
	printf("请输入%d个顶点的值(名称<%d个字符):\n", G.vexnum, MAX_NAME);
	for (i = 0; i < G.vexnum; i++)
		Input(G.vexs[i]);
	for (i = 0; i < G.vexnum; i++)
		for (j = 0; j < G.vexnum; j++)
		{
			G.arcs[i][j].adj = INFINITY;
			G.arcs[i][j].info = NULL;
		}
	printf("请输入%d条弧的顶点1 顶点 2 权值 :\n", G.arcnum);
	for (k = 0; k < G.arcnum; k++)
	{
		scanf("%s %s %d", v1.name, v2.name, &w);
		getchar();
		i = LocateVex(G, v1);//顶点1的序号
		j = LocateVex(G, v2);//顶点2的序号
		G.arcs[i][j].adj = w;//网
		if (IncInfo)
			InputArc(G.arcs[i][j].info);
		G.arcs[j][i] = G.arcs[i][j];//无向
	}
	G.kind = UDN;
}

void CreateGraph(MGraph &G)
{
	printf("请输入图G的类型(有向图:0 有向网:1 无向图:2 无向网:3):");
	scanf("%d", &G.kind);
	switch (G.kind)
	{
	case DG:CreateDG(G); break;
	case DN:CreateDN(G); break;
	case UDG:CreateUDG(G); break;
	case UDN:CreateUDN(G); break;
	default:
		break;
	}
}

VertexType GetVex(MGraph G, int v)//v是G中的某个顶点的序号，返回v的值
{
	if (v >= G.vexnum || v < 0)
		exit(EXIT_FAILURE);
	return G.vexs[v];//返回该顶点的信息
}

Status PutVex(MGraph &G, VertexType v, VertexType value)//v是G中的某个顶点，对v赋新值value
{
	int k = LocateVex(G, v);//k为顶点v在图G中的序号
	if (k < 0)
		return ERROR;
	G.vexs[k] = value;
	return OK;
}

int FirstAdjVex(MGraph G, int v)//v是G中某个顶点的序号，返回v的第一个邻接顶点的序号
{
	int i;
	VRType j = 0;
	if (G.kind % 2)//(DG,DN,UDG,UDN)
		j = INFINITY;//网
	for (i = 0; i < G.vexnum; i++)
		if (G.arcs[i][j].adj != j)
			return i;
	return -1;
}

int NextAdjVex(MGraph G, int v, int w)//v是G中某个顶点的序号，w是v的邻接顶点的序号，返回v的(相对于w的)下一个邻接顶点的序号
{
	int i;
	VRType j = 0;
	if (G.kind % 2)//(DG,DN,UDG,UDN)
		j = INFINITY;
	for (i = w + 1; i < G.vexnum; i++)
		if (G.arcs[v][i].adj != j)
			return i;
	return -1;
}

void InsertVex(MGraph &G, VertexType v)//添加新顶点v(不增加与顶点相关的弧)
{
	int i;
	VRType j = 0;
	if (G.kind % 2)//(DG,DN,UDG,UDN)
		j = INFINITY;
	G.vexs[G.vexnum] = v;
	for (i = 0; i <= G.vexnum; i++)//对于新增的行列
	{
		G.arcs[G.vexnum][i].adj = G.arcs[i][G.vexnum].adj = j;
		G.arcs[G.vexnum][i].info = G.arcs[i][G.vexnum].info = NULL;
	}
	G.vexnum++;
}

Status InsertArc(MGraph &G, VertexType v, VertexType w)//在G中添加弧<v,w>,诺G是无向的，则还添加对称弧<w,v>
{
	int i, v1, w1;
	v1 = LocateVex(G, v);//弧尾
	w1 = LocateVex(G, w);//弧头
	if (v1 < 0 || w1 < 0)
		return ERROR;
	G.arcnum++;
	if (G.kind % 2)//网
	{
		printf("请输入此弧或边的权值: ");
		scanf("%d", &G.arcs[v1][w1].adj);
	}
	else//图
		G.arcs[v1][w1].adj = 1;
	printf("是否含有该弧或边的相关信息(0:无 1:有): ");
	scanf("%d", &i);
	getchar();
	if (i)
		InputArc(G.arcs[v1][w1].info);
	if (G.kind > 1)//无向
		G.arcs[w1][v1] = G.arcs[v1][w1];
	return OK;
}

Status DeleteArc(MGraph &G, VertexType v, VertexType w)//在G中删除弧<v,w>,诺G是无向的，则还删除对称弧<w,v>
{
	int v1, w1;
	VRType j = 0;
	if (G.kind % 2)//网
		j = INFINITY;
	v1 = LocateVex(G, v);//弧尾
	w1 = LocateVex(G, w);//弧头
	if (v1 < 0 || w1 < 0)
		return ERROR;
	if (G.arcs[v1][w1].adj != j)//弧<v,w>存在
	{
		G.arcs[v1][w1].adj = j;//删除弧<v,w>
		if (G.arcs[v1][w1].info)//如果存在相关信息
		{
			free(G.arcs[v1][w1].info);
			G.arcs[v1][w1].info = NULL;
		}
		if (G.kind >= 2)//无向，删除对称的
			G.arcs[w1][v1] = G.arcs[v1][w1];
		G.arcnum--;
	}
	return OK;
}

Status DeleteVex(MGraph &G, VertexType v)//删除顶点v及相关的弧
{
	int i, j, k;
	k = LocateVex(G, v);//k为待删除顶点的序号
	if (k < 0)
		return ERROR;
	for (i = 0; i < G.vexnum; i++)
		DeleteArc(G, v, G.vexs[i]);//删除由顶点v出发的所有的弧
	if (G.kind < 2)//有向
		for (i = 0; i < G.vexnum; i++)//删除发向顶点v的所有弧
			DeleteArc(G, G.vexs[i], v);

	for (j = k + 1; j < G.vexnum; j++)
		G.vexs[j - 1] = G.vexs[j];//前移

								  //先移动，后删除
	for (i = 0; i < G.vexnum; i++)
		for (j = k + 1; j < G.vexnum; j++)
			G.arcs[i][j - 1] = G.arcs[i][j];//删除待删除顶点之右的矩阵元素

	for (i = 0; i < G.vexnum; i++)
		for (j = k + 1; j < G.vexnum; j++)//删除待删除顶点之下的矩阵元素
			G.arcs[j - 1][i] = G.arcs[j][i];

	G.vexnum--;
	return OK;
}

void DestroyGraph(MGraph &G)//销毁图G
{
	int i;
	for (i = G.vexnum - 1; i >= 0; i--)
		DeleteVex(G, G.vexs[i]);
}

void Display(MGraph G)
{
	int i, j;
	char s[7] = "无向网", s1[3] = "边";
	switch (G.kind)
	{
	case DG:strcpy(s, "有向图"); strcpy(s1, "弧"); break;
	case DN:strcpy(s, "有向网"); strcpy(s1, "弧"); break;
	case UDG:strcpy(s, "有向图");
	case UDN:;
	default:
		break;
	}
	printf("%d 个顶点 %d 条 %s 的 %s 顶点依次是 : ", G.vexnum, G.arcnum, s1, s);
	for (i = 0; i < G.vexnum; i++)
		Visit(GetVex(G, i));
	printf("\nG.arcs.adj:\n");
	for (i = 0; i < G.vexnum; i++)
	{
		for (j = 0; j < G.vexnum; j++)
			printf("%12d", G.arcs[i][j].adj);
		printf("\n");
	}
	printf("G.arcs.info: \n");
	if (G.kind < 2)
		printf("弧尾 弧头 该 %s 的信息:\n", s1);
	else
		printf("顶点 1 顶点 2 该 %s 的信息:\n", s1);
	for (i = 0; i<G.vexnum; i++)
		if (G.kind < 2)//有向
		{
			for (j = 0; j<G.vexnum; j++)
				if (G.arcs[i][j].info)
				{
					printf("%5s %5s ", G.vexs[i].name, G.vexs[j].name);
					OutputArc(G.arcs[i][j].info);
				}
		}
		else//无向 输出上三角 对称
			for (j = i + 1; j<G.vexnum; j++)
				if (G.arcs[i][j].info)
				{
					printf("%5s %5s ", G.vexs[i].name, G.vexs[j].name);
					OutputArc(G.arcs[i][j].info);
				}
}

void CreateFromFile(MGraph &G, char *filename, int IncInfo)//由文件构造图或网
{
	int i, j, k;
	VRType w = 0;
	VertexType v1, v2;
	FILE *f;
	f = fopen(filename, "r");
	fscanf(f, "%d", &G.kind);
	if (G.kind % 2)//网
		w = INFINITY;

	fscanf(f, "%d", &G.vexnum);
	for (i = 0; i < G.vexnum; i++)
		InputFormFile(f, G.vexs[i]);//由文件输入顶点信息

	fscanf(f, "%d", &G.arcnum);
	for (i = 0; i < G.vexnum; i++)
		for (j = 0; j < G.vexnum; j++)
		{
			G.arcs[i][j].adj = w;//不相邻
			G.arcs[i][j].info = NULL;
		}
	if (!(G.kind % 2))//图
		w = 1;
	for (k = 0; k < G.arcnum; ++k)//对于所有的弧
	{
		fscanf(f, "%s %s", v1.name, v2.name);
		if (G.kind % 2)
			fscanf(f, "%d", &w);//权值
		i = LocateVex(G, v1);//弧尾
		j = LocateVex(G, v2);//弧头
		G.arcs[i][j].adj = w;
		if (IncInfo)
			InputArcFormFile(f, G.arcs[i][j].info);
		if (G.kind > 1)//无向
			G.arcs[j][i] = G.arcs[i][j];
	}
	fclose(f);
}

/************************广度优先搜索(需要使用队列)***********************************************/

/*************************队列操作*****************************/
typedef int QElemType;

typedef struct QNode
{
	QElemType data;
	QNode *next;
}*QueuePtr;

struct LinkQueue
{
	QueuePtr front, rear;
};

void InitQueue(LinkQueue &Q)
{
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));//头结点
	if (!Q.front)
		exit(EXIT_FAILURE);
	Q.front->next = NULL;
}

void DestroyQueue(LinkQueue &Q)
{
	while (Q.front)
	{
		Q.rear = Q.front->next;
		free(Q.front);
		Q.front = Q.rear;
	}
}

void ClearQueue(LinkQueue &Q)
{
	DestroyQueue(Q);
	InitQueue(Q);
}

Status QueueEmpty(LinkQueue Q)
{
	if (Q.front->next == NULL)
		return true;
	else
		return false;
}

int QueueLength(LinkQueue Q)
{
	int i = 0;
	QueuePtr p = Q.front;
	while (Q.rear != p)
	{
		i++;
		p = p->next;
	}
	return i;
}

Status GetHead(LinkQueue Q, QElemType &e)//返回队头元素
{
	QueuePtr p;
	if (Q.front == Q.rear)
		return ERROR;
	p = Q.front->next;//队头元素
	e = p->data;
	return OK;
}

void EnQueue(LinkQueue &Q, QElemType e)//插入队尾元素
{
	QueuePtr p;
	p = (QueuePtr)malloc(sizeof(QNode));
	if (!p)
		exit(EXIT_FAILURE);
	p->data = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;//p变成尾结点
}

Status DeQueue(LinkQueue &Q, QElemType &e)//删除队头元素，用e返回
{
	QueuePtr p;
	if (Q.front == Q.rear)
		return ERROR;
	p = Q.front->next;
	e = p->data;
	Q.front->next = p->next;//相当于第二个
	if (Q.rear == p)
		Q.rear = Q.front;
	free(p);
	return OK;
}

void QueueTraverse(LinkQueue Q, void(*visit)(QElemType))
{
	QueuePtr p = Q.front->next;//队头结点
	while (p)
	{
		visit(p->data);
		p = p->next;
	}
	printf("\n");
}

/************************广度优先搜索算法******************************/
bool visite[MAX_VERTEX_NUM];
void(*VisitFunc)(VertexType);

void BFSTraverse(Graph G, void(*Visit)(VertexType))
{
	int v, u, w;
	LinkQueue Q;//使用辅助对列Q和访问标志数组visite
	for (v = 0; v < G.vexnum; v++)
		visite[v] = FALSE;//初始化访问标志数组visite
	InitQueue(Q);
	for(v=0;v<G.vexnum;v++)
		if (!visite[v])//顶点v未被访问
		{
			visite[v] = TRUE;//修改访问标志
			Visit(GetVex(G, v));//访问顶点v
			EnQueue(Q, v);//将其入队
			while (!QueueEmpty(Q))
			{
				DeQueue(Q, u);//出队，赋给u
				for (w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, u, w))//相邻的结点//相当于根结点的子结点
					if (!visite[w])											//一层一层的访问
					{
						visite[w] = TRUE;
						Visit(GetVex(G, w));//将其直系相邻的顶点访问
						EnQueue(Q, w);//然后将其入队，下次在访问其直系相邻的
					}
			}//其实其过程相当于层序遍历，只访问其顶点的直系连接点，然后在依次推
		}
	printf("\n");
}
/**************************************************************************/

/*************************深度优先搜索(不需要用到队列,使用递归)**********************************/
void DFS(Graph G, int v)//从v出发递归的深度遍历图
{
	int w;
	visite[v] = TRUE;
	VisitFunc(GetVex(G, v));//访问顶点v
	for (w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w))//从顶点v的第一个邻接点开始
		if (!visite[w])
			DFS(G, w);//对v的未访问的序号为w的邻接点递归调用
}

void DFSTraverse(Graph G, void(*Visit)(VertexType))//从第一个顶点开始
{
	int v;
	VisitFunc = Visit;
	for (v = 0; v < G.vexnum; v++)
		visite[v] = FALSE;
	for (v = 0; v < G.vexnum; v++)
		if (!visite[v])//v尚未访问
			DFS(G, v);
	printf("\n");
}
/************************************************************/
