#include "stdafx.h"
#include "Stack.h"


Status CStack::InitStack(CStack **S)
{
	(*S) = (CStack *)malloc(sizeof(CStack));
	(*S)->base = (SElemType *)malloc(STACKSIZE * sizeof(SElemType));
	if (!(*S)->base) 
		exit(OVERFLOW);
	(*S)->top = (*S)->base;
	(*S)->stacksize = 0;
	return 1;
}

Status CStack::DestroyStack()
{
	free(base); 
	return 1;
}

Status CStack::ClearStack()
{
	stacksize = 0; 
	return 1;
}

bool CStack::StackEmpty()
{
	if (stacksize == 0)
		return true;
	else 
		return false;
}

int CStack::StackLength()
{
	return stacksize;
}

SElemType CStack::GetTop()
{
	if (top == base)
	{
		cerr << "¿ÕÕ»!\n"; exit(1);
	}
	return *(top - 1);
}

Status CStack::Push(SElemType e)
{
	*(top++) = e;
	stacksize++;
	return 1;
}

SElemType CStack::Pop(SElemType *e)
{
	if (top == base)
	{
		cerr << "¿ÕÕ»!\n"; exit(1);
	}
	*e = *--top;
	stacksize--;
	return *e;
}

void CStack::StackTraverse(void(*visit)(SElemType *))
{
	while (top != base)
	{
		stacksize--; 
		visit(--top);
	}
}
