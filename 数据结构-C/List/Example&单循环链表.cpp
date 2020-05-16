#include"SqList.h"
void print(ElemType c)
{
	printf("%4d", c);
}
Status equal(ElemType c1, ElemType c2)
{
	if (c1 == c2)
		return true;
	else
		return false;
}
void main()
{
	LinkList L;
	ElemType e, e0;
	Status i;
	int j, k;
	InitList(L);//初始化

	for (j = 1; j <= 5; j++)
		i = ListInsert(L, 1, j);

	printf("在L的表头依次插入1-5后，L=：\n");
	ListTraverse(L, print);
	i = ListEmpty(L);
	printf("i=%d(0 空，1 非空),表的长度=%d\n", i, ListLength(L));
	ClearList(L);
	printf("清空后，L=：\n");
	ListTraverse(L, print);

	i = ListEmpty(L);
	printf("i=%d(0 空，1 非空),表的长度=%d\n", i, ListLength(L));

	for (j = 1; j <= 10; j++)
		ListInsert(L, j, j);
	printf("在L的表尾依次插入1-10后，L=：\n");
	ListTraverse(L, print);

	for (j = 0; j <= 1; j++)
	{
#ifdef  SLL//仅用于静态链表
		k = LocateElem(L, j);
		if (k)
			printf("值为%d的元素的位序为%d\n", j, k);
#else//仅用于链表
		k = LocateElem(L, j, equal);//返回与第j 个元素相等的位置
		if (k)
			printf("第%d个元素的值为%d\n", j, k);
#endif //  SLL
		else
			printf("没有值为%d的元素", j);
	}

	for (j = 1; j <= 2; j++)
	{
		GetElem(L, j, e0);//第j个元素给e0

		i = PriorElem(L, e0, e);//返回前驱
		if (i == ERROR)
			printf("元素%d无前驱，", e0);
		else
			printf("元素%d的前驱为%d\n", e0, e);
	}

	for (j = ListLength(L) - 1; j <= ListLength(L); j++)
	{
		GetElem(L, j, e0);
		i = NextElem(L, e0, e);
		if (i == ERROR)
			printf("元素%d无后继\n", e0);
		else
			printf("元素%d的后继为%d\n", e0, e);
	}

	k = ListLength(L);
	for (j = k + 1; j >= k; j--)
	{
		i = ListDelete(L, j, e);
		if (i == ERROR)
			printf("删除第%d个元素失败\n", j);
		else
			printf("删除第%d个元素成功，其值为%d\n", j, e);
	}

	printf("依次输出L的元素: ");
	ListTraverse(L, print);
	DestroyList(L);
#ifdef  SLL
	printf("销毁L后，L=%p\n", L);
#endif //  SLL
}