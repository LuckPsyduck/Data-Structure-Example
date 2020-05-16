
#include "LineList.h"

using namespace std;

CLineList::CLineList() {}
CLineList::~CLineList() {}

void CLineList::init(CLineList **L, int ms)
{
	*L = (CLineList *)malloc(sizeof(CLineList));
	(*L)->length = 0;
	(*L)->MaxSize = ms;
}

int CLineList::ListLength()
{
	return length;
}

ElemType CLineList::PriorElem(ElemType cur_e, ElemType &pre_e)
{
	for (int i = 0; i<length; i++)
		if (i != 0 && strcmp(cur_e.name, elem[i].name) == 0)
		{
			pre_e = elem[i - 1];
			return pre_e;
		}
	return cur_e;
}

ElemType CLineList::NextElem(ElemType cur_e, ElemType &next_e)
{
	for (int i = 0; i<length; i++)
		if (i != length - 1 && strcmp(cur_e.name, elem[i].name) == 0)
		{
			next_e = elem[i + 1];
			return next_e;
		}
	return cur_e;
}

bool CLineList::ListDelete(int mark, ElemType &e)
{
	int i, j;
	if (ListEmpty())
		return false;
	if (mark > 0)
	{  //删除表头元素
		e = elem[0];
		for (i = 1; i<length; i++)
			elem[i - 1] = elem[i];
	}
	else if (mark < 0)				//删除表尾元素
		e = elem[length - 1];
	else
	{  //删除值为e的元素
		for (i = 0; i<length; i++)
			if (strcmp(elem[i].name, e.name) == 0)
				break;
		if (i >= length)
			return false;
		else 
			e = elem[i];
		for (j = i + 1; j<length; j++)
			elem[j - 1] = elem[j];
	}
	length--;
	return true;
}

void CLineList::ListTraverse()
{
	for (int i = 0; i<length; i++)
	{
		cout << setw(8) << elem[i].name;
		cout << setw(10) << elem[i].stuno;
		cout << setw(9) << elem[i].age;
		cout << setw(8) << elem[i].score << endl;
	}
}

void CLineList::GetElem(int i, ElemType *e)
{
	*e = elem[i];
}

bool CLineList::EqualList(ElemType *e1, ElemType *e2)
{
	if (strcmp(e1->name, e2->name))//可以封装成一个函数，之后调用，相当于函数重载比较等于运算符
		return false;
	if (strcmp(e1->stuno, e2->stuno))
		return false;
	if (e1->age != e2->age)
		return false;
	if (e1->score != e2->score)
		return false;
	return true;
}

bool CLineList::Less_EqualList(ElemType *e1, ElemType *e2)
{
	if (strcmp(e1->name, e2->name) <= 0)
		return true;
	else
		return false;
}

bool CLineList::LocateElem(ElemType e, int type)//e是否存在于链表中
{
	int i;
	switch (type)
	{
	case EQUAL:
		for (i = 0; i<length; i++)
			if (EqualList(&elem[i], &e))
				return true;
		break;
	default:break;
	}
	return false;
}

//更新线性表中的给定元素
bool CLineList::UpdateList(ElemType& e, ElemType e1)//替换元素
{
	for (int i = 0; i<length; i++)
		if (strcmp(elem[i].name, e.name) == 0)
		{
			elem[i] = e1;
			return true;
		}
	return false;
}

bool CLineList::ListInsert(int i, ElemType &e)//在i之前插入
{
	ElemType *p, *q;
	if (i<1 || i>length + 1)
		return false;
	q = &elem[i - 1];
	for (p = &elem[length - 1]; p >= q; --p)
		*(p + 1) = *p;
	*q = e;
	++length;
	return true;
}

void CLineList::MergeList(CLineList *La, CLineList *Lb)
{
	int i, j, La_len, Lb_len;
	La_len = La->ListLength();
	Lb_len = Lb->ListLength();

	for (i = 0; i<La_len; i++)
		elem[i] = La->elem[i];
	for (j = 0; j<Lb_len; j++)
		elem[i + j] = Lb->elem[j];
	length = La_len + Lb_len;
}

void CLineList::UnionList(CLineList *La, CLineList *Lb)
{
	int i, La_len, Lb_len;
	ElemType e;
	La_len = La->ListLength();
	Lb_len = Lb->ListLength();

	for (i = 0; i<Lb_len; i++)//将a中没有的元素插入
	{
		Lb->GetElem(i, &e);
		if (!LocateElem(e, EQUAL))
			ListInsert(++La_len, e);
	}
}

//对线性表按升序或降序输出
void CLineList::printlist(int mark)
{
	int* b = new int[length];
	int i, k;
	cout << "    姓名     学号       年龄    成绩\n";
	if (mark != 0)
	{
		for (i = 0; i<length; i++)
			b[i] = i;
		for (i = 0; i<length; i++)//排序
		{
			k = i;
			for (int j = i + 1; j<length; j++)//升序
			{
				if (mark == 1 && elem[b[j]].score<elem[b[k]].score)
					k = j;
				if (mark == -1 && elem[b[k]].score<elem[b[j]].score)
					k = j;
			}
			if (k != i)
			{
				int x = b[i];
				b[i] = b[k];
				b[k] = x;
			}
		}
		for (int i = 0; i<length; i++)
		{
			cout << setw(8) << elem[b[i]].name;
			cout << setw(10) << elem[b[i]].stuno;
			cout << setw(9) << elem[b[i]].age;
			cout << setw(8) << elem[b[i]].score << endl;
		}
	}
	else
	{
		for (i = 0; i<length; i++)
		{
			cout << setw(8) << elem[i].name;
			cout << setw(10) << elem[i].stuno;
			cout << setw(9) << elem[i].age;
			cout << setw(8) << elem[i].score << endl;
		}
	}
}


