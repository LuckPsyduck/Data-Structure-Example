// 哈希表.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <math.h>
#include <stdlib.h>
#include<time.h>
using namespace std;

//user data stored in hash table
typedef struct
{
	int stuff;                  //optional related data
}recType;

typedef int hashIndexType;   //index into hash table

#define compEQ(a,b) (a == b)
							 //implementation independent declarations
typedef enum 
{
	STATUS_OK,
	STATUS_MEM_EXHAUSTED,
	STATUS_KEY_NOT_FOUND
}statusEnum;

typedef struct nodeTag 
{
	struct nodeTag *next;   // next node
	int key;                // key
	recType rec;            // user data
}nodeType;

nodeType **hashTable;
int hashTableSize;
//哈希表的插入
statusEnum insert(int key, recType *rec)
{
	nodeType *p, *p0;
	hashIndexType bucket;
	//insert node at beginning of list
	bucket = key % hashTableSize;
	if ((p = new nodeType) == 0)
		return STATUS_MEM_EXHAUSTED;

	p0 = hashTable[bucket];//数组装的是这个桶的元素数组(里面是bucket的数组，为结构体指针)
	hashTable[bucket] = p;
	p->next = p0;//替代原来的值，原值向右移
	p->key = key;
	p->rec = *rec;
	return STATUS_OK;
}

//哈希表的删除
statusEnum Delete(int key) 
{
	nodeType *p0, *p;
	hashIndexType bucket;//int 
	p0 = 0;//find node
	bucket = key % hashTableSize;
	p = hashTable[bucket];
	while (p && !compEQ(p->key, key))
	{
		p0 = p;//相当于前驱
		p = p->next;
	}
	if (!p) 
		return STATUS_KEY_NOT_FOUND;
	//p designates node to delete,remove it from list
	if (p0)
		//not first node,p0 points to previous node
		p0->next = p->next;//桶中之前有值，直接用后序覆盖
	else
		//first node on chain
		hashTable[bucket] = p->next;//将元素装入桶中，为第一个元素
	free(p);
	return STATUS_OK;
}

//哈希表的查找
statusEnum find(int key, recType *rec)
{
	nodeType *p;
	p = hashTable[key%hashTableSize];
	while (p && !compEQ(p->key, key))
		p = p->next;
	*rec = p->rec;
	return STATUS_OK;
}

//哈希表的相关操作的测试
void main()
{
	cout << "hashtable.cpp运行结果:\n";
	int i, maxnum, k = 0;
	recType *rec;
	int *key;
	statusEnum err;
	maxnum = 10;
	hashTableSize = 10;
	srand(time(0));
	if ((rec = new recType[maxnum * sizeof(recType)]) == 0)
	{
		fprintf(stderr, "out of memory (rec)\n"); 
		exit(1);
	}
	if ((key = new int[maxnum * sizeof(int)]) == 0)
	{
		fprintf(stderr, "out of memory (key)\n"); 
		exit(1);
	}
	if ((hashTable = new nodeType *[hashTableSize * sizeof(nodeType)]) == 0)
	{
		fprintf(stderr, "out of memory (hashTable)\n");
		exit(1);
	}
	if (rand())//fill "key" with unique rand numbers
	{
		for (i = 0; i<maxnum; i++) 
			key[i] = rand() % 100;
		cout << " ran ht," << maxnum << " items," << hashTableSize << " hashTable\n";
	}
	else 
	{
		for (i = 0; i<maxnum; i++)
			key[i] = i;
		cout << " seq ht," << maxnum << " items," << hashTableSize << " hashTable\n";
	}
	cout << "插入结果\n";
	for (i = 0, k = 1; i < maxnum; i++, k++)
	{
		err = insert(key[i], &rec[i]);
		if (!err)//插入成功
			cout << " key[" << setw(2) << i << "]=" << setw(3) << key[i];
		if (k % 5 == 0)
			cout << endl;
	}

	cout << endl << "查找结果\n";
	for (k = 1, i = maxnum - 1; i >= 0; i--, k++) 
	{
		err = find(key[i], &rec[i]);
		if (!err)//查找成功
			cout << " key[" << setw(2) << i << "]=" << setw(3) << key[i];
		if (k % 5 == 0) cout << endl;
	}

	cout << endl << "删除结果\n";
	for (k = 1, i = maxnum - 1; i >= 0; i--, k++) 
	{
		err = Delete(key[i]);
		if (!err)//删除成功
			cout << " key[" << setw(2) << i << "]=" << setw(3) << key[i];
		if (k % 5 == 0)
			cout << endl;
	}
}

