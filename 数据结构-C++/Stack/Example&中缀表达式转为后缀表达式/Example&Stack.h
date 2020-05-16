#pragma once
#include<iostream>
#include<iomanip>

using namespace std;

typedef char ElemType;//根据输入的数据不同，定义发生变化

const int LEN = 40;
class CStack
{
private:
	ElemType stack[LEN];
	int top;
public:
	//构造函数
	CStack() { top = 0; }

	//析构函数
	~CStack() {}

	//创建有序或无序栈
	void CreateStack(int, int m = LEN, int mark = 0);

	//清空栈
	void ClearStack();

	//检查栈是否为空
	bool StackEmpty();

	//读取栈顶元素
	ElemType Peek();

	//向栈中插入元素
	void Push(const ElemType&, int m = LEN);

	//从栈中删除元素
	ElemType Pop();

	//检查栈是否已满
	bool StackFull(int m = LEN);

	//栈的输出
	void StackPrint(int m = LEN);
};

