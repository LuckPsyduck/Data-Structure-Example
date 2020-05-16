// 锦标赛排序法.cpp : 定义控制台应用程序的入口点。//又成为树形选择排序
//

#include "stdafx.h"

#include<iostream>
#include<iomanip>
#include<math.h>
#include<stdlib.h>
#include<time.h>

using namespace std;

class DataNode //胜者树结点的类定义
{
public:
	int data;//数据值
	int index;//树中的结点号
	int active;//参选标志
};

//锦标赛排序中的调整算法;i是表中当前
//最小元素的下标,即胜者.从它开始向上调整
void UpdataTree(DataNode *tree, int i)
{
	int j;
	if (i % 2 == 0)								//i为偶数,对手为左结点
		tree[(i - 1) / 2] = tree[i - 1];
	else                                       //i为奇数,对手为右结点
		tree[(i - 1) / 2] = tree[i + 1];
	i = (i - 1) / 2; //i上升到双亲结点位置
	while (i)
	{
		if (i % 2 == 0)
			j = i - 1;//确定i的对手为左结点还是右结点
		else 
			j = i + 1;
		if (!tree[i].active || !tree[j].active)//比赛对手中间有一个空
			if (tree[i].active) 
				tree[(i - 1) / 2] = tree[i];
			else 
				tree[(i - 1) / 2] = tree[j]; //非空者上升到双亲结点
		else                         //比赛对手都不为空
			if (tree[i].data<tree[j].data) 
				tree[(i - 1) / 2] = tree[i];
			else 
				tree[(i - 1) / 2] = tree[j];//胜者上升到双亲结点
			i = (i - 1) / 2; //i上升到双亲结点
	}
}
//建立树的顺序存储数组tree,将数组a[]中的元素复制到胜者树中,
//对它们进行排序,并把结果返回数组中,n是待排序元素个数
void TournmentSort(int a[], int n)
{
	DataNode *tree; //胜者树结点数组
	DataNode item;
	int m, i, j = 0;
	for (int k = 0; k<n; k++)//计算满足>=n的2的最小次幂的数
	{
		m = pow(2, k);
		if (m >= n)
			break;
	}
	int bottomRowSize = m;
	int TreeSize = 2 * bottomRowSize - 1;//计算胜者树的大小:内结点+外结点数
	int loadindex = bottomRowSize - 1;//外结点开始位置
	tree = new DataNode[TreeSize];  //动态分配胜者树结点数组空间

	for (i = loadindex; i<TreeSize; i++)//复制数组数据到树的外结点中
	{
		tree[i].index = i;//下标
		if (j<n) 
		{ 
			tree[i].active = 1; 
			tree[i].data = a[j++];
		}//复制数据
		else 
			tree[i].active = 0; //后面的结点为空的外结点
	}
	i = loadindex;           //进行初始比较寻找最小的项
	while (i)
	{
		j = i;
		while (j<2 * i)          //处理各对比赛者
		{
			if (!tree[j + 1].active || tree[j].data<tree[j + 1].data)
				tree[(j - 1) / 2] = tree[j];
			else 
				tree[(j - 1) / 2] = tree[j + 1];//胜者送入双亲
			j += 2; //下一对参加比较的项
		}
		i = (i - 1) / 2;//i退到双亲,直到i=0为止
	}
	for (i = 0; i<n - 1; i++)//处理其他n-1个元素
	{
		a[i] = tree[0].data;//当前最小元素送数组a
		tree[tree[0].index].active = 0;//该元素相应外结点不再比赛
		UpdataTree(tree, tree[0].index);//从该处向上修改
	}
	a[n - 1] = tree[0].data;
}

//锦标赛排序法的测试
void main()
{
	int n, b[100], i;
	srand(time(0));
	cout << "输入待排序元素个数n:"; 
	cin >> n;
	for (i = 0; i<n; i++)
		b[i] = rand() % 100;
	cout << "排序前数组:\n";
	for (i = 0; i<n; i++)
		cout << setw(4) << b[i];
	cout << endl;
	TournmentSort(b, n);
	cout << "排序后数组:\n";
	for (i = 0; i<n; i++)
		cout << setw(4) << b[i];
	cout << endl;
	cin.get(); cin.get();
}



