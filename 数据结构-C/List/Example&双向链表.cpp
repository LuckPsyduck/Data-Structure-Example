#include"SqList.h"

void print(ElemType c)
{
	printf("%d ", c);
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
	DuLinkList L;
	int i, n = 4;
	Status j;
	ElemType e;
	InitList(L);

	for (i = 1; i <= 5; i++)
		ListInsert(L, i, i);

	printf("逆序输出链表: ");
	ListTraverseBack(L, print);

	j = GetElem(L, 2, e);
	if (j)
		printf("链表的第二个元素值为%d\n", e);
	else
		printf("不存在第二个元素\n");

	i = LocateElem(L, n, equal);

	if (i)
		printf("等于%d的元素是第%d个\n", n, i);
	else
		printf("没有等于%d的元素\n", n);

	j = PriorElem(L, n, e);
	if (j)
		printf("%d的前驱是%d", n, e);
	else
		printf("不存在%d的前驱\n", n);

	j = NextElem(L, n, e);
	if (j)
		printf("%d的后继是%d\n", n, e);
	else
		printf("不存在%d的后继\n", n);

	ListDelete(L, 2, e);
	printf("删除第2个结点，值为%d,其余结点为 ", e);
	ListTraverse(L, print);

	printf("链表的元素个数为%d,", ListLength(L));
	printf("链表是否为空？%d(1是，0否)\n", ListEmpty(L));
	ClearList(L);
	printf("清空后，链表是否空？%d（1 空，0 否）\n", ListEmpty(L));
	DestroyList(L);
}