// 二路平衡归并(磁盘文件).cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"Sort.h"

void main()
{
	int n, i;
	char *fa = ".\\fa1.dat";
	srand(time(0));
	fstream fna(fa, ios::in | ios::out | ios::binary);
	cout << "输入表长n:"; 
	cin >> n;
	cout << "文件未排序前的结果:\n";
	LoadFile myfile(fa, n);
	myfile.Print(fna);
	if (n % 2 == 0)
	{
		myfile.FMergeSort(fna, 2);
		for (i = 2; i <= n / 2; i++)
		{
			myfile.FMergeSort(fna, 2 * i - 1);
			myfile.FMergeSort(fna, 2 * i);
		}
		myfile.FMergeSort(fna, n / 2);
	}
	else
	{
		myfile.FMergeSort(fna, 2);
		for (i = 2; i <= n / 2; i++)
		{
			myfile.FMergeSort(fna, 2 * i - 1);
			myfile.FMergeSort(fna, 2 * i);
		}
		myfile.FMergeSort(fna, n / 2 + 1);
	}
	cout << "文件排序后的结果:\n";
	myfile.Print(fna); 
	fna.close();
}

