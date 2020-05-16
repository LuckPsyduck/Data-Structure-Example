#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef int Status;
#define OK 1
#define ERROR 0
#define OVERFLOW -2

//二叉树的二叉链表存储表示

typedef char TElemType;

typedef struct BiNode
{
	TElemType data;
	struct BiNode *lchild, *rchild;
} BiNode, *BiTree;


//栈的顺序存储结构
#define STACK_INIT_SIZE 100      //存储空间初始分配量
#define STACKINCREMENT 10       //存储空间分配增量

typedef struct
{
	BiTree *base;
	BiTree *top;
	int stacksize;
} Stack;
