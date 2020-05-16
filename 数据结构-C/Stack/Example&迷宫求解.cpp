
#include"stdio.h"
#include<malloc.h>
#include<stdlib.h>
#include<stdio.h>

#define TRUE 1
#define FALSE 0
#define ERROR 0
#define OK 1

typedef int Status;

struct PosType//迷宫坐标位置类型
{
	int x;//行值
	int y;//列值
};

struct SElemType	//栈的元素类型
{
	int ord;			//通道块在路径上的“序号”
	PosType seat;			//通道块在迷宫中的“坐标位置”
	int di;					//从此通道块走向下一通道块的“方向”
};

/************************************栈结构及操作**********************************************/

#define STACK_INIT_SIZE 10//存储空间初始分配量
#define STACK_INCREMENT 2//存储空间分配增量

struct SqStack
{
	SElemType *base;
	SElemType *top;
	int stacksize;//当前已分配存储空间
};

void InitStack(SqStack &S)
{
	if (!(S.base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType))))
		exit(EXIT_FAILURE);
	S.top = S.base;//栈空
	S.stacksize = STACK_INIT_SIZE;//存储空间为初始分配量
}

Status StackEmpty(SqStack S)
{
	if (S.top == S.base)
		return TRUE;
	else
		return FALSE;
}

void Push(SqStack &S, SElemType e)
{
	//插入元素e为栈S新的栈顶元素
	if (S.top - S.base == S.stacksize)//沾满
	{
		S.base = (SElemType *)realloc(S.base, (S.stacksize + STACK_INCREMENT) * sizeof(SElemType));
		if (!S.base)
			exit(EXIT_FAILURE);
		S.top = S.base + S.stacksize;//修改栈顶指针，指向新的栈顶
		S.stacksize += STACK_INCREMENT;//更新当前已分配的存储空间
	}
	*(S.top)++ = e;//将e入栈，称为新的栈顶元素，栈顶指针上移1个存储单元
}

Status Pop(SqStack &S, SElemType &e)//
{
	//若S不为空，删除S的栈顶元素，用E返回其值
	if (S.top == S.base)
		return ERROR;//栈空
	else
		e = *--S.top;
	return OK;
}

/******************************************************************************************/

#define MAXLENGTH 25						//迷宫的最大行列为25

typedef int MazeType[MAXLENGTH][MAXLENGTH];//迷宫数组类型[行][列]
MazeType m;	//迷宫数组

int x, y;							//迷宫行数，列数

PosType begin, end;
PosType direct[4] = { { 0, 1 },{ 1, 0 },{ 0, -1 },{ -1, 0 } };//{行增量，列增量}，移动方向依次为东南西北

void Print()//输出迷宫的解
{
	int i, j;
	for (i = 0; i < x; i++)
	{
		for (j = 0; j < y; j++)
			printf("%3d", m[i][j]);
		printf("\n");
	}
}

void Init()							//设定迷宫布局，墙为0，通道为1
{
	int i, j, x1, y1;				//x1,y1内墙单元的行列数
	printf("输入迷宫的行，列数：");
	scanf("%d,%d", &x, &y);

	for (i = 0; i<y; i++)
	{
		m[0][i] = 0;//上边为0
		m[x - 1][i] = 0;
	}
	for (i = 1; i<x - 1; i++)
	{
		m[i][0] = 0;
		m[i][y - 1] = 0;
	}

	for (i = 1; i < x - 1; i++)
		for (j = 1; j < y - 1; j++)
			m[i][j] = 1;//定义出墙外，其余全是通道，初值为1

	printf("请输入迷宫内墙单元数：");
	scanf("%d", &j);
	printf("请依次输入迷宫内墙每个单元的行数，列数：\n");
	for (i = 1; i <= j; i++)
	{
		scanf("%d,%d", &x1, &y1);
		m[x1][y1] = 0;					//修改内墙的值为0
	}
	printf("迷宫的结构如下：\n");
	Print();						//直接调用函数
	printf("请输入入口的行数列数：");
	scanf("%d,%d", &begin.x, &begin.y);
	printf("请输入出口的行数列数：");
	scanf("%d,%d", &end.x, &end.y);
}

int curstep = 1;//当前足迹，初值为1，在入口处

Status Pass(PosType b)
{
	//挡迷宫的b点值为1（既可以通过），返回OK
	if (m[b.x][b.y] == 1)
		return OK;
	else
		return ERROR;
}

void FootPrint(PosType b)
{
	//使m的b点的值变为足迹（curstep）
	m[b.x][b.y] = curstep;
}

void NextPos(PosType &b, int di)
{                                  //根据当前位置b及移动方向di,修改b为下一位置
	b.x += direct[di].x;
	b.y += direct[di].y;
}

void MarkPrint(PosType b)
{
	m[b.x][b.y] = -1;
}

Status MazePath(PosType start, PosType end)
{
	PosType curpos = start;//当前位置在入口
	SqStack S;
	SElemType e;//栈元素
	InitStack(S);
	do
	{
		if (Pass(curpos))//当前位置可通过，也是未曾走过的通道块
		{
			FootPrint(curpos); //留下足迹，使迷宫当前位置的值为curstep
			e.ord = curstep;//栈元素的序号为当前足迹
			e.seat = curpos;//栈元素的位置为当前位置
			e.di = 0;//从当前位置出发，下一位置向东
			Push(S, e);
			curstep++;//足迹加1
			if (curpos.x == end.x&&curpos.y == end.y)//到达出口
				return TRUE;
			NextPos(curpos, e.di);//由当前位置及移动方向，确定下一个当前位置，赋给curpos		
		}
		else//当前位置不能通过
		{
			if (!StackEmpty(S))
			{
				Pop(S, e);//退栈道前一位置
				curstep--;
				while (e.di == 3 && !StackEmpty(S))//当前位置处于最后一个方向且不空
				{
					MarkPrint(e.seat);				//在前一位置留下由其不能到达终点的标记			
					Pop(S, e);						//在退回一部
					curstep--;
				}
				if (e.di < 3)//未到最后一个方向
				{
					e.di++;       //换下一个方向探索
					Push(S, e);    //入栈该位置下一个方向
					curstep++;
					curpos = e.seat;    //确定当前位置
					NextPos(curpos, e.di);     //由当前位置及移动方向，确定下一个当前位置，赋给curpos		
				}
			}
		}
	} while (!StackEmpty(S));
	return FALSE;
}

void main(int argc, char* argv[])
{
	Init();
	if (MazePath(begin, end))
	{
		printf("此迷宫从入口到出口的一条路径为：\n");
		Print();//输出此通路m数组
	}
	else
		printf("没有从入口到出口的路径：\n");
}

