// 求解迷宫问题(回溯法).cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<iomanip>
#include<stdlib.h>
#include<fstream>
using namespace std;

//路口的结构体定义
typedef struct
{
	int left;
	int forward;
	int right;
}InterS;

//迷宫类定义与实现
class Maze
{
private:
	int mazeSize;//路口个数
	int Exit;    //出口
	InterS *intSec;//路口集合
public:
	//构造函数
	Maze(char *filename);

	//搜索函数
	int TravMaze(int intSecV);
};

Maze::Maze(char *filename)
{
	ifstream fin;
	fin.open(".\\Maze1.dat", ios::in);//打开文件
	if (!fin)
	{
		cerr << "数据文件无法打开!\n"; 
		exit(1);
	}
	fin >> mazeSize;//读入路口个数
	intSec = new InterS[mazeSize + 1];//建立路口集合数组
	for (int i = 1; i <= mazeSize; i++)//读入所有路口的结构体数值
		fin >> intSec[i].left >> intSec[i].forward >> intSec[i].right;
	fin >> Exit; //读入出口号码
	fin.close();//关闭文件
}

int Maze::TravMaze(int intSecV)
{
	if (intSecV>0)
	{
		if (intSecV == Exit)//到达出口// 7
		{
			cout << intSecV << "<==";//输出路口号码
			return 1;
		}
		else if (TravMaze(intSec[intSecV].left))//向左搜索
		{
			cout << intSecV << "<==";//输出路口号码
			return 1;
		}
		else if (TravMaze(intSec[intSecV].forward))//向前搜索
		{
			cout << intSecV << "<==";
			return 1;
		}
		else if (TravMaze(intSec[intSecV].right))//向右搜索
		{
			cout << intSecV << "<==";
			return 1;
		}
	}
	return 0;
}

//迷宫类的测试
void main()
{
	cout << "migong.cpp运行结果:\n";
	cout << "求解迷宫问题:\n";
	char fileName[20] = { ".\\Maze1.dat" };
	Maze m(fileName);
	int start = 1;
	if (m.TravMaze(start))
		cout << endl << "此迷宫的一条通路如上输出所示!\n";
	else
		cout << "此迷宫无通路!\n";
	cin.get();
}







