//对外存文件(磁盘文件)进行排序的算法
#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<iomanip>
#include<time.h>
using namespace std;

typedef struct
{
	int key;
	int stn;
}ElemType;

int b = sizeof(ElemType);

//类定义
class LoadFile
{
public:
	//构造函数
	//向物理文件名为fname指针所指文件中输出n个记录
	LoadFile(char* fname, int n);

	//采用选择排序法对文件A的记录进行排序
	void FMergeSort(fstream &A, ElemType(&a)[10], int n);

	//顺序打印ff文件中每个记录
	void Print(fstream &ff);
};

//类的实现
//向物理文件名为fname指针所指文件中输出n个记录
LoadFile::LoadFile(char* fname, int n)
{
	fstream f(fname, ios::out | ios::binary | ios::trunc);

	//用所给的物理文件名定义一个输出文件流对象f，
	//它是与物理文件相对应的逻辑文件
	if (!f)
	{
		cerr << fname << ' ' << "not found!" << endl;
		exit(1);
	}

	for (int i = 0; i<n; i++)//假定向每个记录的排序码域输入数据,其值由随机产生
	{
		ElemType x;
		x.key = i; 
		x.stn = rand() % 200;
		f.write((char *)&x, b);
	}
	f.close();
}

//关闭逻辑文件f
 //采用选择排序法对文件A的记录进行排序
void LoadFile::FMergeSort(fstream &A, ElemType(&a)[10], int n)
{
	int i, j, k;
	A.seekg(0, ios::end);//将文件指针移至文件未
	A.seekg(0);//将文件指针移至文件首
	for (i = 0; i<n; i++)
		A.read((char*)&a[i], b);//从文件中读一记录到a[i]中
	for (i = 0; i<n - 1; i++)
	{
		k = i;
		for (j = i + 1; j<n; j++)
			if (a[k].stn>a[j].stn) 
				k = j;
		if (k != i)
		{
			int t;
			t = a[k].stn;
			a[k].stn = a[i].stn;
			a[i].stn = t;
			t = a[k].key; 
			a[k].key = a[i].key; 
			a[i].key = t;
		}
	}
	A.seekg(0);
	for (i = 0; i<10; i++)
		A.write((char *)&a[i], b);
}

//顺序打印ff文件中每个记录
void LoadFile::Print(fstream &ff)
{
	ElemType x;
	ff.seekg(0, ios::end);//将文件指针移至文件未
	int n = ff.tellg() / b;  //用n表示文件所含的记录数
	ff.seekg(0);  //将文件指针移至文件首
	for (int i = 0; i<n; i++) 
	{
		ff.read((char*)&x, b);//从文件中读一记录到x中
		cout << setw(4) << x.stn;
	}
	cout << endl;
}

