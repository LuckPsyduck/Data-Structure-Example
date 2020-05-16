/*1 2 3 3 7               9 8 8 7 5*/
#include"SqList.h"

void print(ElemType c)
{
	printf("%4d", c);
}

void main()
{
	int n = 5;
	LinkList La, Lb, Lc;

	printf("按非递减顺序:\n");
	CreateList1(La, n);
	printf("La= \n");
	ListTraverse(La, print);

	printf("按非递增顺序:\n");
	CreateList(Lb, n);
	printf("Lb= \n");
	ListTraverse(Lb, print);

	MergeList(La, Lb, Lc);
	printf("Lc= \n");
	ListTraverse(Lc, print);
}