#include"Stack.h"
void print(SElemType c)
{
	printf("%d ", c);
}

void main()
{
	int j;
	SqStack s;

	SElemType e;
	InitStack(s);

	for (j = 1; j <= 12; j++)
		Push(s, j);
	printf("栈中元素依次为:");
	StackTraverse(s, print);

	Pop(s, e);
	printf("弹出的栈顶元素e=%d\n", e);

	printf("栈空否?%d(1 空 0 否),", StackLength(s));
	GetTop(s, e);
	printf("栈顶元素e=%d,栈的长度为%d\n", e, StackLength(s));

	ClearStack(s);
	printf("清空栈后，栈是否为空？%d(1 空 0 否)\n", StackEmpty(s));
	DestroyStack(s);
	printf("销毁栈后,s.top=%p,s.base=%p,s.stacksize=%d\n", s.top, s.base, s.stacksize);
}