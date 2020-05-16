#pragma once

const int SM = 40;
#include "LinkStack.h"
using namespace std;

//计算由str字符串所表示的后缀表达式的值,表达式要以'@'字符结束.
float Evaluate(char* str)
{
	CLinkStack S;//创建对象S
	S.InitStack(SM);//初始化栈
	istrstream ins(str);//把str定义为输入字符串流对象ins
	char ch;            //用于输入字符
	float x;   //用于输入浮点数
	ins >> ch;   //从ins流对象(即str字符串)中顺序读入一个字符
	while (ch != '@')//扫描每一个字符并进行相应处理
	{
		switch (ch)
		{
		case '+':x = S.Pop() + S.Pop(); break;
		case '-':x = S.Pop();   // Pop(S)弹出减数
			x = S.Pop() - x; //Pop(S)弹出的是被减数
			break;
		case '*':x = S.Pop()*S.Pop(); break;
		case '/':x = S.Pop();   // Pop(S)弹出除数
			if (x != 0.0)
				x = S.Pop() / x;     //Pop(S)弹出的是被除数
			else                    //除数为0时终止运行
			{ 
				cerr << "除数为0!" << endl; 
				exit(1);
			}
			break;
		default://读入的必为一个浮点数的最高位数字
			ins.putback(ch); //把它重新回送到输入流中
			ins >> x;//放回原处
		} //从字符串输入流中读入一个浮点数
		  //把读入的一个浮点数或进行相应运算的结果压入到S栈中
		S.Push(x);//数字入栈
		ins >> ch; //输入下一个字符,以便进行下一轮循环处理
	}

	if (!S.StackEmpty())//若栈中仅有一个元素,则它是后缀表达式的值,否则为出错
	{
		x = S.Pop();
		if (S.StackEmpty()) 
			return x;
		else 
		{ 
			cerr << "表达式出错!" << endl;
			exit(1); 
		}
	}
	else 
	{//若最后栈为空,则终止运行
		cerr << "栈为空!" << endl;
		exit(1);
	}
	return x;
}

