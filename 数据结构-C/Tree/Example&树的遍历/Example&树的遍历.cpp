//假设输入字符为：ABC##DE#G##F###，实际输入时，#用空格代替。
#include"Tree.h"
//遍历数据元素时所调用函数
Status PrintElement(TElemType e)
{
	putchar(e);
	return OK;
}

int main()
{
	BiTree T;
	puts("请按先序输入二叉树:");
	CreatBiTree(&T);
	//先序
	puts("先序递归:");
	PreOrderTraverse_Recursive(T, PrintElement); putchar('\n');
	puts("先序非递归:");
	PreOrderTraverse_NonRecursive(T, PrintElement); putchar('\n');
	//中序
	puts("中序递归:");
	InOrderTraverse_Recursive(T, PrintElement); putchar('\n');
	puts("中序非递归:");
	InOrderTraverse_NonRecursive(T, PrintElement); putchar('\n');
	InOrderTraverse_NonRecursive_2(T, PrintElement); putchar('\n');
	//后序
	puts("后序递归:");
	PostOrderTraverse_Recursive(T, PrintElement); putchar('\n');
	puts("后序非递归:");
	PostOrderTraverse_NonRecursive(T, PrintElement); putchar('\n');
	return 0;
}
