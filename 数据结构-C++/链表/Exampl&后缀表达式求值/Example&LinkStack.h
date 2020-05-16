#pragma once
#include<iostream>
#include<iomanip>
#include<stdlib.h>
#include<strstream>

typedef float ElemType;

const int LEN = 40;
typedef struct Stack {
	ElemType data;
	struct Stack *next;
}StackNode;//结点数据类型


class CLinkStack
{
public:
	CLinkStack();
	~CLinkStack() {};
private:
	StackNode *top;//指向栈顶的指针
	int size;// 堆栈的结点个数
public:

	//初始化栈,分配存储空间并置空
	void InitStack(int);

	//创建有序或无序栈
	void CreateStack(int, int m = LEN, int mark = 0);

	//返回堆栈的结点个数
	int StackSize();

	//清空栈
	void ClearStack();

	//删除栈
	void DeleteStack();

	//检查栈是否为空
	bool StackEmpty();

	//读取栈顶元素
	ElemType Peek();

	//向栈中插入元素
	void Push(const ElemType&);

	//从栈中删除元素
	ElemType Pop();

	//检查栈是否已满
	bool StackFull(ElemType m = LEN);

	//栈的输出
	void StackPrint(ElemType m = LEN);
};

