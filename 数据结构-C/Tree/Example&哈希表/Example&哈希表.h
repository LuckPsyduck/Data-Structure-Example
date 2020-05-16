#pragma once

#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
int m;
typedef int KeyType;
typedef int Status;

#define EQ(a,b)((a)==(b))
#define LT(a,b)((a)<(b))
#define LQ(a,b)((a)<=(b))

struct ElemType
{
	KeyType key;
	int order;
};

int hashsize[] = { 11,19,29,37 };
struct HashTable
{
	ElemType *elem;//动态分配数组
	int count;//当前元素个数
	int sizeindex;//hashsize[]的容量
};
#define SUCCESS 1
#define UNSUCCESS 0
#define DUPLICATE -1
#define NULL_KEY 0
#define OK 1
#define ERROR 0
void InitHashTable(HashTable &H)
{
	int i;
	H.count = 0;
	H.sizeindex = 0;
	m = hashsize[0];//哈希表的表长
	H.elem = (ElemType *)malloc(m * sizeof(ElemType));
	if (!H.elem)
		exit(EXIT_FAILURE);
	for (i = 0; i < m; i++)
		H.elem[i].key = NULL_KEY;//未填记录的标志
}

void DestroyHashTable(HashTable &H)
{
	free(H.elem);
	H.elem = NULL;
	H.count = 0;
	H.sizeindex = 0;
}

unsigned Hash(KeyType K)//哈希函数
{
	return K % m;
}

int d(int i)//增量序列函数
{
	return i;//线性探测再散列
	/*return ((i + 1) / 2)*((i + 1) / 2)*(int)pow(-1, i - 1);
	return rand();*/
}

void collision(KeyType K, int &p, int i)//开放定址法处理函数
{
	p = (Hash(K) + d(i)) % m;
}

Status SearchHash(HashTable H, int K, int &p, int &c)
{
	p = Hash(K);//p指示插入位置
	while (H.elem[p].key!=NULL&&!EQ(K,H.elem[p].key))
	{
		c++;//记录冲突次数
		if (c < m)//在H中有可能找到插入地址，修改
			collision(K, p, c);//求得下一探查地址p
		else
			break;
	}
	if EQ(K, H.elem[p].key)
		return SUCCESS;
	else
		return UNSUCCESS;
}

void RecreateHashTable(HashTable &);
//查找不成功时插入数据元素e到开放定址哈希表H中，
//诺冲突次数过大，则重建哈希 表
Status InsertHash(HashTable &H, ElemType e)
{
	int p, c = 0;
	if (SearchHash(H, e.key, p, c))
		return DUPLICATE;
	else if (c < hashsize[H.sizeindex] / 2)//未找到，冲突次数也c未达到上限
	{
		H.elem[p] = e;
		++H.count;
		return OK;
	}
	else//未找到，但冲突次数c已达到上限
	{
		RecreateHashTable(H);
		return UNSUCCESS;
	}
}

void RecreateHashTable(HashTable &H)
{
	int i, count = H.count;
	ElemType *p, *elem = (ElemType *)malloc(count * sizeof(ElemType));
	p = elem;
	for (int i = 0; i < m; i++)
		if ((H.elem + i)->key != NULL_KEY)
			*p++ = *(H.elem + i);
	H.count = 0;
	H.sizeindex++;//增大存储容量为下一个序列数
	m = hashsize[H.sizeindex];
	H.elem = (ElemType *)realloc(H.elem, m * sizeof(ElemType));
	for (i = 0; i < m; i++)
		H.elem[i].key = NULL_KEY;
	for (p = elem; p < elem + count; p++)//将原有的数据按照新的表长插入到重建的哈希表中
		InsertHash(H, *p);
	free(elem);
}

void TraverseHash(HashTable H, void(*Visit)(int, ElemType))
{
	int i;
	printf("哈希地址0-%d\n", m - 1);
	for (i = 0; i < m; i++)
		if (H.elem[i].key != NULL_KEY)
			Visit(i, H.elem[i]);
}