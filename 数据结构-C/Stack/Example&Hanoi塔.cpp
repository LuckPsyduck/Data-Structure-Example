// 栈_Hanoi塔.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
int c = 0;
void move(char x, int n, char z)
{
	printf("第%i步，将%i号盘从%c移到%c\n", ++c, n, x, z);
}
//将塔座x上按直径有小到大且自上而下编号为1至n的n个盘
void hanoi(int n, char x, char y, char z)
{
	if (n == 1)
		move(x, 1, z);//将编号为1的圆盘从x移到z
	else
	{
		hanoi(n - 1, x, z, y);//将x上编号为1至n-1的圆盘移到y，z作为辅助塔
		move(x, n, z);//将编号为n的圆盘从x移到z
		hanoi(n - 1, y, x, z);//将y上编号为1至n-1的圆盘移到z,x作为辅助塔
	}
}
int main()
{
	int n;
	printf("3个塔座为a,b,c,圆盘最初在a座，借助b座移到c座，请输入圆盘数: ");
	scanf("%d", &n);
	hanoi(n, 'a', 'b', 'c');
    return 0;
}

