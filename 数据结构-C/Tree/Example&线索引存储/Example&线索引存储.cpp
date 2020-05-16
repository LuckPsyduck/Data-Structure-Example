#include"Tree3.h"
//#define CHAR 0
#define FLAG 1//是否进行后续遍历
void main()
{
	BiThrTree H, T;

	for (int i = 1; i < 3; i++)
	{
#if CHAR //CHAR 的值为非0，结点类型为字符
		printf("请按先序输入二叉树！\n");
#else 
		printf("请按先序输入二叉树！\n");
#endif
		CreateBiThrTree(T);
		scanf("%*c");
		/*	getchar();*/
		switch (i)
		{
		case 1:PreOrderThreading(H, T); printf("先序遍历线索二叉树:\n"); PreOrderTraverse_Thr(H, visit); break;
		case 2:InOrderThreading(H, T); printf("中序遍历线索二叉树:\n"); InOrderTraverse_Thr(H, visit); break;
		case 3:PostOrderThreading(H, T);
#if FLAG
			printf("后序遍历线索二叉树:\n");
			PostOrderTraverse_Thr(H, visit); break;
#endif
		default:break;
		}
		printf("\n");
		DestroyBiThrThree(H);
	}
}