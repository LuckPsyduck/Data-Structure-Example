#include"hash.h"
#define N 15
void Visit(int p, ElemType r)
{
	printf("address=%d(%d,%d)\n", p, r.key, r.order);
}
void main()
{
	ElemType r[N];
	HashTable h;
	int i, n, p = 0;
	Status j;
	KeyType k;
	FILE *f;
	f = fopen("T.txt", "r");
	do
	{
		i = fscanf(f, "%d %d", &r[p].key, &r[p].order);
		if (i != -1)
			p++;
	} while (!feof(f) && p < N);
	fclose(f);
	InitHashTable(h);
	for (i = 0; i < p - 1; i++)
	{
		j = InsertHash(h, r[i]);
		if (j == DUPLICATE)
			printf("表中已有关键字为%d的记录，无法再插入记录(%d,%d)\n",r[i].key,r[i].key,r[i].order);
	}
	printf("按哈希表地址的顺序遍历哈希表:\n");
	TraverseHash(h, Visit);
	printf("请输入待查找的关键字:");
	scanf("%d", &k);
	j = SearchHash(h, k, p, n);
	if (j == SUCCESS)
		Visit(p, h.elem[p]);
	else
		printf("未找到\n");
	j = InsertHash(h, r[i]);
	if (j == ERROR)
		j = InsertHash(h, r[i]);
	printf("按哈希表地址的顺序遍历重建后的哈希表:\n");
	TraverseHash(h, Visit);

	printf("输入待查找记录的关键字:\n");
	scanf("%d", &k);
	j = SearchHash(h, k, p, n);
	if (j == SUCCESS)
		Visit(p, h.elem[p]);
	else
		printf("未找到\n");
	DestroyHashTable(h);
}