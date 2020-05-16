// 散列表类定义及实现.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"HList.h"

using namespace std;

//散列表类的相关操作的测试
void main()
{
	//定义数组b并初始化
	ElemType a[16] = { 12,18,15,32,6,23,21,48,36,57,
		45,29,25,38,14,9 }, d;
	//元素个数
	int m = 16, b, *p = NULL;
	//定义对象
	LHList<ElemType> B(m);
	//利用键盘输入操作主文件的插入、删除和查找
	while (1) 
	{
		cout << endl << "功能号表:" << endl;
		cout << "1---创建散列表" << endl;
		cout << "2---向主文件插入元素" << endl;
		cout << "3---从主文件中删除元素" << endl;
		cout << "4---从主文件中查找元素" << endl;
		cout << "5---输出主文件" << endl;
		cout << "6---结束运行" << endl;
		char ch;
		cout << "请输入你的选择(1-5): ";
		cin >> ch;
		switch (ch)
		{
		case '1':cout << "创建散列表" << endl;
			B.CreateHashTable(a, m);
			break;
		case '2':cout << "输入待插入元素d:";
			cin >> d; B.Insert(d); 
			break;
		case '3':cout << "输入待删除元素b:"; 
			cin >> b;
			if (B.Delete(b)) 
				cout << "删除成功!\n";
			else 
				cout << "删除不成功!\n"; 
			break;
		case '4':cout << "输入待查找元素b:";
			cin >> b;
			p = B.Search(b);
			if (p == NULL) 
				cout << "查找不成功!\n";
			else 
				cout << "查找成功!\n"; 
			break;
		case '5':B.PrintHashList(); 
			break;
		case '6':return;
		default:cout << "输入选择错误,请重输!" << endl;
		}
	}
}

