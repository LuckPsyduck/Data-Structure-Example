#pragma once
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

int b = sizeof(ElemType);//b表示ElemType记录类型的大小
						 //类定义
class LoadFile
{
public:
	//构造函数
	//向物理文件名为fname指针所指文件中输出n个记录
	LoadFile(char* fname, int n);

	//把文件A中两个相邻位置s?m和m+1?t的有序表归并为
	//文件R中对应位置s?t上的一个有序表
	void FTwoMerge(fstream &A, fstream &R, int s, int m, int t);

	//对文件A进行一趟二路归并的算法
	void FMergePass(fstream &A, fstream &R, int n, int len);

	//对磁盘文件进行二路归并排序的算法
	void FMergeSort(fstream &A, int BlockSize);

	//顺序打印ff文件中每个记录
	void Print(fstream &ff);
};

//类的实现
//向物理文件名为fname的指针所指文件中输出n个记录
LoadFile::LoadFile(char* fname, int n)
{
	ofstream f(fname, ios::out | ios::binary);
	//用所给的物理文件名定义一个输出文件
	//流对象f是与物理文件相对应的逻辑文件
	if (!f) 
	{
		cerr << fname << ' ' << "not found!" << endl; 
		exit(1);
	}
	for (int i = 0; i<n; i++)
	{//假定向每个记录的排序码域的数据由随机产生
		ElemType x;
		x.key = i; 
		x.stn = rand() % 100;
		f.write((char *)&x, b);//强制类型转换
	}
}

//把文件A中两个相邻位置s?m和m+1?t的有序表归并为
//文件R中对应位置s?t上的一个有序表
void LoadFile::FTwoMerge(fstream &A, fstream &R, int s, int m, int t)
{
	int i, j, k;
	ElemType a1, a2;
	i = s; j = m + 1; k = s;//分别给指示每个有序表元素位置的指针赋初值
	R.seekg(k*b);  //将文件R中的文件指针移到记录下标为k的位置,
				   //两个有序表中同时存在未归并元素时的处理过程
	while (i <= m && j <= t)
	{
		A.seekg(i*b);
		//从文件A的记录下标为s开始的归并段中读出一个记录到a1中
		A.read((char*)&a1, b);

		//从文件A的记录下标为m+1开始的归并段中读出一个记录到a2中
		A.seekg(j*b);
		A.read((char*)&a2, b);

		//将a1和a2中排序码较小的记录写入到R文件中
		if (a1.stn <= a2.stn) 
		{
			R.write((char*)&a1, b);
			i++;
		}
		else 
		{ 
			R.write((char*)&a2, b); 
			j++; 
		}
	}
	//对前一个归并段中存在的未归并元素进行处理
	A.seekg(i*b);
	while (i <= m) 
	{
		A.read((char*)&a1, b);
		R.write((char*)&a1, b);
		i++;
	}
	//对后一个有序表中存在的未归并元素进行处理 
	A.seekg(j*b);
	while (j <= t)
	{
		A.read((char*)&a2, b);
		R.write((char*)&a2, b);
		j++;
	}
}

//对文件A进行一趟二路归并的算法
void LoadFile::FMergePass(fstream &A, fstream &R, int n, int len)
//把文件A中每个长度为len的有序表两两归并到文件R中
{
	ElemType x;
	int p = 0;//p用于指向每一对归并段的首记录位置,初值为0
	while (p + 2 * len - 1 <= n - 1)
	{//两两归并长度均为len的有序表
		FTwoMerge(A, R, p, p + len - 1, p + 2 * len - 1);
		p += 2 * len;
	}
	if (p + len - 1<n - 1)//归并最后两个长度不等的有序表
		FTwoMerge(A, R, p, p + len - 1, n - 1);
	else 
	{ //把剩下的最后一个有序表复制到R中
		A.seekg(p*b);  //移动文件A中的指针到规定的位置
		R.seekg(p*b);  //移动文件R中的指针到对应位置
		for (int i = p; i <= n - 1; i++) 
		{
			A.read((char*)&x, b);
			R.write((char*)&x, b);
		}
	}
}

//对磁盘文件进行二路归并排序的算法
void LoadFile::FMergeSort(fstream &A, int BlockSize)
//采用归并排序的方法对文件A中的每个有序
//子表长度为BlockSize的记录进行排序
{
	char *ff = ".\\temp.dat";
	fstream R(ff, ios::in | ios::out | ios::binary | ios::trunc);
	//定义一个能够按块随机存取的辅助文件R
	if (!R) 
	{
		cerr << "temp.dat" << ' ' << "not open!" << endl; 
		exit(1);
	}
	int len = BlockSize;
	//从有序表长度为给定值BlockSize开始归并
	A.seekg(0, ios::end);
	//将文件A中的指针移到文件的末尾
	int n = A.tellg() / b;
	//用n表示文件中所含的记录个数,b为记录的大小
	while (len<n)
	{
		FMergePass(A, R, n, len);
		//从A归并到R中,得到每个有序表的长度为2*len
		len *= 2;
		//修改len的值为R中的每个有序表的长度
		FMergePass(R, A, n, len);
		//从R归并到A中,得到每个有序表的长度为2*len
		len *= 2;
	}
	//修改len的值为A中的每个有序表的长度
	R.close();//关闭辅助文件R
			  //从磁盘上删除R所对应的物理文件
	remove(ff);
}

//顺序打印出ff文件中每个记录
void LoadFile::Print(fstream &ff)
{
	ElemType x;
	ff.seekg(0, ios::end);//将文件指针移至文件未
	int n = ff.tellg() / b; //用n表示文件所含的记录数
	ff.seekg(0);  //将文件指针移至文件首
	for (int i = 0; i<n; i++)
	{
		ff.read((char*)&x, b);//从文件中读一记录到x中
		if (i % 10 == 0)//每行显示10个数据
			cout << endl;//每个数据占4个字符显示位置
		cout << setw(4) << x.stn;
	}
	cout << endl;
}


