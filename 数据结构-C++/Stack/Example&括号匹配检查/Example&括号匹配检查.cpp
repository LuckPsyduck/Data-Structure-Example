// 括号匹配检查.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include "Stack.h"

void main()
{
	CStack *p;
	int n, m , q = 0;
	char ch, ca, cd;
	cout << "运行结果:\n";
	cout << "输入括号的个数m: ";
	cin >> m;
	cout << "输入括号字符序列:";
	p->InitStack(&p);
	for (n = 1; n<m; n++)
	{
		cin >> ch;
		if (ch == '[') 
			p->Push(ch);

		if (ch == '(')
			p->Push(ch);

		if (ch == '{')
			p->Push(ch);

		if (ch == ']')
		{
			ca = p->Pop(&cd);
			if (ca == '[') 
				cout << ca << "与" << ch << "是匹配的!\n";
			else
			{
				cout << ca << "与" << ch << "不是匹配的!\n"; 
				q++;
			}
		}
		if (ch == ')')
		{
			ca = p->Pop(&cd);
			if (ca == '(') 
				cout << ca << "与" << ch << "是匹配的!\n";
			else
			{
				cout << ca << "与" << ch << "不是匹配的!\n";
				q++;
			}
		}
		if (ch == '}')
		{
			ca = p->Pop(&cd);
			if (ca == '{') 
				cout << ca << "与" << ch << "是匹配的!\n";
			else
			{
				cout << ca << "与" << ch << "不是匹配的!\n";
				q++;
			}
		}
		if (p->StackEmpty()) 
			break;
	}
	if (q >= 1) 
		cout << "刮号序列不匹配!\n";
	else 
		cout << "刮号序列匹配!\n";
	cin.get(); 
	cin.get();
}










