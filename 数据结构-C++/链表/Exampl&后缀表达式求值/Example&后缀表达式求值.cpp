// 后缀表达式求值.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"Evaluate.h"

void main()
{
	char p[40];
	float y;
	printf("Evaluatem.cpp运行结果:\n");
	printf("输入后缀表达式:");
	gets_s(p);
	y = Evaluate(p);
	printf("后缀表达式的值:");
	printf("%5.0f\n", y); 
	cin.get();
}




