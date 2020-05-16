#include"SqList.h"
void print1(ElemType c)
{
	printf("%4d", c);
}
void main()
{
	SqList La, Lb, Lc;
	int j;
	InitList(La);
	for (j = 1; j <= 5; j++)
		ListInsert(La, j, j);
	printf("La=: \n");
	ListTraverse(La, print1);

	InitList(Lb);
	for (j = 1; j <= 5; j++)
		ListInsert(Lb, j, 2*j);
	printf("Lb=: \n");
	ListTraverse(Lb, print1);

	MergeList(La, Lb, Lc);
	printf("Lc= :\n");
	ListTraverse(Lc, print1);
	printf("\n");
}