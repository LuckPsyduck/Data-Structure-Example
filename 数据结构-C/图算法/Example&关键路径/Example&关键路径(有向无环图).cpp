// 关键路径(有向无环图).cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"关键路径.h"

int main()
{
	ALGraph h;
	printf("请选择有向图\n");
	CreateGraph(h);
	Display(h);
	CriticalPath(h);
    return 0;
}

