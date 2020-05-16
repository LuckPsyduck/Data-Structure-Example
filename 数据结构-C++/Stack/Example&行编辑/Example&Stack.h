#pragma once
#include<iostream>
#include<iomanip>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
using namespace std;


typedef char Status;
typedef char SElemType;

//typedef char Status;
//typedef char SElemType;

#define ERROR 0
#define EQUAL 1

#define STACKSIZE 100
#define STACKINCREMENT 10

class CStack
{
public:
	CStack() {};
	~CStack() {};
private:
	SElemType *base;
	SElemType *top;
	int stacksize; 

public:
	//构造一个空栈S
	Status InitStack(CStack  **S);

	//栈存在则栈被销毁
	Status DestroyStack();

	//栈存在则清为空栈
	Status ClearStack();

	//栈存在则返回true,否则false
	bool StackEmpty();

	// 栈存在则返回栈的元素个数,即栈的长度
	int StackLength();

	//栈存在且非空则返回栈的栈顶元素
	SElemType GetTop();

	// 栈存在则插入元素e为新的栈顶元素
	Status Push(SElemType e);

	// 栈存在且非空则删除栈的栈顶元素并用e返回其值
	SElemType Pop(SElemType *e);

	// 栈的遍历
	void StackTraverse(void(*visit)(SElemType *));
};

