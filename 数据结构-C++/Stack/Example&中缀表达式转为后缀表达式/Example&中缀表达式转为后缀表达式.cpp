// 中缀表达式转为后缀表达式.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include<ctype.h>//含有int isdigit(int c)函数的原型
#include "Translate.h"

void main()
{
	printf("运行结果:\n");
	printf("输入中缀表达式:");
	char p1[40], p2[40];
	gets_s(p1);
	zhuanhuan(p1, p2);
	printf("\n输出后缀表达式:");
	printf("%s", p2); 
	cin.get();
}




