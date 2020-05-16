/*不断按回车键，出现运行结果*/
#include "LineList.h"
using namespace std;

void main()
{
	cout << "linelist1m.cpp运行结果:\n";
	ElemType e, e1, e2, e3, e4, e5, e6;
	CLineList *La, *Lb, *Lc;
	int k;
	cout << "首先调用插入函数.\n";
	La->init(&La, 4);
	strcpy(e1.name, "stu1");
	strcpy(e1.stuno, "100001");
	e1.age = 22;
	e1.score = 88;
	La->ListInsert(1, e1);
	strcpy(e2.name, "stu2");
	strcpy(e2.stuno, "100002");
	e2.age = 21;
	e2.score = 79;
	La->ListInsert(2, e2);
	strcpy(e3.name, "stu3");
	strcpy(e3.stuno, "100003");
	e3.age = 19;
	e3.score = 87;
	La->ListInsert(3, e3);
	La->printlist(0);
	cout << "表La长:" << La->ListLength() << endl;
	cin.get();

	Lb->init(&Lb, 4);
	strcpy(e4.name, "zmofun");
	strcpy(e4.stuno, "100001");
	e4.age = 20;
	e4.score = 94;
	Lb->ListInsert(1, e4);
	strcpy(e5.name, "bobjin");
	strcpy(e5.stuno, "100002");
	e5.age = 23;
	e5.score = 69;
	Lb->ListInsert(2, e5);
	strcpy(e6.name, "stu1");
	strcpy(e6.stuno, "100001");
	e6.age = 22;
	e6.score = 88;
	Lb->ListInsert(3, e6);
	Lb->printlist(0);
	cout << "表Lb长:" << Lb->ListLength() << endl;
	cin.get();

	cout << "表La与Lb合并为表Lc:\n";
	Lc->init(&Lc, 6);
	Lc->MergeList(La, Lb);
	Lc->printlist(0);
	cout << "表Lc长:" << Lc->ListLength() << endl;
	cin.get();

	cout << "表La与Lb联合为表La:\n";
	La->UnionList(La, Lb);
	La->printlist(0);
	cout << "表La长:" << La->ListLength() << endl;
	cin.get();

	k = Lc->ListDelete(-1, e6);
	if (k == 0) cout << "删除失败!\n";
	else cout << "删除成功!\n";
	cout << "输出表Lc:\n";
	Lc->printlist(0);
	cin.get();
	strcpy(e.name, "NoName");
	La->PriorElem(e2, e);
	if (strcmp(e.name, "NoName") == 0)
		cout << "e2无前驱!\n";
	else
		cout << "e2的前驱e.name=" << e.name << endl;

	strcpy(e.name, "NoName");
	La->NextElem(e3, e);
	if (strcmp(e.name, "NoName") == 0)
		cout << "e3无后继!\n";
	else
		cout << "e3的后继e.name=" << e.name << endl;
	cin.get();
	cout << "按成绩升序输出表Lc\n";
	Lc->printlist(1);
	cin.get();
	cout << "按成绩降序输出表Lc\n";
	Lc->printlist(-1);
	cin.get();
}


