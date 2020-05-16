// 链式栈(递归).cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
using namespace std;

class list;
class CListNode {
	friend class CList;
	int data;
	CListNode *link;
	CListNode(int value, CListNode *zz) :data(value), link(zz) {}
};

class CList {
	CListNode *first;

	//累加和
	long sum(CListNode *p);

	//计数器
	long count(CListNode *p);

public:
	CList() :first(NULL) {}

	//生成栈
	void add(int value);

	//显示栈中数据
	void display();

	//获取累加和
	long get_sum() { return sum(first); }

	//获取数据个数
	long get_count() { return count(first); }

	//求平均
	float get_avg()
	{
		return (float)sum(first) / count(first);
	}
};

void CList::add(int value) 
{
	CListNode *p = new CListNode(value, first);
	if (p != NULL) 
		first = p;
	else 
		cerr << "Memory Error!" << endl;
}

void CList::display() 
{
	cout << "数据域的各个值:";
	for (CListNode *p = first; p != NULL; p = p->link)
		cout << setw(2) << p->data;
	cout << endl;
}

long CList::sum(CListNode *p) {
	if (p->link == NULL)
		return p->data;
	else 
		return
		p->data + sum(p->link);//迭代
}

long CList::count(CListNode *p) 
{
	long n = 1;
	if (p->link == NULL)
	{ 
		return 1;
	}
	else
	{ 
		return count(p->link) + n; 
	}
}

void main()
{
	cout << "Recurve.cpp运行结果:\n";
	CList a;
	a.add(1);
	a.add(2);
	a.add(3);
	a.add(4);
	a.display();
	cout << "累加和sum=" << a.get_sum() << endl;
	cout << "数据个数count=" << a.get_count() << endl;
	cout << "平均值avg=" << a.get_avg() << endl;
	cin.get();
}


