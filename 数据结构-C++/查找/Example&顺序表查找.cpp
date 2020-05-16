// 顺序表查找.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<iomanip>
#include<fstream>
#include<stdlib.h>
#include<time.h>
using namespace std;

//典型的关键字类型说明：
typedef int KeyType;//整型
					//对数值型关键字
#define EQ(a,b) ((a)==(b))
#define LT(a,b) ((a)<(b))
#define LQ(a,b) ((a)<=(b))

//线性表在顺序存储结构下的顺序查找				
typedef  struct
{
	int key;
	float info;
}STable;

//顺序查找的算法：
int Search_seq(STable ST[], int n, int key)
{
	int i = n;
	ST[0].key = key;//待查找的放在0号位置
	while (ST[i].key != key) 
		i--;//从表尾往前查
	return i;
}

//线性表在链式存储结构下的顺序查找
struct node
{
	int data;
	struct node *next;
};

int searlb(struct node *h, int x)
{
	struct node *m;
	m = h;
	while (m->next != NULL&&m->data != x) 
		m = m->next;
	return(m->data);
}

//静态查找表的顺序存储结构下的顺序查找
typedef struct {
	KeyType key;//学号
	int maths;//数学成绩
	int english;//英语成绩
}ElemType;

typedef struct 
{
	ElemType *elem;
	int length;//学生人数
}SSTable;

int Search_Seq(SSTable ST, KeyType key)
{
	int i;
	ST.elem[0].key = key;
	for (i = ST.length; !EQ(ST.elem[i].key, key); --i);//下标
	return i;
}

//静态查找表的顺序存储结构下的折半查找
int Search_Bin(SSTable ST, KeyType key)
{
	int low, mid, high;
	low = 0; high = ST.length;
	while (low <= high) 
	{
		mid = (low + high) / 2;
		if EQ(key, ST.elem[mid].key)
			return mid;
		else if LT(key, ST.elem[mid].key)
			high = mid - 1;
		else 
			low = mid + 1;
	}
	return 0;
}

void getdata(SSTable * t)
{
	char *fp = ".\\stu.dat";
	int i = 0;
	fstream ff(fp, ios::in | ios::trunc);
	ff.read((char *)&(t->length), 4);//元素的大小
	while (i<t->length)
	{
		ff.read((char *)&(t->elem[i].key), 4);
		ff.read((char *)&(t->elem[i].maths), 4);
		ff.read((char *)&(t->elem[i].english), 4);
		i++;
	}
	ff.close();
}

void main()
{
	int i=0;
	ElemType stu[50];
	SSTable  clas;
	clas.length = 10;
	char *fp = ".\\stu.dat";
	srand(time(0));
	fstream fa(fp, ios::out | ios::trunc);
	fa.write((char *)&(clas.length), 4);
	for (i = 0; i<10; i++)
	{
		stu[i].key = 1000 + i;
		stu[i].maths = rand() % 100;
		stu[i].english = rand() % 100;
		fa.write((char *)&(stu[i]), 12);//取地址，在强制类型转换
	}
	fa.close();
	int j, k;
	clas.elem = stu;
	getdata(&clas);
	cout << "该班学生数:" << clas.length;
	cout << "\n输入要查找的学号:"; 
	cin >> k;
	i = Search_Seq(clas, k);
	j = Search_Bin(clas, k);

	cout << "\n学号 数学  英语\n";
	cout << clas.elem[i].key << setw(4)
		<< clas.elem[i].maths << setw(6) << clas.elem[i].english << endl;
	cout << clas.elem[j].key << setw(4)
		<< clas.elem[j].maths << setw(6) << clas.elem[j].english << endl;

	cout << "学号   总分\n";
	for (i = 0; i<10; i++)
	{
		j = stu[i].maths + stu[i].english;
		cout << 1000 + i << setw(6) << j << endl;
	}
}


