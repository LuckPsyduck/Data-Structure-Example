#include"headfile.h"

//初始化栈
Status InitStack(Stack *s)
{
	s->base = (BiTree*)malloc(sizeof(BiTree)*STACK_INIT_SIZE);
	s->top = s->base;
	s->stacksize = STACK_INIT_SIZE;
	return OK;
}

//判断栈是否为空
Status StackEmpty(Stack *s)
{
	if (s->base == s->top)
		return OK;
	return ERROR;
}

//获得栈顶元素
Status GetTop(Stack *s, BiTree *c)
{
	if (StackEmpty(s))
		return ERROR;
	*c = *(s->top - 1);
	return OK;
}

//进栈
Status Push(Stack *s, BiTree c)
{
	//如果空间不够，增加空间的分配
	if (s->top - s->base >= s->stacksize)
	{
		s->base = (BiTree*)realloc(s->base, sizeof(BiTree)*(s->stacksize + STACKINCREMENT));
		s->stacksize = s->stacksize + STACKINCREMENT;
	}
	*(s->top++) = c;
	return OK;
}

//出栈
Status Pop(Stack *s, BiTree *c)
{
	if (StackEmpty(s))
		return ERROR;
	*c = *(--s->top);
	return OK;
}
