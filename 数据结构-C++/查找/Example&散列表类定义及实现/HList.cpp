#include "stdafx.h"
#include "HList.h"//除法散列法
using namespace std;

template class LHList<ElemType>;

//构造函数,初始化散列表
template<class T>
LHList<T>::LHList(int MaxSize)
{
	m = MaxSize;
	HT = new LNode*[m];
	for (int i = 0; i<m; i++)
		HT[i] = NULL;
}

//析构函数,清除一个散列表
template<class T>
LHList<T>::~LHList()
{
	LNode* p;//data next
	for (int i = 0; i<m; i++) 
	{
		p = HT[i];
		while (p != NULL)
		{
			HT[i] = p->next;
			delete p;
			p = HT[i];
		}
	}
	delete[]HT;
}

//基于开放地址法的建散列表
template<class T>
void LHList<T>::CreateHashTable(T A[], int n)//根据A[0..n-1]中结点建立散列表T[0..m-1]
{
	int i;
	if (n > m) //用开放定址法处理冲突时,装填因子α须不大于1 //表示不能填满
	{
		cerr << "Load factor>1:\n"; 
		return;
	}
	for (i = 0; i<n; i++) //依次将A[0..n-1]插入到散列表T[0..m-1]中//并非是按顺序的，按照关键字来查找
		Insert(A[i]);
}

//向散列表插入一个元素
template<class T>
void LHList<T>::Insert(T item)
{
	int d = HashAddress(item, m);//计算item的散列地址 // 通过计算来确定位置，
	LNode* p = new LNode;	//为新元素分配存储结点	
	p->data = item;//把新结点插入到d单链表的表头
	p->next = HT[d];
	HT[d] = p;//赋给头元素
}

//从散列表中查找一个元素
template<class T>
T *LHList<T>::Search(T item)
{
	int d = HashAddress(item, m);//计算item的散列地址
	LNode* p = HT[d];//得到对应单链表的表头指针
	//从该单链表中顺序查找匹配的元素,
	//若查找成功返回该元素的地址
	while (p != NULL)
	{
		if (p->data == item) 
			return &(p->data);
		else 
			p = p->next;
	}
	return NULL;	//查找失败返回空指针
}

//从散列表中删除一个元素
template<class T>
bool LHList<T>::Delete(T item)
{
	int d = HashAddress(item, m);//计算item的散列地址
	LNode* p = HT[d];	//p指向对应单链表的表头指针
	
	if (p == NULL)//若单链表为空，则删除失败返回假
		return false;

	if (p->data == item)	//若表头结点为被删除的结点,则删除它后返回真
	{
		HT[d] = p->next;
		delete p;
		return true;
	}
	//从第二个结点起查找被删除的元素,
	//若查找成功则删除它并返回真
	LNode* q = p->next;
	while (q != NULL)
	{
		if (q->data == item) 
		{
			p->next = q->next;
			delete q;
			return true;
		}
		else
		{ 
			p = q; //前驱
			q = q->next; 
		}
	}
	return false;	//没有可删除的元素,则返回假
}

//显示输出散列表中的所有元素
template<class T>
void LHList<T>::PrintHashList()
{
	LNode* p; int n = 0;
	for (int i = 0; i<m; i++) 
	{
		p = HT[i];
		n++;
		cout << setw(3) << i << ':';
		while (p)
		{
			n++;
			cout << setw(3) << p->data;
			if (n % 5 == 0) 
				cout << endl;
			p = p->next;
		}
	}
}


