// 选择排序(磁盘文件).cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"Sort.h"

void main()
{
	int m = 10;
	ElemType d[10];
	char *fa = ".\\fa1.dat";
	srand(time(0));
	fstream fna(fa, ios::out | ios::in | ios::binary | ios::trunc);
	cout << "文件未排序前的结果:\n";
	LoadFile myfile(fa, m);
	myfile.Print(fna);
	cout << "文件排序后的结果:\n";
	myfile.FMergeSort(fna, d, m);
	myfile.Print(fna);
	fna.close(); 
	cin.get();
}
