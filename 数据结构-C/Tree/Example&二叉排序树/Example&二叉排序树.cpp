#include"BinarySortTree.h"
void main()
{
	BiTree dt, p;
	int i, n;
	KeyType j;
	ElemType r;
	Status k;
	FILE *f;

	f = fopen("T.txt", "r");
	fscanf(f, "%d", &n);
	InitDSTable(dt);//构造空二叉排序树
	for (i = 0; i < n; i++)//I依次在二叉排序树dt中插入n个数据元素
	{
		InputFromFile(f, r);
		k = InsertBST(dt, r);
		if (!k)
			printf("二叉排序树dt中已经存在关键字为%d的数据，故(%d,%d)无法插入到dt中\n", r.key, r.key, r.others);
	}
	fclose(f);
	printf("中序遍历二叉排序树dt:\n");//确定dt是否排序
	TraverseDSTable(dt, Visit);
	printf("\n");

	printf("先序遍历二叉树:\n");//确定dt的形态
	PostOrderTraverse(dt, Visit);
	printf("\n");

	printf("请输入待查找的关键字的值:");
	InputKey(j);
	p = SearchBST(dt, j);
	/*通过中序和先序（中序和后序）遍历二叉排序树，就可以确定二叉排序树的形态*/
	if (p)
	{
		printf("dt中存在关键字为 %d 的结点", j);
		DeleteBST(dt, j);
		printf("删除此结点后，中序遍历二叉树dt:\n");
		TraverseDSTable(dt, Visit);
		printf("\n");

		printf("先序遍历二叉树:\n");
		PostOrderTraverse(dt, Visit);
		printf("\n");
	}
	else
		printf("dt中不存在关键字为%d的结点\n", j);
	DestroyDSTable(dt);
}