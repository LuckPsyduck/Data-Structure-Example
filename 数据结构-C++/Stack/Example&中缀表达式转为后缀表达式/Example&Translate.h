#pragma once
#include "Stack.h"
const int SM = 40;//数组的最大容量

int Precedence(char op);

//将字符串s1中的中缀表达式转换为存于字符串s2中的后缀表达式
void zhuanhuan(char s1[SM], char s2[SM])
{
	CStack R;        //定义用于暂存运算符的栈
	R.Push('@');    //给栈底放入'@'字符,它具有最低优先级0
	int i, j;
	i = 0;          //用于指示扫描s1串中字符的位置,初值为0
	j = 0;          //用于指示s2串中待存字符的位置,初值为0
	char ch = s1[i];//ch保存s1串中扫描到的字符,初值为第一个字符
	while (ch != '@')
	{					//顺序处理中缀表达式中的每个字符
		if (ch == ' ')//对于空格字符不做任何处理,顺序读取下一个字符	
			ch = s1[++i];
		else if (ch == '(')
		{
			R.Push(ch);//对于左括号,直接进栈
			ch = s1[++i];
		}
		else if (ch == ')')//对于右括号，使括号内的仍停留在栈中的运算符依				
		{								 //出栈并写入到s2中
			while (R.Peek() != '(')
				s2[j++] = R.Pop();
			R.Pop();  //删除栈顶的左括号
			ch = s1[++i];
		}
		else if (ch == '+' || ch == '-' || ch == '*' || ch == '/')//对于四则运算符，使暂存在栈中的
		{															//不低于ch优先级的运算符依次出栈并写入到s2中
			char w = R.Peek();
			while (Precedence(w) >= Precedence(ch))//Precedence(w)函数返回运算符形参的优先级
			{
				s2[j++] = w; 
				R.Pop();
				w = R.Peek();
			}
			R.Push(ch); //把ch运算符写入栈中
			ch = s1[++i];
		}
		else//此处必然为数字或小数点字符
		{
			while (isdigit(ch) || ch == '.')//把一个数值中的每一位依次写入到s2串中
			{
				s2[j++] = ch;
				ch = s1[++i];
			}
			s2[j++] = ' ';//被转换后的每个数值后放入一个空格
		}
	}
	//把暂存在栈中的运算符依次出栈并写入到s2串中
	ch = R.Pop();
	while (ch != '@') {
		if (ch == '(') {
			cerr << "expression error!" << endl;
			exit(1);
		}
		else {
			s2[j++] = ch;
			ch = R.Pop();
		}
	}
	//在后缀表达式的末尾放入表达式结束符和字符串结束符
	s2[j++] = '@';
	s2[j++] = '\0';
}

//求运算符优先级的Precedence函数为：
int Precedence(char op)//返回运算符op所对应的优先级数值
{
	switch (op)
	{
	case '+':
	case '-':return 1;//定义加减运算的优先级为1
	case '*':
	case '/':return 2;//定义乘除运算的优先级为2
	case '(':
	case '@':
		//定义在栈中的左括号和栈底字符的优先级为0
	default:return 0;
	}
}

